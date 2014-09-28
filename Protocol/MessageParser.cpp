//
//  MessageParser.cpp
//  Protocol
//
//  Created by Wahid Tanner on 9/26/14.
//

#include "MessageModel.h"
#include "MessageParser.h"
#include "InvalidProtoException.h"

using namespace std;
using namespace MuddledManaged;

Protocol::MessageParser::MessageParser ()
{ }

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
        shared_ptr<MessageModel> message(new MessageModel(*current));
        model->addMessage(message);

        // Move to the opening brace.
        ++current;
        if (current == end || *current != "{")
        {
            throw InvalidProtoException(current.line(), current.column(), "Expected { character.");
        }

        // Move to the closing brace.
        ++current;
        if (current == end || *current != "}")
        {
            throw InvalidProtoException(current.line(), current.column(), "Expected } character or field definition.");
        }

        return true;
    }
    return false;
}
