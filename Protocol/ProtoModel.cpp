//
//  ProtoModel.cpp
//  Protocol
//
//  Created by Wahid Tanner on 9/16/14.
//

#include "ProtoModel.h"
#include "InvalidProtoException.h"

using namespace std;
using namespace MuddledManaged;

Protocol::ProtoModel::ProtoModel (const std::string & fileName)
: Nameable(fileName), mCurrentField(nullptr), mCurrentOneof(nullptr), mCurrentEnum(nullptr),
  mCurrentEnumValue(nullptr)
{
}

Protocol::ProtoModel::ProtoModel (const ProtoModel & src)
: Nameable(src), Packageable(src), OptionModelContainer(src), EnumModelContainer(src), MessageModelContainer(src),
  mMessagePath(src.mMessagePath),
  mMessageQueue(src.mMessageQueue), mCurrentField(src.mCurrentField), mCurrentOneof(src.mCurrentOneof),
  mCurrentEnum(src.mCurrentEnum), mCurrentEnumValue(src.mCurrentEnumValue), mPrivateEnumTypes(src.mPrivateEnumTypes),
  mPublicEnumTypes(src.mPublicEnumTypes), mPrivateMessageTypes(src.mPrivateMessageTypes), mPublicMessageTypes(src.mPublicMessageTypes)
{
}

void Protocol::ProtoModel::completeModel ()
{
    auto messageCurrent = messages()->begin();
    auto messageEnd = messages()->end();
    while (messageCurrent != messageEnd)
    {
        auto messageModel = *messageCurrent;

        updateMessageFields(messageModel.get());

        ++messageCurrent;
    }
}

void Protocol::ProtoModel::updateMessageFields (MessageModel * pMessageModel, const std::string & parentMessages)
{
    auto subMessageCurrent = pMessageModel->messages()->begin();
    auto subMessageEnd = pMessageModel->messages()->end();
    while (subMessageCurrent != subMessageEnd)
    {
        auto messageModel = *subMessageCurrent;

        string parentScope = parentMessages;
        if (!parentScope.empty())
        {
            parentScope += ".";
        }
        parentScope += pMessageModel->namePascal();
        updateMessageFields(messageModel.get(), parentScope);

        ++subMessageCurrent;
    }

    auto messageFieldCurrent = pMessageModel->fields()->begin();
    auto messageFieldEnd = pMessageModel->fields()->end();
    while (messageFieldCurrent != messageFieldEnd)
    {
        auto messageFieldModel = *messageFieldCurrent;

        if (messageFieldModel->fieldCategory() == MessageFieldModel::FieldCategory::unknown)
        {
            string messageScope = parentMessages;
            if (!messageScope.empty())
            {
                messageScope += ".";
            }
            messageScope += pMessageModel->namePascal();
            string currentScope = messageFieldModel->package();
            if (!currentScope.empty())
            {
                currentScope += ".";
            }
            currentScope += messageScope;
            bool typeFound = false;
            while (true)
            {
                string currentPath = currentScope;
                if (!currentPath.empty())
                {
                    currentPath += ".";
                }
                currentPath += messageFieldModel->fieldType();
                if (typeExistsAsEnum(currentPath))
                {
                    messageFieldModel->updateFieldCategoryToEnum(currentPath);
                    typeFound = true;
                    break;
                }
                if (typeExistsAsMessage(currentPath))
                {
                    messageFieldModel->updateFieldCategoryToMessage(currentPath);
                    typeFound = true;
                    break;
                }

                // The current referenced type was not found. Keep backing up until a match is found.
                if (currentScope.empty())
                {
                    break;
                }

                auto index = currentScope.find_last_of('.');
                if (index == string::npos)
                {
                    currentScope = "";
                }
                else
                {
                    currentScope = currentScope.substr(0, index);
                }
            }
        }

        ++messageFieldCurrent;
    }
}

