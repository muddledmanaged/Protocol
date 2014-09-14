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
    Protocol::TokenReader reader1("Empty.proto");
    Protocol::TokenReader reader2("EmptyMessage.proto");
}

DESIGNER_SCENARIO( TokenReader, "Iteration/Normal", "TokenReader can iterate empty proto." )
{
    Protocol::TokenReader reader("Empty.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyTrue(iter1 != iter2);
    verifyEqual("", iter1->text());
    verifyEqual('\0', iter1->endingDelimiter());
    verifyEqual("", iter2->text());
    verifyEqual('\0', iter2->endingDelimiter());

    ++iter1;

    verifyFalse(iter1 != iter2);
    verifyEqual("", iter1->text());
    verifyEqual('\0', iter1->endingDelimiter());
}

DESIGNER_SCENARIO( TokenReader, "Iteration/Normal", "TokenReader can iterate empty message." )
{
    Protocol::TokenReader reader("EmptyMessage.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyTrue(iter1 != iter2);
    verifyEqual("message empty", iter1->text());
    verifyEqual('{', iter1->endingDelimiter());
    verifyEqual("", iter2->text());
    verifyEqual('\0', iter2->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("", iter1->text());
    verifyEqual('}', iter1->endingDelimiter());

    ++iter1;

    verifyFalse(iter1 != iter2);
    verifyEqual("", iter1->text());
    verifyEqual('\0', iter1->endingDelimiter());
}
