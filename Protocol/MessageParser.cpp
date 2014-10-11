//
//  MessageParser.cpp
//  Protocol
//
//  Created by Wahid Tanner on 9/26/14.
//

#include "ParserManager.h"
#include "MessageModel.h"
#include "MessageParser.h"
#include "InvalidProtoException.h"

using namespace std;
using namespace MuddledManaged;

Protocol::MessageParser::MessageParser ()
{
}

bool Protocol::MessageParser::parse (TokenReader::iterator current, TokenReader::iterator end, shared_ptr<ProtoModel> model)
{
    if (current != end && *current == "message")
    {
        // Move to the message name.
        ++current;
        if (current == end || current->empty())
        {
            throw InvalidProtoException(current.line(), current.column(), "Expected message name.");
        }
        shared_ptr<MessageModel> message(new MessageModel(*current, model->currentPackage()));
        model->addMessage(current, message);

        // Move to the opening brace.
        ++current;
        if (current == end || *current != "{")
        {
            throw InvalidProtoException(current.line(), current.column(), "Expected { character.");
        }

        // Process the contents.
        ParserManager * parserMgr = ParserManager::instance();
        bool closingBraceFound = false;
        ++current;
        while (current != end)
        {
            if (*current == "}")
            {
                closingBraceFound = true;
                break;
            }

            bool parserFound = false;
            for (auto & parser: *parserMgr->parsers("message"))
            {
                if (parser->parse(current, end, model))
                {
                    parserFound = true;
                    break;
                }
            }
            if (!parserFound)
            {
                throw InvalidProtoException(current.line(), current.column(), "Unexpected message content found.");
            }
            ++current;
        }
        if (!closingBraceFound)
        {
            // We reached the end of the file without finding the closing brace.
            throw InvalidProtoException(current.line(), current.column(), "Expected } character or field definition.");
        }
        model->completeMessage();

        return true;
    }
    return false;
}
