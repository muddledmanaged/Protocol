//
//  MessageFieldModel.cpp
//  Protocol
//
//  Created by Wahid Tanner on 10/3/14.
//

#include "MessageFieldModel.h"

using namespace std;
using namespace MuddledManaged;

Protocol::MessageFieldModel::MessageFieldModel (Requiredness requiredness, const std::string & fieldType, const std::string & name, unsigned int index)
: mRequiredness(requiredness), mFieldType(fieldType), mName(name), mIndex(index)
{
}

Protocol::MessageFieldModel::Requiredness Protocol::MessageFieldModel::requiredness () const
{
    return mRequiredness;
}

string Protocol::MessageFieldModel::fieldType () const
{
    return mFieldType;
}

string Protocol::MessageFieldModel::name () const
{
    return mName;
}

unsigned int Protocol::MessageFieldModel::index () const
{
    return mIndex;
}

void Protocol::MessageFieldModel::addOption (OptionModelCollection::value_type & option)
{
    mOptions.push_back(option);
}

const Protocol::MessageFieldModel::OptionModelCollection * Protocol::MessageFieldModel::options () const
{
    return &mOptions;
}
