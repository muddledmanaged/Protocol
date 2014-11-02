//
//  MessageFieldModel.cpp
//  Protocol
//
//  Created by Wahid Tanner on 10/3/14.
//

#include "MessageFieldModel.h"
#include "ProtoModel.h"

using namespace std;
using namespace MuddledManaged;

Protocol::MessageFieldModel::MessageFieldModel (Requiredness requiredness, const std::string & fieldType, FieldCategory fieldCategory,
                                                const std::string & name, unsigned int index)
: Nameable(name), mRequiredness(requiredness), mFieldType(fieldType), mFieldCategory(fieldCategory), mIndex(index)
{
}

Protocol::MessageFieldModel::MessageFieldModel (const MessageFieldModel & src)
: Nameable(src), OptionModelContainer(src), mRequiredness(src.mRequiredness), mFieldType(src.mFieldType),
  mFieldCategory(src.mFieldCategory), mIndex(src.mIndex)
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

Protocol::MessageFieldModel::FieldCategory Protocol::MessageFieldModel::fieldCategory () const
{
    return mFieldCategory;
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
    mFieldCategory = rhs.mFieldCategory;
    mIndex = rhs.mIndex;

    return *this;
}

Protocol::MessageFieldModel::FieldCategory Protocol::MessageFieldModel::fieldCategoryFromType (const std::string & fieldType,
                                                                                           const Protocol::ProtoModel * protoModel)
{
    if (fieldType == "bool")
    {
        return MessageFieldModel::FieldCategory::numericType;
    }
    if (fieldType == "string")
    {
        return MessageFieldModel::FieldCategory::stringType;
    }
    if (fieldType == "double")
    {
        return MessageFieldModel::FieldCategory::numericType;
    }
    if (fieldType == "float")
    {
        return MessageFieldModel::FieldCategory::numericType;
    }
    if (fieldType == "int32")
    {
        return MessageFieldModel::FieldCategory::numericType;
    }
    if (fieldType == "int64")
    {
        return MessageFieldModel::FieldCategory::numericType;
    }
    if (fieldType == "uint32")
    {
        return MessageFieldModel::FieldCategory::numericType;
    }
    if (fieldType == "uint64")
    {
        return MessageFieldModel::FieldCategory::numericType;
    }
    if (fieldType == "sint32")
    {
        return MessageFieldModel::FieldCategory::numericType;
    }
    if (fieldType == "sint64")
    {
        return MessageFieldModel::FieldCategory::numericType;
    }
    if (fieldType == "fixed32")
    {
        return MessageFieldModel::FieldCategory::numericType;
    }
    if (fieldType == "fixed64")
    {
        return MessageFieldModel::FieldCategory::numericType;
    }
    if (fieldType == "sfixed32")
    {
        return MessageFieldModel::FieldCategory::numericType;
    }
    if (fieldType == "sfixed64")
    {
        return MessageFieldModel::FieldCategory::numericType;
    }
    if (fieldType == "bytes")
    {
        return MessageFieldModel::FieldCategory::stringType;
    }
    return MessageFieldModel::FieldCategory::numericType;
}
