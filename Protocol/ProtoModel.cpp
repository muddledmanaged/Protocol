//
//  ProtoModel.cpp
//  Protocol
//
//  Created by Wahid Tanner on 9/16/14.
//

#include "ProtoModel.h"

using namespace std;
using namespace MuddledManaged;

Protocol::ProtoModel::ProtoModel ()
{
    mPackage = "";
}

string Protocol::ProtoModel::package () const
{
    return mPackage;
}

void Protocol::ProtoModel::setPackage (const string & package)
{
    mPackage = package;
}
