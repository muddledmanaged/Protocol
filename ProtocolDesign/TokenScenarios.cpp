//
//  TokenScenarios.cpp
//  Protocol
//
//  Created by Wahid Tanner on 9/13/14.
//

#include <string>

#include "../Submodules/Designer/Designer/Designer.h"

#include "../Protocol/Token.h"

using namespace std;
using namespace MuddledManaged;

DESIGNER_SCENARIO( Token, "Construction/Normal", "Default Token can be constructed." )
{
    Protocol::Token token;

    verifyEqual("", token.text());
    verifyEqual('\0', token.endingDelimiter());
}

DESIGNER_SCENARIO( Token, "Construction/Normal", "Token can be constructed." )
{
    string text = "message test";
    char delimiter = '{';
    Protocol::Token token(text, delimiter);

    verifyEqual(text, token.text());
    verifyEqual(delimiter, token.endingDelimiter());
}
