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

DESIGNER_SCENARIO( TokenReader, "Iteration/String", "TokenReader can iterate random text with a string." )
{
    Protocol::TokenReader reader("TextString.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyTrue(iter1 != iter2);
    verifyEqual("Just some text on a single line.", iter1->text());
    verifyEqual('\"', iter1->endingDelimiter());
    verifyEqual("", iter2->text());
    verifyEqual('\0', iter2->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("With /* a */ \\\"string\\\" // that looks like a comment.", iter1->text());
    verifyEqual('\"', iter1->endingDelimiter());

    ++iter1;

    verifyFalse(iter1 != iter2);
    verifyEqual("", iter1->text());
    verifyEqual('\0', iter1->endingDelimiter());
}

DESIGNER_SCENARIO( TokenReader, "Iteration/String", "TokenReader can iterate random text with an unterminated string." )
{
    Protocol::TokenReader reader("TextStringEOF.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyTrue(iter1 != iter2);
    verifyEqual("Just some text on a single line.", iter1->text());
    verifyEqual('\"', iter1->endingDelimiter());
    verifyEqual("", iter2->text());
    verifyEqual('\0', iter2->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("With an unterminated string.", iter1->text());
    verifyEqual('\0', iter1->endingDelimiter());

    ++iter1;

    verifyFalse(iter1 != iter2);
    verifyEqual("", iter1->text());
    verifyEqual('\0', iter1->endingDelimiter());
}

DESIGNER_SCENARIO( TokenReader, "Iteration/String", "TokenReader can iterate random text with a string on multiple lines." )
{
    Protocol::TokenReader reader("TextStringMultiLine.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyTrue(iter1 != iter2);
    verifyEqual("Just some text on a single line.", iter1->text());
    verifyEqual('\"', iter1->endingDelimiter());
    verifyEqual("", iter2->text());
    verifyEqual('\0', iter2->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("With a string on", iter1->text());
    verifyEqual('\0', iter1->endingDelimiter());

    ++iter1;

    verifyFalse(iter1 != iter2);
    verifyEqual("", iter1->text());
    verifyEqual('\0', iter1->endingDelimiter());
}

DESIGNER_SCENARIO( TokenReader, "Iteration/Normal", "TokenReader can iterate random text with whitespace." )
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

DESIGNER_SCENARIO( TokenReader, "Iteration/Normal", "TokenReader can iterate full message." )
{
    Protocol::TokenReader reader("MessageEverything.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyTrue(iter1 != iter2);
    verifyEqual("import public", iter1->text());
    verifyEqual('\"', iter1->endingDelimiter());
    verifyEqual("", iter2->text());
    verifyEqual('\0', iter2->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("MessageNamespace.proto", iter1->text());
    verifyEqual('\"', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("", iter1->text());
    verifyEqual(';', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("package Uv.W.Xyz", iter1->text());
    verifyEqual(';', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("message M1", iter1->text());
    verifyEqual('{', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("oneof choices", iter1->text());
    verifyEqual('{', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("string str", iter1->text());
    verifyEqual('=', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("1", iter1->text());
    verifyEqual(';', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("bool b", iter1->text());
    verifyEqual('=', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("200", iter1->text());
    verifyEqual(';', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("", iter1->text());
    verifyEqual('}', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("", iter1->text());
    verifyEqual('}', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("message M2", iter1->text());
    verifyEqual('{', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("message M3", iter1->text());
    verifyEqual('{', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("required Abc.Def.Simple s", iter1->text());
    verifyEqual('=', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("1", iter1->text());
    verifyEqual(';', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("", iter1->text());
    verifyEqual('}', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("enum E1", iter1->text());
    verifyEqual('{', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("option allow_alias", iter1->text());
    verifyEqual('=', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("true", iter1->text());
    verifyEqual(';', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("None", iter1->text());
    verifyEqual('=', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("0", iter1->text());
    verifyEqual(';', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("All", iter1->text());
    verifyEqual('=', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("1", iter1->text());
    verifyEqual(';', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("Everything", iter1->text());
    verifyEqual('=', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("1", iter1->text());
    verifyEqual(';', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("", iter1->text());
    verifyEqual('}', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("required M1 msg1", iter1->text());
    verifyEqual('=', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("1", iter1->text());
    verifyEqual(';', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("optional M3 msg3", iter1->text());
    verifyEqual('=', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("2", iter1->text());
    verifyEqual(';', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("optional E1 e1", iter1->text());
    verifyEqual('=', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("3", iter1->text());
    verifyEqual('[', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("default", iter1->text());
    verifyEqual('=', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("None", iter1->text());
    verifyEqual(']', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("", iter1->text());
    verifyEqual(';', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("optional double d1", iter1->text());
    verifyEqual('=', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("4", iter1->text());
    verifyEqual('[', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("default", iter1->text());
    verifyEqual('=', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("3.14", iter1->text());
    verifyEqual(']', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("", iter1->text());
    verifyEqual(';', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("optional float f1", iter1->text());
    verifyEqual('=', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("5", iter1->text());
    verifyEqual(';', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("repeated int32 i1", iter1->text());
    verifyEqual('=', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("6", iter1->text());
    verifyEqual('[', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("packed", iter1->text());
    verifyEqual('=', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("true", iter1->text());
    verifyEqual(']', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("", iter1->text());
    verifyEqual(';', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("optional int64 i64", iter1->text());
    verifyEqual('=', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("7", iter1->text());
    verifyEqual(';', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("optional uint32 ui32", iter1->text());
    verifyEqual('=', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("8", iter1->text());
    verifyEqual(';', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("optional uint64 ui64", iter1->text());
    verifyEqual('=', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("9", iter1->text());
    verifyEqual(';', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("optional sint32 si32", iter1->text());
    verifyEqual('=', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("10", iter1->text());
    verifyEqual(';', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("optional sint64 si64", iter1->text());
    verifyEqual('=', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("11", iter1->text());
    verifyEqual(';', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("optional fixed32 fx32", iter1->text());
    verifyEqual('=', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("12", iter1->text());
    verifyEqual(';', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("optional fixed64 fx64", iter1->text());
    verifyEqual('=', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("13", iter1->text());
    verifyEqual(';', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("optional sfixed32 sfx32", iter1->text());
    verifyEqual('=', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("14", iter1->text());
    verifyEqual(';', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("optional sfixed64 sfx64", iter1->text());
    verifyEqual('=', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("15", iter1->text());
    verifyEqual(';', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("optiona bool b", iter1->text());
    verifyEqual('=', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("16", iter1->text());
    verifyEqual(';', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("required string str1", iter1->text());
    verifyEqual('=', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("17", iter1->text());
    verifyEqual(';', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("optional bytes bts", iter1->text());
    verifyEqual('=', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("18", iter1->text());
    verifyEqual(';', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("", iter1->text());
    verifyEqual('}', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("message M4", iter1->text());
    verifyEqual('{', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("repeated M2.M3 msg23", iter1->text());
    verifyEqual('=', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("1", iter1->text());
    verifyEqual(';', iter1->endingDelimiter());

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("", iter1->text());
    verifyEqual('}', iter1->endingDelimiter());
    
    ++iter1;

    verifyFalse(iter1 != iter2);
    verifyEqual("", iter1->text());
    verifyEqual('\0', iter1->endingDelimiter());
}
