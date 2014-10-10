//
//  OptionInlineParser.cpp
//  Protocol
//
//  Created by Wahid Tanner on 10/9/14.
//

#include <memory>
#include <stdexcept>

#include "OptionModel.h"
#include "OptionInlineParser.h"
#include "InvalidProtoException.h"

using namespace std;
using namespace MuddledManaged;

Protocol::OptionInlineParser::OptionInlineParser ()
{ }

bool Protocol::OptionInlineParser::parse (TokenReader::iterator current, TokenReader::iterator end, std::shared_ptr<ProtoModel> model)
{
    if (current != end)
    {
        // Get the option name.
        if (current->empty())
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

        // This parser does not move to the terminating character because there could be multiple options.

        return true;
    }
    return false;
}
