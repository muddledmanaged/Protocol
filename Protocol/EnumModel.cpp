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
: Nameable(name), Packageable(package)
{
}

Protocol::EnumModel::EnumModel (const EnumModel & src)
: Nameable(src), Packageable(src), OptionModelContainer(src), EnumValueModelContainer(src)
{
}

Protocol::EnumModel & Protocol::EnumModel::operator = (const EnumModel & rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    Nameable::operator=(rhs);
    Packageable::operator=(rhs);
    OptionModelContainer::operator=(rhs);
    EnumValueModelContainer::operator=(rhs);

    return *this;
}
