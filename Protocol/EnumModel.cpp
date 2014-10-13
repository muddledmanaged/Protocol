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

void Protocol::EnumModel::addEnumValue (EnumValueModelCollection::value_type value)
{
    mValues.push_back(value);
}

const Protocol::EnumModel::EnumValueModelCollection * Protocol::EnumModel::values () const
{
    return &mValues;
}

void Protocol::EnumModel::addOption (OptionModelCollection::value_type option)
{
    mOptions.push_back(option);
}

const Protocol::EnumModel::OptionModelCollection * Protocol::EnumModel::options () const
{
    return &mOptions;
}
