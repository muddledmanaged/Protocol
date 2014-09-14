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

DESIGNER_SCENARIO( TokenReader, "Construction/Normal", "TokenReader can open proto file." )
{
    Protocol::TokenReader reader1("Empty.proto");
    Protocol::TokenReader reader2("Message.proto");
}

DESIGNER_SCENARIO( TokenReader, "Construction/NotFound", "TokenReader cannot open nonexisting proto file." )
{
    Protocol::TokenReader reader("NotFound.proto");

    verifyTrue(false); // Fail this until it is implemented.
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

DESIGNER_SCENARIO( TokenReader, "Iteration/Normal", "TokenReader can iterate empty proto with single-line comment." )
{
    Protocol::TokenReader reader("EmptyCommentSingleLine.proto");
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

DESIGNER_SCENARIO( TokenReader, "Iteration/EOF", "TokenReader can iterate empty proto with single-line comment with no line feed." )
{
    Protocol::TokenReader reader("EmptyCommentSingleLineEOF.proto");
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

DESIGNER_SCENARIO( TokenReader, "Iteration/Normal", "TokenReader can iterate empty proto with multi-line comment." )
{
    Protocol::TokenReader reader("EmptyCommentMultiLine.proto");
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

DESIGNER_SCENARIO( TokenReader, "Iteration/EOF", "TokenReader can iterate empty proto with multi-line comment with no end." )
{
    Protocol::TokenReader reader("EmptyCommentMultiLineEOF.proto");
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

DESIGNER_SCENARIO( TokenReader, "Iteration/Normal", "TokenReader can iterate empty proto with many comments." )
{
    Protocol::TokenReader reader("EmptyComment.proto");
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

DESIGNER_SCENARIO( TokenReader, "Iteration/Unrecognized", "TokenReader can iterate random text." )
{
    Protocol::TokenReader reader("Text.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyTrue(iter1 != iter2);
    verifyEqual("Just some text on a single line.", iter1->text());
    verifyEqual('\0', iter1->endingDelimiter());
    verifyEqual("", iter2->text());
    verifyEqual('\0', iter2->endingDelimiter());

    ++iter1;

    verifyFalse(iter1 != iter2);
    verifyEqual("", iter1->text());
    verifyEqual('\0', iter1->endingDelimiter());
}

DESIGNER_SCENARIO( TokenReader, "Iteration/Unrecognized", "TokenReader can iterate random text with a single-line comment." )
{
    Protocol::TokenReader reader("TextCommentSingleLine.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyTrue(iter1 != iter2);
    verifyEqual("Just some text on a single line.", iter1->text());
    verifyEqual('\0', iter1->endingDelimiter());
    verifyEqual("", iter2->text());
    verifyEqual('\0', iter2->endingDelimiter());

    ++iter1;

    verifyFalse(iter1 != iter2);
    verifyEqual("", iter1->text());
    verifyEqual('\0', iter1->endingDelimiter());
}

DESIGNER_SCENARIO( TokenReader, "Iteration/EOF", "TokenReader can iterate random text with a single-line comment with no line feed." )
{
    Protocol::TokenReader reader("TextCommentSingleLineEOF.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyTrue(iter1 != iter2);
    verifyEqual("Just some text on a single line.", iter1->text());
    verifyEqual('\0', iter1->endingDelimiter());
    verifyEqual("", iter2->text());
    verifyEqual('\0', iter2->endingDelimiter());

    ++iter1;

    verifyFalse(iter1 != iter2);
    verifyEqual("", iter1->text());
    verifyEqual('\0', iter1->endingDelimiter());
}

DESIGNER_SCENARIO( TokenReader, "Iteration/Unrecognized", "TokenReader can iterate random text with a multi-line comment." )
{
    Protocol::TokenReader reader("TextCommentMultiLine.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyTrue(iter1 != iter2);
    verifyEqual("Just some text on a single line.", iter1->text());
    verifyEqual('\0', iter1->endingDelimiter());
    verifyEqual("", iter2->text());
    verifyEqual('\0', iter2->endingDelimiter());

    ++iter1;

    verifyFalse(iter1 != iter2);
    verifyEqual("", iter1->text());
    verifyEqual('\0', iter1->endingDelimiter());
}

DESIGNER_SCENARIO( TokenReader, "Iteration/EOF", "TokenReader can iterate random text with a multi-line comment with no end." )
{
    Protocol::TokenReader reader("TextCommentMultiLineEOF.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyTrue(iter1 != iter2);
    verifyEqual("Just some text on a single line.", iter1->text());
    verifyEqual('\0', iter1->endingDelimiter());
    verifyEqual("", iter2->text());
    verifyEqual('\0', iter2->endingDelimiter());

    ++iter1;

    verifyFalse(iter1 != iter2);
    verifyEqual("", iter1->text());
    verifyEqual('\0', iter1->endingDelimiter());
}

DESIGNER_SCENARIO( TokenReader, "Iteration/Unrecognized", "TokenReader can iterate random text with whitespace." )
{
    Protocol::TokenReader reader("TextWhitespace.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyTrue(iter1 != iter2);
    verifyEqual("Just some text on various lines.", iter1->text());
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
    Protocol::TokenReader reader("Message.proto");
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

DESIGNER_SCENARIO( TokenReader, "Iteration/Normal", "TokenReader can iterate empty message with whitespace." )
{
    Protocol::TokenReader reader("MessageWhitespace.proto");
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

DESIGNER_SCENARIO( TokenReader, "Iteration/Normal", "TokenReader can iterate empty message with comments." )
{
    Protocol::TokenReader reader("MessageComment.proto");
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
