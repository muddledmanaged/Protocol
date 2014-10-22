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
  MessageModelContainer(src), mName(src.mName), mOneofs(src.mOneofs)
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

void Protocol::MessageModel::addOneof (OneofModelCollection::value_type & oneof)
{
    mOneofs.push_back(oneof);
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
    MessageModelContainer::operator=(rhs);

    mName = rhs.mName;
    mOneofs = rhs.mOneofs;

    return *this;
}
