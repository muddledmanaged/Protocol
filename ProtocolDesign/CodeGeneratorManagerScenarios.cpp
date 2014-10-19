//
//  CodeGeneratorManagerScenarios.cpp
//  Protocol
//
//  Created by Wahid Tanner on 10/18/14.
//

#include <string>

#include "../Submodules/Designer/Designer/Designer.h"

#include "../Protocol/CodeGeneratorManager.h"

using namespace std;
using namespace MuddledManaged;

DESIGNER_SCENARIO( CodeGeneratorManager, "Construction/Normal", "CodeGeneratorManager can be constructed." )
{
    Protocol::CodeGeneratorManager * pManager = Protocol::CodeGeneratorManager::instance();

    verifyTrue(pManager != nullptr);
}

DESIGNER_SCENARIO( CodeGeneratorManager, "Construction/Normal", "CodeGeneratorManager cannot construct unknown generators." )
{
    Protocol::CodeGeneratorManager * pManager = Protocol::CodeGeneratorManager::instance();

    auto generator = pManager->generator("");
    verifyTrue(generator == nullptr);

    generator = pManager->generator("unknown");
    verifyTrue(generator == nullptr);
}

DESIGNER_SCENARIO( CodeGeneratorManager, "Construction/Normal", "CodeGeneratorManager can construct CPP generator." )
{
    Protocol::CodeGeneratorManager * pManager = Protocol::CodeGeneratorManager::instance();

    auto generator = pManager->generator("CPlusPlus");
    verifyTrue(generator != nullptr);
}
