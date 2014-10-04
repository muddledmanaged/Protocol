//
//  MessageFieldParser.cpp
//  Protocol
//
//  Created by Wahid Tanner on 10/3/14.
//

#include <memory>
#include <stdexcept>

#include "MessageFieldModel.h"
#include "MessageFieldParser.h"
#include "InvalidProtoException.h"

using namespace std;
using namespace MuddledManaged;

Protocol::MessageFieldParser::MessageFieldParser ()
{ }

bool Protocol::MessageFieldParser::parse (TokenReader::iterator current, TokenReader::iterator end, std::shared_ptr<ProtoModel> model)
{
    if (current != end)
    {
        Protocol::MessageFieldModel::Requiredness requiredness = Protocol::MessageFieldModel::Requiredness::required;
        if (*current == "required")
        {
            requiredness = Protocol::MessageFieldModel::Requiredness::required;
        }
        else if (*current == "optional")
        {
            requiredness = Protocol::MessageFieldModel::Requiredness::optional;
        }
        else if (*current == "repeated")
        {
            requiredness = Protocol::MessageFieldModel::Requiredness::repeated;
        }
        else
        {
            return false;
        }

        // Move to the field type.
        ++current;
        if (current == end || current->empty())
        {
            throw InvalidProtoException(current.line(), current.column(), "Expected field type.");
        }
        string fieldType = *current;

        // Move to the field name.
        ++current;
        if (current == end || current->empty())
        {
            throw InvalidProtoException(current.line(), current.column(), "Expected field name.");
        }
        string name = *current;

        // Move to the equal.
        ++current;
        if (current == end || *current != "=")
        {
            throw InvalidProtoException(current.line(), current.column(), "Expected = character.");
        }

        // Move to the field index.
        ++current;
        if (current == end || current->empty())
        {
            throw InvalidProtoException(current.line(), current.column(), "Expected field index.");
        }
        unsigned int index = stoi(*current);

        shared_ptr<MessageFieldModel> field(new MessageFieldModel(requiredness, fieldType, name, index));
        model->addField(current, field);

        // Move to the semicolon.
        ++current;
        if (current == end || *current != ";")
        {
            throw InvalidProtoException(current.line(), current.column(), "Expected ; character.");
        }

        return true;
    }
    return false;
}
