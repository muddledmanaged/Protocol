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

Protocol::MessageFieldModel::MessageFieldModel (Requiredness requiredness, const std::string & fieldType,
                                                const std::string & name, unsigned int index)
: Nameable(name), mRequiredness(requiredness), mFieldType(fieldType), mIndex(index)
{
    setFieldCategoryAndFullType();
}

Protocol::MessageFieldModel::MessageFieldModel (const MessageFieldModel & src)
: Nameable(src), Packageable(src), OptionModelContainer(src), mRequiredness(src.mRequiredness), mFieldType(src.mFieldType),
  mFieldTypeFull(src.mFieldTypeFull), mFieldCategory(src.mFieldCategory), mIndex(src.mIndex)
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

string Protocol::MessageFieldModel::fieldTypeFull () const
{
    return mFieldTypeFull;
}

Protocol::MessageFieldModel::FieldCategory Protocol::MessageFieldModel::fieldCategory () const
{
    return mFieldCategory;
}

void Protocol::MessageFieldModel::updateFieldCategoryToEnum (const std::string & fullFieldType)
{
    if (mFieldCategory == FieldCategory::unknown)
    {
        mFieldCategory = FieldCategory::enumType;
        mFieldTypeFull = fullFieldType;
    }
}

void Protocol::MessageFieldModel::updateFieldCategoryToMessage (const std::string & fullFieldType)
{
    if (mFieldCategory == FieldCategory::unknown)
    {
        mFieldCategory = FieldCategory::messageType;
        mFieldTypeFull = fullFieldType;
    }
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
    Packageable::operator=(rhs);
    OptionModelContainer::operator=(rhs);

    mRequiredness = rhs.mRequiredness;
    mFieldType = rhs.mFieldType;
    mFieldTypeFull = rhs.mFieldTypeFull;
    mFieldCategory = rhs.mFieldCategory;
    mIndex = rhs.mIndex;

    return *this;
}

void Protocol::MessageFieldModel::setFieldCategoryAndFullType ()
{
    mFieldTypeFull = mFieldType;
    
    if (mFieldType == "bool")
    {
        mFieldCategory = FieldCategory::numericType;
    }
    else if (mFieldType == "string")
    {
        mFieldCategory = FieldCategory::stringType;
    }
    else if (mFieldType == "double")
    {
        mFieldCategory = FieldCategory::numericType;
    }
    else if (mFieldType == "float")
    {
        mFieldCategory = FieldCategory::numericType;
    }
    else if (mFieldType == "int32")
    {
        mFieldCategory = FieldCategory::numericType;
    }
    else if (mFieldType == "int64")
    {
        mFieldCategory = FieldCategory::numericType;
    }
    else if (mFieldType == "uint32")
    {
        mFieldCategory = FieldCategory::numericType;
    }
    else if (mFieldType == "uint64")
    {
        mFieldCategory = FieldCategory::numericType;
    }
    else if (mFieldType == "sint32")
    {
        mFieldCategory = FieldCategory::numericType;
    }
    else if (mFieldType == "sint64")
    {
        mFieldCategory = FieldCategory::numericType;
    }
    else if (mFieldType == "fixed32")
    {
        mFieldCategory = FieldCategory::numericType;
    }
    else if (mFieldType == "fixed64")
    {
        mFieldCategory = FieldCategory::numericType;
    }
    else if (mFieldType == "sfixed32")
    {
        mFieldCategory = FieldCategory::numericType;
    }
    else if (mFieldType == "sfixed64")
    {
        mFieldCategory = FieldCategory::numericType;
    }
    else if (mFieldType == "bytes")
    {
        mFieldCategory = FieldCategory::stringType;
    }
    else
    {
        mFieldCategory = FieldCategory::unknown;
        mFieldTypeFull = "";
    }
}