void Protocol::ProtoModel::addField (TokenReader::iterator current, MessageFieldModelCollection::value_type & field)
{
    field->setPackage(package());

    if (mMessageQueue.empty())
    {
        throw InvalidProtoException(current.line(), current.column(), "Required message not found.");
    }
    else
    {
        if (mCurrentOneof != nullptr)
        {
            mCurrentOneof->addField(field);
        }
        else
        {
            mMessageQueue.back()->addField(field);
        }
    }
    mCurrentField = field;
}

void Protocol::ProtoModel::completeField ()
{
    mCurrentField = nullptr;
}

void Protocol::ProtoModel::addEnum (TokenReader::iterator current, EnumModelCollection::value_type & enumeration)
{
    addPublicEnumType(current, fullPathWithCurrentPackageAndMessagePath(enumeration->namePascal()));
    enumeration->setPackage(package());

    if (mMessageQueue.empty())
    {
        EnumModelContainer::addEnum(enumeration);
    }
    else
    {
        mMessageQueue.back()->addEnum(enumeration);
    }
    mCurrentEnum = enumeration;
}

void Protocol::ProtoModel::completeEnum ()
{
    mCurrentEnum = nullptr;
}

void Protocol::ProtoModel::addEnumValue (TokenReader::iterator current, EnumValueModelCollection::value_type & value)
{
    if (mCurrentEnum != nullptr)
    {
        mCurrentEnum->addEnumValue(value);
    }
    else
    {
        throw InvalidProtoException(current.line(), current.column(), "Required enum not found.");
    }
    mCurrentEnumValue = value;
}

void Protocol::ProtoModel::completeEnumValue ()
{
    mCurrentEnumValue = nullptr;
}

void Protocol::ProtoModel::addMessage (TokenReader::iterator current, MessageModelCollection::value_type & message)
{
    addPublicMessageType(current, fullPathWithCurrentPackageAndMessagePath(message->namePascal()));
    message->setPackage(package());

    if (mMessageQueue.empty())
    {
        MessageModelContainer::addMessage(message);
    }
    else
    {
        mMessageQueue.back()->addMessage(message);
    }
    mMessageQueue.push_back(message);
    updateMessagePath();
}

void Protocol::ProtoModel::completeMessage ()
{
    mMessageQueue.pop_back();
    updateMessagePath();
}

void Protocol::ProtoModel::addOneof (TokenReader::iterator current, OneofModelCollection::value_type & oneof)
{
    if (mMessageQueue.empty())
    {
        throw InvalidProtoException(current.line(), current.column(), "Required message not found.");
    }
    else
    {
        mMessageQueue.back()->addOneof(oneof);
        mCurrentOneof = oneof;
    }
}

void Protocol::ProtoModel::completeOneof ()
{
    mCurrentOneof = nullptr;
}

void Protocol::ProtoModel::addOption (TokenReader::iterator current, const OptionModelCollection::value_type & option)
{
    if (mCurrentField != nullptr)
    {
        mCurrentField->addOption(option);
    }
    else if (mCurrentEnumValue != nullptr)
    {
        mCurrentEnumValue->addOption(option);
    }
    else if (mCurrentEnum != nullptr)
    {
        mCurrentEnum->addOption(option);
    }
    else if (mCurrentOneof != nullptr)
    {
        mCurrentOneof->addOption(option);
    }
    else if (mMessageQueue.empty())
    {
        OptionModelContainer::addOption(option);
    }
    else
    {
        mMessageQueue.back()->addOption(option);
    }
}

bool Protocol::ProtoModel::typeExists (const string & fullName) const
{
    if (typeExistsAsEnum(fullName) || typeExistsAsMessage(fullName))
    {
        return true;
    }
    return false;
}

bool Protocol::ProtoModel::typeExistsAsEnum (const string & fullName) const
{
    auto typeIter = mPrivateEnumTypes.find(fullName);
    if (typeIter != mPrivateEnumTypes.end())
    {
        return true;
    }
    typeIter = mPublicEnumTypes.find(fullName);
    if (typeIter != mPublicEnumTypes.end())
    {
        return true;
    }
    return false;
}

bool Protocol::ProtoModel::typeExistsAsMessage (const string & fullName) const
{
    auto typeIter = mPrivateMessageTypes.find(fullName);
    if (typeIter != mPrivateMessageTypes.end())
    {
        return true;
    }
    typeIter = mPublicMessageTypes.find(fullName);
    if (typeIter != mPublicMessageTypes.end())
    {
        return true;
    }
    return false;
}

