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

    verifyFalse(iter1 != iter2);
    verifyEqual("", *iter1);
    verifyEqual("", *iter2);
}

DESIGNER_SCENARIO( TokenReader, "Iteration/Normal", "TokenReader can iterate empty proto with single-line comment." )
{
    Protocol::TokenReader reader("EmptyCommentSingleLine.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyFalse(iter1 != iter2);
    verifyEqual("", *iter1);
    verifyEqual("", *iter2);
}

DESIGNER_SCENARIO( TokenReader, "Iteration/EOF", "TokenReader can iterate empty proto with single-line comment with no line feed." )
{
    Protocol::TokenReader reader("EmptyCommentSingleLineEOF.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyFalse(iter1 != iter2);
    verifyEqual("", *iter1);
    verifyEqual("", *iter2);
}

DESIGNER_SCENARIO( TokenReader, "Iteration/Normal", "TokenReader can iterate empty proto with multi-line comment." )
{
    Protocol::TokenReader reader("EmptyCommentMultiLine.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyFalse(iter1 != iter2);
    verifyEqual("", *iter1);
    verifyEqual("", *iter2);
}

DESIGNER_SCENARIO( TokenReader, "Iteration/EOF", "TokenReader can iterate empty proto with multi-line comment with no end." )
{
    Protocol::TokenReader reader("EmptyCommentMultiLineEOF.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyFalse(iter1 != iter2);
    verifyEqual("", *iter1);
    verifyEqual("", *iter2);
}

DESIGNER_SCENARIO( TokenReader, "Iteration/Normal", "TokenReader can iterate empty proto with many comments." )
{
    Protocol::TokenReader reader("EmptyComment.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyFalse(iter1 != iter2);
    verifyEqual("", *iter1);
    verifyEqual("", *iter2);
}

DESIGNER_SCENARIO( TokenReader, "Iteration/Unrecognized", "TokenReader can iterate random text." )
{
    Protocol::TokenReader reader("Text.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyTrue(iter1 != iter2);
    verifyEqual("Just", *iter1);
    verifyEqual("", *iter2);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("some", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("text", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("on", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("a", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("single", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("line.", *iter1);

    ++iter1;

    verifyFalse(iter1 != iter2);
    verifyEqual("", *iter1);
}

DESIGNER_SCENARIO( TokenReader, "Iteration/Unrecognized", "TokenReader can iterate random text with a single-line comment." )
{
    Protocol::TokenReader reader("TextCommentSingleLine.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyTrue(iter1 != iter2);
    verifyEqual("text", *iter1);
    verifyEqual("", *iter2);

    ++iter1;

    verifyFalse(iter1 != iter2);
    verifyEqual("", *iter1);
}

DESIGNER_SCENARIO( TokenReader, "Iteration/EOF", "TokenReader can iterate random text with a single-line comment with no line feed." )
{
    Protocol::TokenReader reader("TextCommentSingleLineEOF.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyTrue(iter1 != iter2);
    verifyEqual("text", *iter1);
    verifyEqual("", *iter2);

    ++iter1;

    verifyFalse(iter1 != iter2);
    verifyEqual("", *iter1);
}

DESIGNER_SCENARIO( TokenReader, "Iteration/Unrecognized", "TokenReader can iterate random text with a multi-line comment." )
{
    Protocol::TokenReader reader("TextCommentMultiLine.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyTrue(iter1 != iter2);
    verifyEqual("text", *iter1);
    verifyEqual("", *iter2);

    ++iter1;

    verifyFalse(iter1 != iter2);
    verifyEqual("", *iter1);
}

DESIGNER_SCENARIO( TokenReader, "Iteration/EOF", "TokenReader can iterate random text with a multi-line comment with no end." )
{
    Protocol::TokenReader reader("TextCommentMultiLineEOF.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyTrue(iter1 != iter2);
    verifyEqual("text", *iter1);
    verifyEqual("", *iter2);

    ++iter1;

    verifyFalse(iter1 != iter2);
    verifyEqual("", *iter1);
}

DESIGNER_SCENARIO( TokenReader, "Iteration/Unrecognized", "TokenReader can iterate random text with adjacent comments." )
{
    Protocol::TokenReader reader("TextCommentNoSpace.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyTrue(iter1 != iter2);
    verifyEqual("text", *iter1);
    verifyEqual("", *iter2);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("more", *iter1);

    ++iter1;

    verifyFalse(iter1 != iter2);
    verifyEqual("", *iter1);
}

DESIGNER_SCENARIO( TokenReader, "Iteration/Unrecognized", "TokenReader can iterate random text with a string." )
{
    Protocol::TokenReader reader("TextString.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyTrue(iter1 != iter2);
    verifyEqual("text", *iter1);
    verifyEqual("", *iter2);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("\"", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("With /* a */ \\\"string\\\" // that looks like a comment.", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("\"", *iter1);

    ++iter1;

    verifyFalse(iter1 != iter2);
    verifyEqual("", *iter1);
}

DESIGNER_SCENARIO( TokenReader, "Iteration/Unrecognized", "TokenReader can iterate random text with multiple delimiters." )
{
    Protocol::TokenReader reader("TextDelimiterMultiple.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);
    verifyEqual("", *iter2);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("text", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("{", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("}", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("[", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("]", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("\"", *iter1);

    ++iter1;

    verifyFalse(iter1 != iter2);
    verifyEqual("", *iter1);
}

DESIGNER_SCENARIO( TokenReader, "Iteration/Unrecognized", "TokenReader can iterate an empty string." )
{
    Protocol::TokenReader reader("TextStringEmpty.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyTrue(iter1 != iter2);
    verifyEqual("\"", *iter1);
    verifyEqual("", *iter2);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("\"", *iter1);

    ++iter1;

    verifyFalse(iter1 != iter2);
    verifyEqual("", *iter1);
}

DESIGNER_SCENARIO( TokenReader, "Iteration/EOF", "TokenReader can iterate random text with an unterminated string." )
{
    Protocol::TokenReader reader("TextStringEOF.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyTrue(iter1 != iter2);
    verifyEqual("text", *iter1);
    verifyEqual("", *iter2);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("\"", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("With an unterminated string.", *iter1);

    ++iter1;

    verifyFalse(iter1 != iter2);
    verifyEqual("", *iter1);
}

DESIGNER_SCENARIO( TokenReader, "Iteration/EOF", "TokenReader can iterate random text with a string on multiple lines." )
{
    Protocol::TokenReader reader("TextStringMultiLine.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyTrue(iter1 != iter2);
    verifyEqual("text", *iter1);
    verifyEqual("", *iter2);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("\"", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("With a string on", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("multiple", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("lines.", *iter1);

    ++iter1;

    verifyFalse(iter1 != iter2);
    verifyEqual("", *iter1);
}

DESIGNER_SCENARIO( TokenReader, "Iteration/EOF", "TokenReader can iterate random text with unterminated strings ending with escape." )
{
    Protocol::TokenReader reader("TextStringEndingEscape.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyTrue(iter1 != iter2);
    verifyEqual("\"", *iter1);
    verifyEqual("", *iter2);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("unterminated string with \\", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("\"", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("another at the end \\", *iter1);

    ++iter1;

    verifyFalse(iter1 != iter2);
    verifyEqual("", *iter1);
}

DESIGNER_SCENARIO( TokenReader, "Iteration/EOF", "TokenReader can iterate random text with unterminated strings at end of line and file." )
{
    // The empty token after the first quote is needed to differentiate
    // this scenario from a legitimate "text"
    Protocol::TokenReader reader("TextStringEndingQuote.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyTrue(iter1 != iter2);
    verifyEqual("\"", *iter1);
    verifyEqual("", *iter2);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("text", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("\"", *iter1);

    ++iter1;

    verifyFalse(iter1 != iter2);
    verifyEqual("", *iter1);
}

DESIGNER_SCENARIO( TokenReader, "Iteration/Normal", "TokenReader can iterate random text with whitespace." )
{
    Protocol::TokenReader reader("TextWhitespace.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyTrue(iter1 != iter2);
    verifyEqual("Just", *iter1);
    verifyEqual("", *iter2);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("some", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("text", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("on", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("various", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("lines.", *iter1);

    ++iter1;

    verifyFalse(iter1 != iter2);
    verifyEqual("", *iter1);
}

DESIGNER_SCENARIO( TokenReader, "Iteration/Normal", "TokenReader can iterate empty message." )
{
    Protocol::TokenReader reader("Message.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyTrue(iter1 != iter2);
    verifyEqual("message", *iter1);
    verifyEqual("", *iter2);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("empty", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("{", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("}", *iter1);

    ++iter1;

    verifyFalse(iter1 != iter2);
    verifyEqual("", *iter1);
}

DESIGNER_SCENARIO( TokenReader, "Iteration/Normal", "TokenReader can iterate empty message with whitespace." )
{
    Protocol::TokenReader reader("MessageWhitespace.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyTrue(iter1 != iter2);
    verifyEqual("message", *iter1);
    verifyEqual("", *iter2);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("empty", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("{", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("}", *iter1);

    ++iter1;

    verifyFalse(iter1 != iter2);
    verifyEqual("", *iter1);
}

DESIGNER_SCENARIO( TokenReader, "Iteration/Normal", "TokenReader can iterate empty message with comments." )
{
    Protocol::TokenReader reader("MessageComment.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyTrue(iter1 != iter2);
    verifyEqual("message", *iter1);
    verifyEqual("", *iter2);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("empty", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("{", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("}", *iter1);

    ++iter1;

    verifyFalse(iter1 != iter2);
    verifyEqual("", *iter1);
}

DESIGNER_SCENARIO( TokenReader, "Iteration/Normal", "TokenReader can iterate full message." )
{
    Protocol::TokenReader reader("MessageEverything.proto");
    auto iter1 = reader.begin();
    auto iter2 = reader.end();

    verifyTrue(iter1 != iter2);
    verifyEqual("import", *iter1);
    verifyEqual("", *iter2);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("public", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("\"", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("MessageNamespace.proto", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("\"", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("package", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("Uv.W.Xyz", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("message", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("M1", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("{", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("oneof", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("choices", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("{", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("string", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("str", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("1", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("bool", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("b", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("200", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("}", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("}", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("package", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("Uv", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("message", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("M2", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("{", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("message", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("M3", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("{", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("required", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("Abc.Def.Simple", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("s", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("1", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("}", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("enum", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("E1", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("{", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("option", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("allow_alias", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("true", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("None", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("0", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("All", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("1", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("Everything", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("1", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("}", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("required", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("M1", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("msg1", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("1", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("optional", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("M3", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("msg3", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("2", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("optional", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("E1", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("e1", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("3", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("[", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("default", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("None", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("]", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("optional", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("double", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("d1", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("4", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("[", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("default", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("3.14", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("]", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("optional", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("float", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("f1", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("5", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("repeated", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("int32", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("i1", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("6", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("[", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("packed", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("true", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("]", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("optional", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("int64", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("i64", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("7", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("optional", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("uint32", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("ui32", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("8", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("optional", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("uint64", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("ui64", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("9", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("optional", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("sint32", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("si32", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("10", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("optional", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("sint64", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("si64", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("11", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("optional", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("fixed32", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("fx32", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("12", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("optional", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("fixed64", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("fx64", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("13", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("optional", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("sfixed32", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("sfx32", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("14", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("optional", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("sfixed64", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("sfx64", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("15", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("optional", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("bool", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("b", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("16", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("required", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("string", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("str1", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("17", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("optional", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("bytes", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("bts", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("18", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("optional", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("E3", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("e3", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("19", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("}", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("enum", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("E3", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("{", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("Good", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("0", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("Better", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("1", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("}", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("message", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("M4", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("{", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("repeated", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("M2.M3", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("msg23", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("=", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual("1", *iter1);

    ++iter1;

    verifyTrue(iter1 != iter2);
    verifyEqual(";", *iter1);

    ++iter1;
    
    verifyTrue(iter1 != iter2);
    verifyEqual("}", *iter1);

    ++iter1;

    verifyFalse(iter1 != iter2);
    verifyEqual("", *iter1);
}
