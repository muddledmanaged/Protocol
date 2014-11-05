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
: Nameable(name), Packageable(package)
{
}

Protocol::MessageModel::MessageModel (const MessageModel & src)
: Nameable(src), Packageable(src), OptionModelContainer(src), MessageFieldModelContainer(src),
  EnumModelContainer(src), MessageModelContainer(src), OneofModelContainer(src)
{
}

Protocol::MessageModel & Protocol::MessageModel::operator = (const MessageModel & rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    Nameable::operator=(rhs);
    Packageable::operator=(rhs);
    OptionModelContainer::operator=(rhs);
    MessageFieldModelContainer::operator=(rhs);
    EnumModelContainer::operator=(rhs);
    MessageModelContainer::operator=(rhs);
    OneofModelContainer::operator=(rhs);

    return *this;
}
