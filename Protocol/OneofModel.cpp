//
//  OneofModel.cpp
//  Protocol
//
//  Created by Wahid Tanner on 10/5/14.
//

#include "OneofModel.h"

using namespace std;
using namespace MuddledManaged;

Protocol::OneofModel::OneofModel (const string & name)
: mName(name)
{
}

Protocol::OneofModel::OneofModel (const OneofModel & src)
: OptionModelContainer(src), mName(src.mName), mFields(src.mFields)
{
}

string Protocol::OneofModel::name () const
{
    return mName;
}

void Protocol::OneofModel::addField (MessageFieldModelCollection::value_type & field)
{
    mFields.push_back(field);
}

const Protocol::OneofModel::MessageFieldModelCollection * Protocol::OneofModel::fields () const
{
    return &mFields;
}

Protocol::OneofModel & Protocol::OneofModel::operator = (const OneofModel & rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    OptionModelContainer::operator=(rhs);

    mName = rhs.mName;
    mFields = rhs.mFields;

    return *this;
}
