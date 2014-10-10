//
//  OptionModel.cpp
//  Protocol
//
//  Created by Wahid Tanner on 10/9/14.
//

#include "OptionModel.h"

using namespace std;
using namespace MuddledManaged;

Protocol::OptionModel::OptionModel (const std::string & name, const std::string & value)
: mName(name), mValue(value)
{
}

string Protocol::OptionModel::name () const
{
    return mName;
}

string Protocol::OptionModel::value () const
{
    return mValue;
}
