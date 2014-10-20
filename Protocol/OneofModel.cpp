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
: OptionModelContainer(src), MessageFieldModelContainer(src), mName(src.mName)
{
}

string Protocol::OneofModel::name () const
{
    return mName;
}

Protocol::OneofModel & Protocol::OneofModel::operator = (const OneofModel & rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    OptionModelContainer::operator=(rhs);
    MessageFieldModelContainer::operator=(rhs);

    mName = rhs.mName;

    return *this;
}
