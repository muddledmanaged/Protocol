//
//  TokenReaderScenarios.cpp
//  Protocol
//
//  Created by Wahid Tanner on 9/13/14.
//

#include <string>

#include "../Submodules/Designer/Designer/Designer.h"

#include "../Protocol/TokenReader.h"

using namespace std;
using namespace MuddledManaged;

DESIGNER_SCENARIO( TokenReader, "Construction/Normal", "TokenReader can be constructed." )
{
    Protocol::TokenReader reader("main.cpp");

    //verifyEqual("", token.text());
    //verifyEqual('\0', token.endingDelimiter());
}
