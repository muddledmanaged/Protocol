//
//  MessageModel.cpp
//  Protocol
//
//  Created by Wahid Tanner on 9/26/14.
//

#include "MessageModel.h"

using namespace std;
using namespace MuddledManaged;

Protocol::MessageModel::MessageModel (const string & name, const string & package)
: Packageable(package), mName(name)
{
}

string Protocol::MessageModel::name () const
{
    return mName;
}
