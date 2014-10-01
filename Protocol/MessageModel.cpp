//
//  MessageModel.cpp
//  Protocol
//
//  Created by Wahid Tanner on 9/26/14.
//

#include "MessageModel.h"

using namespace std;
using namespace MuddledManaged;

Protocol::MessageModel::MessageModel (const string & name, const string & package)
: Packageable(package), mName(name)
{
}

string Protocol::MessageModel::name () const
{
    return mName;
}

void Protocol::MessageModel::addEnum (EnumModelCollection::value_type enumeration)
{
    mEnums.push_back(enumeration);
}

void Protocol::MessageModel::addMessage (MessageModelCollection::value_type message)
{
    mMessages.push_back(message);
}

Protocol::MessageModel::EnumModelCollection::const_iterator Protocol::MessageModel::cbeginEnum () const
{
    return mEnums.cbegin();
}

Protocol::MessageModel::EnumModelCollection::const_iterator Protocol::MessageModel::cendEnum () const
{
    return mEnums.cend();
}

Protocol::MessageModel::MessageModelCollection::const_iterator Protocol::MessageModel::cbeginMessage () const
{
    return mMessages.cbegin();
}

Protocol::MessageModel::MessageModelCollection::const_iterator Protocol::MessageModel::cendMessage () const
{
    return mMessages.cend();
}
