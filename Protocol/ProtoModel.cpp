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

void Protocol::ProtoModel::addField (TokenReader::iterator current, MessageFieldModelCollection::value_type field)
{
    if (mMessageQueue.empty())
    {
        throw InvalidProtoException(current.line(), current.column(), "Required message not found.");
    }
    else
    {
        mMessageQueue.back()->addField(field);
    }
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
}

void Protocol::ProtoModel::completeEnum ()
{
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
    }
}

void Protocol::ProtoModel::completeOneof ()
{
}

const Protocol::ProtoModel::EnumModelCollection * Protocol::ProtoModel::enums () const
{
    return &mEnums;
}

const Protocol::ProtoModel::MessageModelCollection * Protocol::ProtoModel::messages () const
{
    return &mMessages;
}
