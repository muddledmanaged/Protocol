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

string Protocol::EnumValueModel::name () const
{
    return mName;
}

unsigned int Protocol::EnumValueModel::value () const
{
    return mValue;
}

void Protocol::EnumValueModel::addOption (OptionModelCollection::value_type option)
{
    mOptions.push_back(option);
}

const Protocol::EnumValueModel::OptionModelCollection * Protocol::EnumValueModel::options () const
{
    return &mOptions;
}
