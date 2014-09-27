//
//  MessageParser.cpp
//  Protocol
//
//  Created by Wahid Tanner on 9/26/14.
//

#include "MessageModel.h"
#include "MessageParser.h"

using namespace std;
using namespace MuddledManaged;

Protocol::MessageParser::MessageParser ()
{ }

bool Protocol::MessageParser::parse (TokenReader::iterator begin, TokenReader::iterator end, shared_ptr<ProtoModel> model)
{
    if (begin != end && *begin == "message")
    {
        // Move to the message name.
        ++begin;
        if (begin == end || begin->empty())
        {
            throw std::logic_error("");
        }
        shared_ptr<MessageModel> message(new MessageModel(*begin));
        model->addMessage(message);

        // Move to the opening brace.
        ++begin;
        if (begin == end || *begin != "{")
        {
            throw std::logic_error("");
        }

        // Move to the closing brace.
        ++begin;
        if (begin == end || *begin != "}")
        {
            throw std::logic_error("");
        }

        return true;
    }
    return false;
}
