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

Protocol::MessageModel::MessageModel (const MessageModel & src)
: Packageable(src), Nestable(src), OptionModelContainer(src), MessageFieldModelContainer(src), EnumModelContainer(src),
  mName(src.mName), mMessages(src.mMessages), mOneofs(src.mOneofs)
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

void Protocol::MessageModel::addMessage (MessageModelCollection::value_type & message)
{
    mMessages.push_back(message);
}

void Protocol::MessageModel::addOneof (OneofModelCollection::value_type & oneof)
{
    mOneofs.push_back(oneof);
}

const Protocol::MessageModel::MessageModelCollection * Protocol::MessageModel::messages () const
{
    return &mMessages;
}

const Protocol::MessageModel::OneofModelCollection * Protocol::MessageModel::oneofs () const
{
    return &mOneofs;
}

Protocol::MessageModel & Protocol::MessageModel::operator = (const MessageModel & rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    Packageable::operator=(rhs);
    Nestable::operator=(rhs);
    OptionModelContainer::operator=(rhs);
    MessageFieldModelContainer::operator=(rhs);
    EnumModelContainer::operator=(rhs);

    mName = rhs.mName;
    mMessages = rhs.mMessages;
    mOneofs = rhs.mOneofs;

    return *this;
}
