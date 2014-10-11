//
//  ProtoModel.cpp
//  Protocol
//
//  Created by Wahid Tanner on 9/16/14.
//

#include "ProtoModel.h"
#include "InvalidProtoException.h"

using namespace std;
using namespace MuddledManaged;

Protocol::ProtoModel::ProtoModel ()
: mCurrentField(nullptr), mCurrentOneof(nullptr), mCurrentEnum(nullptr), mCurrentEnumValue(nullptr)
{
}

std::string Protocol::ProtoModel::currentPackage () const
{
    return package();
}

void Protocol::ProtoModel::setCurrentPackage (const string & package)
{
    setPackage(package);
}

void Protocol::ProtoModel::addToCurrentPackage (const string & additionalPackage)
{
    setPackage(package() + "." + additionalPackage);
}

void Protocol::ProtoModel::addField (TokenReader::iterator current, MessageFieldModelCollection::value_type field)
{
    if (mMessageQueue.empty())
    {
        throw InvalidProtoException(current.line(), current.column(), "Required message not found.");
    }
    else
    {
        if (mCurrentOneof != nullptr)
        {
            mCurrentOneof->addField(field);
        }
        else
        {
            mMessageQueue.back()->addField(field);
        }
    }
    mCurrentField = field;
}

void Protocol::ProtoModel::completeField ()
{
    mCurrentField = nullptr;
}

void Protocol::ProtoModel::addEnum (TokenReader::iterator current, EnumModelCollection::value_type enumeration)
{
    if (mMessageQueue.empty())
    {
        mEnums.push_back(enumeration);
    }
    else
    {
        mMessageQueue.back()->addEnum(enumeration);
    }
    mCurrentEnum = enumeration;
}

void Protocol::ProtoModel::completeEnum ()
{
    mCurrentEnum = nullptr;
}

void Protocol::ProtoModel::addEnumValue (TokenReader::iterator current, EnumValueModelCollection::value_type value)
{
    if (mCurrentEnum != nullptr)
    {
        mCurrentEnum->addEnumValue(value);
    }
    else
    {
        throw InvalidProtoException(current.line(), current.column(), "Required enum not found.");
    }
    mCurrentEnumValue = value;
}

void Protocol::ProtoModel::completeEnumValue ()
{
    mCurrentEnumValue = nullptr;
}

void Protocol::ProtoModel::addMessage (TokenReader::iterator current, MessageModelCollection::value_type message)
{
    if (mMessageQueue.empty())
    {
        mMessages.push_back(message);
    }
    else
    {
        mMessageQueue.back()->addMessage(message);
    }
    mMessageQueue.push_back(message);
}

void Protocol::ProtoModel::completeMessage ()
{
    mMessageQueue.pop_back();
}

void Protocol::ProtoModel::addOneof (TokenReader::iterator current, OneofModelCollection::value_type oneof)
{
    if (mMessageQueue.empty())
    {
        throw InvalidProtoException(current.line(), current.column(), "Required message not found.");
    }
    else
    {
        mMessageQueue.back()->addOneof(oneof);
        mCurrentOneof = oneof;
    }
}

void Protocol::ProtoModel::completeOneof ()
{
    mCurrentOneof = nullptr;
}

void Protocol::ProtoModel::addOption (TokenReader::iterator current, OptionModelCollection::value_type option)
{
    if (mCurrentField != nullptr)
    {
        mCurrentField->addOption(option);
    }
    else if (mCurrentEnumValue != nullptr)
    {
        mCurrentEnumValue->addOption(option);
    }
    else
    {
        mOptions.push_back(option);
    }
}

const Protocol::ProtoModel::EnumModelCollection * Protocol::ProtoModel::enums () const
{
    return &mEnums;
}

const Protocol::ProtoModel::MessageModelCollection * Protocol::ProtoModel::messages () const
{
    return &mMessages;
}

const Protocol::ProtoModel::OptionModelCollection * Protocol::ProtoModel::options () const
{
    return &mOptions;
}
