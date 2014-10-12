//
//  ImportParser.cpp
//  Protocol
//
//  Created by Wahid Tanner on 10/12/14.
//

#include <memory>

#include "ImportParser.h"
#include "ProtoParser.h"
#include "TokenReader.h"
#include "ParserManager.h"
#include "InvalidProtoException.h"

using namespace std;
using namespace MuddledManaged;

Protocol::ImportParser::ImportParser ()
{
}

bool Protocol::ImportParser::parse (TokenReader::iterator current, TokenReader::iterator end, bool firstChance, shared_ptr<ProtoModel> model)
{
    if (current != end && *current == "import")
    {
        // Move to the public flag or proto name.
        bool publicFlag = false;
        ++current;
        if (current != end && *current == "public")
        {
            publicFlag = true;
            ++current;
        }
        if (current == end || *current != "\"")
        {
            throw InvalidProtoException(current.line(), current.column(), "Expected beginning quote character.");
        }

        // Move to the proto name.
        ++current;
        if (current == end || current->empty())
        {
            throw InvalidProtoException(current.line(), current.column(), "Expected beginning quote character.");
        }
        string protoName = *current;

        // Move to the ending quote.
        ++current;
        if (current == end || *current != "\"")
        {
            throw InvalidProtoException(current.line(), current.column(), "Expected ending quote character.");
        }

        // Move to the semicolon.
        ++current;
        if (current == end || *current != ";")
        {
            throw InvalidProtoException(current.line(), current.column(), "Expected ; character.");
        }

        shared_ptr<Protocol::ProtoModel> model;
        Protocol::ProtoParser parser(protoName);
        model = parser.parse();

        return true;
    }
    return false;
}
