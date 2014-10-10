//
//  MessageFieldParser.cpp
//  Protocol
//
//  Created by Wahid Tanner on 10/3/14.
//

#include <memory>
#include <stdexcept>

#include "ParserManager.h"
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

        // Move to the semicolon or inline options.
        ParserManager * parserMgr = ParserManager::instance();
        bool optionFound = false;
        ++current;
        if (current == end)
        {
            throw InvalidProtoException(current.line(), current.column(), "Expected ; or [ character.");
        }
        while (*current != ";")
        {
            if (optionFound)
            {
                if (current == end)
                {
                    throw InvalidProtoException(current.line(), current.column(), "Expected , or ] character.");
                }
                if (*current == "]")
                {
                    // Move to the semicolon.
                    ++current;
                    if (current == end || *current != ";")
                    {
                        throw InvalidProtoException(current.line(), current.column(), "Expected ; character.");
                    }
                    break;
                }
                if (*current != ",")
                {
                    throw InvalidProtoException(current.line(), current.column(), "Expected , or ] character.");
                }
            }
            else
            {
                if (*current != "[")
                {
                    throw InvalidProtoException(current.line(), current.column(), "Expected ; or [ character.");
                }
                optionFound = true;
            }
            ++current;
            if (current == end)
            {
                throw InvalidProtoException(current.line(), current.column(), "Expected option name.");
            }

            bool parserFound = false;
            for (auto & parser: *parserMgr->parsers("optionInline"))
            {
                if (parser->parse(current, end, model))
                {
                    parserFound = true;
                    break;
                }
            }
            if (!parserFound)
            {
                throw InvalidProtoException(current.line(), current.column(), "Unexpected option content found.");
            }

            // Move to the comma or closing bracket.
            ++current;
        }
        model->completeField();

        return true;
    }
    return false;
}
