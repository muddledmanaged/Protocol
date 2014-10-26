//
//  CodeGeneratorCPP.cpp
//  Protocol
//
//  Created by Wahid Tanner on 10/17/14.
//

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include "CodeGeneratorCPP.h"

using namespace std;
using namespace boost;
using namespace MuddledManaged;

const std::string Protocol::CodeGeneratorCPP::mHeaderFileExtension = ".protocol.h";
const std::string Protocol::CodeGeneratorCPP::mSourceFileExtension = ".protocol.cpp";
const std::string Protocol::CodeGeneratorCPP::mHeaderFileProlog =
"// This file was generated from the Protocol compiler./n"
"// You should not edit this file directly./n";
const std::string Protocol::CodeGeneratorCPP::mSourceFileProlog =
"// This file was generated from the Protocol compiler./n"
"// You should not edit this file directly./n";

Protocol::CodeGeneratorCPP::CodeGeneratorCPP ()
{ }

void Protocol::CodeGeneratorCPP::generateCode (const string & outputFolder, const ProtoModel & model)
{
    if (!filesystem::exists(outputFolder))
    {
        filesystem::create_directory(outputFolder);
    }
}
