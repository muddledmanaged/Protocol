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

void Protocol::OneofModel::addOption (OptionModelCollection::value_type & option)
{
    mOptions.push_back(option);
}

const Protocol::OneofModel::OptionModelCollection * Protocol::OneofModel::options () const
{
    return &mOptions;
}