void Protocol::ProtoModel::updateMessagePath ()
{
    mMessagePath = "";
    bool firstMessage = true;
    for (auto & message: mMessageQueue)
    {
        if (firstMessage)
        {
            firstMessage = false;
        }
        else
        {
            mMessagePath += ".";
        }
        mMessagePath += message->namePascal();
    }
}

string Protocol::ProtoModel::fullPathWithCurrentPackageAndMessagePath (const std::string & name) const
{
    string path = package();
    if (!path.empty() && !mMessagePath.empty())
    {
        path += ".";
    }
    path += mMessagePath;
    if (!path.empty())
    {
        path += ".";
    }
    path += name;

    return path;
}

void Protocol::ProtoModel::addImportedProtoName (TokenReader::iterator current, const string & protoName)
{
    mImportedProtoNames.push_back(protoName);
}

void Protocol::ProtoModel::addPrivateEnumType (TokenReader::iterator current, const string & namedType)
{
    if (typeExists(namedType))
    {
        throw InvalidProtoException(current.line(), current.column(), "Duplicate type names are not allowed.");
    }
    mPrivateEnumTypes.emplace(namedType);
}

void Protocol::ProtoModel::addPublicEnumType (TokenReader::iterator current, const string & namedType)
{
    if (typeExists(namedType))
    {
        throw InvalidProtoException(current.line(), current.column(), "Duplicate type names are not allowed.");
    }
    mPublicEnumTypes.emplace(namedType);
}

void Protocol::ProtoModel::addPrivateMessageType (TokenReader::iterator current, const string & namedType)
{
    if (typeExists(namedType))
    {
        throw InvalidProtoException(current.line(), current.column(), "Duplicate type names are not allowed.");
    }
    mPrivateMessageTypes.emplace(namedType);
}

void Protocol::ProtoModel::addPublicMessageType (TokenReader::iterator current, const string & namedType)
{
    if (typeExists(namedType))
    {
        throw InvalidProtoException(current.line(), current.column(), "Duplicate type names are not allowed.");
    }
    mPublicMessageTypes.emplace(namedType);
}

const Protocol::ProtoModel::ImportedProtoNameCollection * Protocol::ProtoModel::importedProtoNames () const
{
    return &mImportedProtoNames;
}

const Protocol::ProtoModel::NamedTypeCollection * Protocol::ProtoModel::privateEnumTypes () const
{
    return &mPrivateEnumTypes;
}

const Protocol::ProtoModel::NamedTypeCollection * Protocol::ProtoModel::publicEnumTypes () const
{
    return &mPublicEnumTypes;
}

const Protocol::ProtoModel::NamedTypeCollection * Protocol::ProtoModel::privateMessageTypes () const
{
    return &mPrivateMessageTypes;
}

const Protocol::ProtoModel::NamedTypeCollection * Protocol::ProtoModel::publicMessageTypes () const
{
    return &mPublicMessageTypes;
}

Protocol::ProtoModel & Protocol::ProtoModel::operator = (const ProtoModel & rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    Nameable::operator=(rhs);
    Packageable::operator=(rhs);
    OptionModelContainer::operator=(rhs);
    EnumModelContainer::operator=(rhs);
    MessageModelContainer::operator=(rhs);

    mMessagePath = rhs.mMessagePath;
    mMessageQueue = rhs.mMessageQueue;
    mCurrentField = rhs.mCurrentField;
    mCurrentOneof = rhs.mCurrentOneof;
    mCurrentEnum = rhs.mCurrentEnum;
    mCurrentEnumValue = rhs.mCurrentEnumValue;
    mPrivateEnumTypes = rhs.mPrivateEnumTypes;
    mPublicEnumTypes = rhs.mPublicEnumTypes;
    mPrivateMessageTypes = rhs.mPrivateMessageTypes;
    mPublicMessageTypes = rhs.mPublicMessageTypes;

    return *this;
}
