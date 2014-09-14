//
//  Token.cpp
//  Protocol
//
//  Created by Wahid Tanner on 9/11/14.
//

#include "Token.h"

using namespace std;
using namespace MuddledManaged;

ostream & operator << (ostream & stream, const Protocol::Token & token)
{
    stream << "(\"" << token.text() << "\", '" << token.endingDelimiter() << "')";

    return stream;
};
