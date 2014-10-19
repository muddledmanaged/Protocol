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
: mName(name), mValue(value)
{
}

Protocol::EnumValueModel::EnumValueModel (const EnumValueModel & src)
: OptionModelContainer(src), mName(src.mName), mValue(src.mValue)
{
}

string Protocol::EnumValueModel::name () const
{
    return mName;
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

    OptionModelContainer::operator=(rhs);

    mName = rhs.mName;
    mValue = rhs.mValue;

    return *this;
}
