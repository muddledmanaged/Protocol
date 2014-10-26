//
//  CodeGeneratorCPPScenarios.cpp
//  Protocol
//
//  Created by Wahid Tanner on 10/18/14.
//

#include <string>

#include "../Submodules/Designer/Designer/Designer.h"

#include "../Protocol/CodeGeneratorManager.h"
#include "../Protocol/ProtoParser.h"

using namespace std;
using namespace MuddledManaged;

DESIGNER_SCENARIO( CodeGeneratorCPP, "Operation/Normal", "CPP generator can create empty file." )
{
    Protocol::CodeGeneratorManager * pManager = Protocol::CodeGeneratorManager::instance();

    auto generator = pManager->generator("CPlusPlus");

    Protocol::ProtoParser parser("Empty.proto");
    auto model = parser.parse();

    generator->generateCode("Generated", *model);
}