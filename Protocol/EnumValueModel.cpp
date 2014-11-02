//
//  EnumValueModel.cpp
//  Protocol
//
//  Created by Wahid Tanner on 10/6/14.
//

#include "EnumValueModel.h"

using namespace std;
using namespace MuddledManaged;

Protocol::EnumValueModel::EnumValueModel (const std::string & name, unsigned int value)
: Nameable(name), mValue(value)
{
}

Protocol::EnumValueModel::EnumValueModel (const EnumValueModel & src)
: Nameable(src), OptionModelContainer(src), mValue(src.mValue)
{
}

unsigned int Protocol::EnumValueModel::value () const
{
    return mValue;
}

Protocol::EnumValueModel & Protocol::EnumValueModel::operator = (const EnumValueModel & rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    Nameable::operator=(rhs);
    OptionModelContainer::operator=(rhs);

    mValue = rhs.mValue;

    return *this;
}
