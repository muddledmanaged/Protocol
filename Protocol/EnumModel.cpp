//
//  EnumModel.cpp
//  Protocol
//
//  Created by Wahid Tanner on 9/30/14.
//

#include "EnumModel.h"

using namespace std;
using namespace MuddledManaged;

Protocol::EnumModel::EnumModel (const string & name, const string & package)
: Packageable(package), mName(name)
{
}

string Protocol::EnumModel::name () const
{
    return mName;
}

void Protocol::EnumModel::addEnumValue (EnumValueModelCollection::value_type value)
{
    mValues.push_back(value);
}

const Protocol::EnumModel::EnumValueModelCollection * Protocol::EnumModel::values () const
{
    return &mValues;
}
