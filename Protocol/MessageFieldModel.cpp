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
: Nameable(name), mRequiredness(requiredness), mFieldType(fieldType), mIndex(index)
{
}

Protocol::MessageFieldModel::MessageFieldModel (const MessageFieldModel & src)
: Nameable(src), OptionModelContainer(src), mRequiredness(src.mRequiredness), mFieldType(src.mFieldType), mIndex(src.mIndex)
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

unsigned int Protocol::MessageFieldModel::index () const
{
    return mIndex;
}

Protocol::MessageFieldModel & Protocol::MessageFieldModel::operator = (const MessageFieldModel & rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    Nameable::operator=(rhs);
    OptionModelContainer::operator=(rhs);

    mRequiredness = rhs.mRequiredness;
    mFieldType = rhs.mFieldType;
    mIndex = rhs.mIndex;

    return *this;
}
