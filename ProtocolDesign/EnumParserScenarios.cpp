//
//  EnumParserScenarios.cpp
//  Protocol
//
//  Created by Wahid Tanner on 10/1/14.
//

#include <string>

#include "../Submodules/Designer/Designer/Designer.h"

#include "../Protocol/ProtoParser.h"
#include "../Protocol/EnumParser.h"

using namespace std;
using namespace MuddledManaged;

DESIGNER_SCENARIO( EnumParser, "Construction/Normal", "EnumParser can be constructed." )
{
    Protocol::EnumParser parser;
}

DESIGNER_SCENARIO( EnumParser, "Parsing/Normal", "EnumParser can parse empty enum." )
{
    shared_ptr<Protocol::ProtoModel> model;
    string name = "empty";

    Protocol::ProtoParser parser("Enum.proto");
    model = parser.parse();

    int count = 0;
    auto begin = model->cbeginEnum();
    auto end = model->cendEnum();
    while (begin != end)
    {
        count++;
        auto enumeration = *begin;
        verifyEqual(name, enumeration->name());
        begin++;
    }

    verifyEqual(1, count);
}

DESIGNER_SCENARIO( EnumParser, "Parsing/Normal", "EnumParser can parse multiple empty enums." )
{
    shared_ptr<Protocol::ProtoModel> model;

    Protocol::ProtoParser parser("EnumMultiple.proto");
    model = parser.parse();

    int count = 0;
    auto begin = model->cbeginEnum();
    auto end = model->cendEnum();
    while (begin != end)
    {
        count++;
        auto enumeration = *begin;
        if (count == 1)
        {
            verifyEqual("one", enumeration->name());
        }
        else
        {
            verifyEqual("two", enumeration->name());
        }
        verifyEqual("", enumeration->package());
        begin++;
    }

    verifyEqual(2, count);
}

DESIGNER_SCENARIO( EnumParser, "Parsing/Normal", "EnumParser can assign current package." )
{
    shared_ptr<Protocol::ProtoModel> model;

    Protocol::ProtoParser parser("EnumMultiplePackage.proto");
    model = parser.parse();

    int count = 0;
    auto begin = model->cbeginEnum();
    auto end = model->cendEnum();
    while (begin != end)
    {
        count++;
        auto enumeration = *begin;
        if (count == 1)
        {
            verifyEqual("abc", enumeration->package());
        }
        else
        {
            verifyEqual("def", enumeration->package());
        }
        begin++;
    }

    verifyEqual(2, count);
}
