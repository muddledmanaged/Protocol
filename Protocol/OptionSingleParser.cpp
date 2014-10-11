//
//  OptionStandaloneParser.cpp
//  Protocol
//
//  Created by Wahid Tanner on 10/9/14.
//

#include <memory>
#include <stdexcept>

#include "OptionModel.h"
#include "OptionStandaloneParser.h"
#include "InvalidProtoException.h"

using namespace std;
using namespace MuddledManaged;

Protocol::OptionStandaloneParser::OptionStandaloneParser ()
{ }

bool Protocol::OptionStandaloneParser::parse (TokenReader::iterator current, TokenReader::iterator end, std::shared_ptr<ProtoModel> model)
{
    if (current != end && *current == "option")
    {
        // Move to the option name.
        ++current;
        if (current == end || current->empty())
        {
            throw InvalidProtoException(current.line(), current.column(), "Expected option name.");
        }
        string name = *current;

        // Move to the equal.
        ++current;
        if (current == end || *current != "=")
        {
            throw InvalidProtoException(current.line(), current.column(), "Expected = character.");
        }

        // Move to the option value.
        ++current;
        if (current == end || current->empty())
        {
            throw InvalidProtoException(current.line(), current.column(), "Expected option value.");
        }
        string value = *current;

        shared_ptr<OptionModel> option(new OptionModel(name, value));
        model->addOption(current, option);

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
