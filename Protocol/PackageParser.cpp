//
//  PackageParser.cpp
//  Protocol
//
//  Created by Wahid Tanner on 9/26/14.
//

#include <stdexcept>

#include "PackageParser.h"

using namespace std;
using namespace MuddledManaged;

Protocol::PackageParser::PackageParser ()
{ }

bool Protocol::PackageParser::parse (TokenReader::iterator begin, TokenReader::iterator end, std::shared_ptr<ProtoModel> model)
{
    if (begin != end && *begin == "package")
    {
        // Move to the package name.
        ++begin;
        if (begin == end || begin->empty())
        {
            throw std::logic_error("");
        }
        model->setCurrentPackage(*begin);

        // Move to the semicolon.
        ++begin;
        if (begin == end || *begin != ";")
        {
            throw std::logic_error("");
        }

        return true;
    }
    return false;
}
