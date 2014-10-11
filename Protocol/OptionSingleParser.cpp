//
//  OptionSingleParser.cpp
//  Protocol
//
//  Created by Wahid Tanner on 10/9/14.
//

#include <memory>
#include <stdexcept>

#include "ParserManager.h"
#include "OptionSingleParser.h"
#include "InvalidProtoException.h"

using namespace std;
using namespace MuddledManaged;

Protocol::OptionSingleParser::OptionSingleParser ()
{ }

bool Protocol::OptionSingleParser::parse (TokenReader::iterator current, TokenReader::iterator end, std::shared_ptr<ProtoModel> model)
{
    if (current != end && *current == "option")
    {
        // Process the contents.
        ParserManager * parserMgr = ParserManager::instance();
        bool parserFound = false;
        ++current;
        for (auto & parser: *parserMgr->parsers("option"))
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
