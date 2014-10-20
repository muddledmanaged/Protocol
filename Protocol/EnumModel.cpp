//
//  EnumModel.cpp
//  Protocol
//
//  Created by Wahid Tanner on 9/30/14.
//

#include "EnumModel.h"

using namespace std;
using namespace MuddledManaged;

Protocol::EnumModel::EnumModel (const string & name, const string & package, const string & parentTypes)
: Packageable(package), Nestable(parentTypes), mName(name)
{
}

Protocol::EnumModel::EnumModel (const EnumModel & src)
: Packageable(src), Nestable(src), OptionModelContainer(src), EnumValueModelContainer(src), mName(src.mName)
{
}

string Protocol::EnumModel::name () const
{
    return mName;
}

string Protocol::EnumModel::fullName () const
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

Protocol::EnumModel & Protocol::EnumModel::operator = (const EnumModel & rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    Packageable::operator=(rhs);
    Nestable::operator=(rhs);
    OptionModelContainer::operator=(rhs);
    EnumValueModelContainer::operator=(rhs);

    mName = rhs.mName;

    return *this;
}
