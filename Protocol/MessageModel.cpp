//
//  MessageModel.cpp
//  Protocol
//
//  Created by Wahid Tanner on 9/26/14.
//

#include "MessageModel.h"

using namespace std;
using namespace MuddledManaged;

Protocol::MessageModel::MessageModel (const string & name, const string & package, const string & parentTypes)
: Packageable(package), Nestable(parentTypes), mName(name)
{
}

string Protocol::MessageModel::name () const
{
    return mName;
}

string Protocol::MessageModel::fullName () const
{
    string fullName = package();
    if (!fullName.empty())
    {
        fullName += ".";
    }

    fullName += parentTypes();
    if (!parentTypes().empty())
    {
        fullName += ".";
    }
    fullName += name();

    return fullName;
}

void Protocol::MessageModel::addField (MessageFieldModelCollection::value_type & field)
{
    mFields.push_back(field);
}

void Protocol::MessageModel::addEnum (EnumModelCollection::value_type & enumeration)
{
    mEnums.push_back(enumeration);
}

void Protocol::MessageModel::addMessage (MessageModelCollection::value_type & message)
{
    mMessages.push_back(message);
}

void Protocol::MessageModel::addOneof (OneofModelCollection::value_type & oneof)
{
    mOneofs.push_back(oneof);
}

void Protocol::MessageModel::addOption (OptionModelCollection::value_type & option)
{
    mOptions.push_back(option);
}

const Protocol::MessageModel::MessageFieldModelCollection * Protocol::MessageModel::fields () const
{
    return &mFields;
}

const Protocol::MessageModel::EnumModelCollection * Protocol::MessageModel::enums () const
{
    return &mEnums;
}

const Protocol::MessageModel::MessageModelCollection * Protocol::MessageModel::messages () const
{
    return &mMessages;
}

const Protocol::MessageModel::OneofModelCollection * Protocol::MessageModel::oneofs () const
{
    return &mOneofs;
}

const Protocol::MessageModel::OptionModelCollection * Protocol::MessageModel::options () const
{
    return &mOptions;
}
