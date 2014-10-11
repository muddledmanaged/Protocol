//
//  OptionValueParser.cpp
//  Protocol
//
//  Created by Wahid Tanner on 10/9/14.
//

#include <memory>
#include <stdexcept>

#include "OptionModel.h"
#include "OptionValueParser.h"
#include "InvalidProtoException.h"

using namespace std;
using namespace MuddledManaged;

Protocol::OptionValueParser::OptionValueParser ()
{ }

bool Protocol::OptionValueParser::parse (TokenReader::iterator current, TokenReader::iterator end, std::shared_ptr<ProtoModel> model)
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

    // This parser is designed to be used by either the OptionSingleParser or the OptionGroupParser and
    // does not move to the terminating character because there could be multiple options.
    return true;
}
