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
: mCurrentNestedType(""), mCurrentField(nullptr), mCurrentOneof(nullptr), mCurrentEnum(nullptr), mCurrentEnumValue(nullptr)
{
}

string Protocol::ProtoModel::currentNestedType () const
{
    return mCurrentNestedType;
}

void Protocol::ProtoModel::updateCurrentNestedType ()
{
    mCurrentNestedType = "";
    bool firstMessage = true;
    for (auto & message: mMessageQueue)
    {
        if (firstMessage)
        {
            firstMessage = false;
        }
        else
        {
            mCurrentNestedType += ".";
        }
        mCurrentNestedType += message->name();
    }
}

string Protocol::ProtoModel::currentPackage () const
{
    return package();
}

void Protocol::ProtoModel::setCurrentPackage (const string & package)
{
    setPackage(package);
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
    addPublicEnumType(current, enumeration->fullName());

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
    addPublicMessageType(current, message->fullName());

    if (mMessageQueue.empty())
    {
        mMessages.push_back(message);
    }
    else
    {
        mMessageQueue.back()->addMessage(message);
    }
    mMessageQueue.push_back(message);
    updateCurrentNestedType();
}

void Protocol::ProtoModel::completeMessage ()
{
    mMessageQueue.pop_back();
    updateCurrentNestedType();
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
    else if (mCurrentEnum != nullptr)
    {
        mCurrentEnum->addOption(option);
    }
    else if (mCurrentOneof != nullptr)
    {
        mCurrentOneof->addOption(option);
    }
    else if (mMessageQueue.empty())
    {
        mOptions.push_back(option);
    }
    else
    {
        mMessageQueue.back()->addOption(option);
    }
}

bool Protocol::ProtoModel::typeExists (string namedType) const
{
//    auto typeIter = mPrivateEnumTypes.find(namedType);
//    if (typeIter != mPrivateEnumTypes.end())
//    {
//        return true;
//    }
//    typeIter = mPublicEnumTypes.find(namedType);
//    if (typeIter != mPublicEnumTypes.end())
//    {
//        return true;
//    }
//    typeIter = mPrivateMessageTypes.find(namedType);
//    if (typeIter != mPrivateMessageTypes.end())
//    {
//        return true;
//    }
//    typeIter = mPublicMessageTypes.find(namedType);
//    if (typeIter != mPublicMessageTypes.end())
//    {
//        return true;
//    }
    return false;
}

void Protocol::ProtoModel::addPrivateEnumType (TokenReader::iterator current, const string & namedType)
{
    if (typeExists(namedType))
    {
        throw InvalidProtoException(current.line(), current.column(), "Duplicate type names are not allowed.");
    }
    mPrivateEnumTypes.push_back(namedType);
}

void Protocol::ProtoModel::addPublicEnumType (TokenReader::iterator current, const string & namedType)
{
    if (typeExists(namedType))
    {
        throw InvalidProtoException(current.line(), current.column(), "Duplicate type names are not allowed.");
    }
    mPublicEnumTypes.push_back(namedType);
}

void Protocol::ProtoModel::addPrivateMessageType (TokenReader::iterator current, const string & namedType)
{
    if (typeExists(namedType))
    {
        throw InvalidProtoException(current.line(), current.column(), "Duplicate type names are not allowed.");
    }
    mPrivateMessageTypes.push_back(namedType);
}

void Protocol::ProtoModel::addPublicMessageType (TokenReader::iterator current, const string & namedType)
{
    if (typeExists(namedType))
    {
        throw InvalidProtoException(current.line(), current.column(), "Duplicate type names are not allowed.");
    }
    mPublicMessageTypes.push_back(namedType);
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

const Protocol::ProtoModel::NamedTypeCollection * Protocol::ProtoModel::privateEnumTypes () const
{
    return &mPrivateEnumTypes;
}

const Protocol::ProtoModel::NamedTypeCollection * Protocol::ProtoModel::publicEnumTypes () const
{
    return &mPublicEnumTypes;
}

const Protocol::ProtoModel::NamedTypeCollection * Protocol::ProtoModel::privateMessageTypes () const
{
    return &mPrivateMessageTypes;
}

const Protocol::ProtoModel::NamedTypeCollection * Protocol::ProtoModel::publicMessageTypes () const
{
    return &mPublicMessageTypes;
}
