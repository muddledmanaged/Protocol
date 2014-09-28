//
//  PackageParser.cpp
//  Protocol
//
//  Created by Wahid Tanner on 9/26/14.
//

#include <stdexcept>

#include "PackageParser.h"
#include "InvalidProtoException.h"

using namespace std;
using namespace MuddledManaged;

Protocol::PackageParser::PackageParser ()
{ }

bool Protocol::PackageParser::parse (TokenReader::iterator current, TokenReader::iterator end, std::shared_ptr<ProtoModel> model)
{
    if (current != end && *current == "package")
    {
        // Move to the package name.
        ++current;
        if (current == end || current->empty())
        {
            throw InvalidProtoException(current.line(), current.column(), "Expected package name.");
        }
        model->setCurrentPackage(*current);

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
