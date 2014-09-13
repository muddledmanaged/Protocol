//
//  Token.cpp
//  Protocol
//
//  Created by Wahid Tanner on 9/11/14.
//

#include "Token.h"

using namespace std;

ostream & operator << (ostream & stream, const Token & token)
{
    stream << "(\"" << token.text() << "\", '" << token.endingDelimiter() << "')";

    return stream;
};
