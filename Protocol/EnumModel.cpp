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
