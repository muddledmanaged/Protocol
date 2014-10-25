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
  MessageModelContainer(src), OneofModelContainer(src), mName(src.mName)
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
    OneofModelContainer::operator=(rhs);

    mName = rhs.mName;

    return *this;
}
