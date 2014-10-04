//
//  MessageFieldParserScenarios.cpp
//  Protocol
//
//  Created by Wahid Tanner on 10/3/14.
//

#include <string>

#include "../Submodules/Designer/Designer/Designer.h"

#include "../Protocol/ProtoParser.h"
#include "../Protocol/MessageFieldParser.h"

using namespace std;
using namespace MuddledManaged;

DESIGNER_SCENARIO( MessageFieldParser, "Construction/Normal", "MessageFieldParser can be constructed." )
{
    Protocol::MessageFieldParser parser;
}

DESIGNER_SCENARIO( MessageFieldParser, "Parsing/Normal", "MessageFieldParser can parse simple message." )
{
    shared_ptr<Protocol::ProtoModel> model;

    Protocol::ProtoParser parser("MessageFieldMultiple.proto");
    model = parser.parse();

    int message1Count = 0;
    auto begin1 = model->messages()->cbegin();
    auto end1 = model->messages()->cend();
    while (begin1 != end1)
    {
        message1Count++;
        auto message1 = *begin1;
        verifyEqual("messageOne", message1->name());

        int field1Count = 0;
        auto begin2 = message1->fields()->cbegin();
        auto end2 = message1->fields()->cend();
        while (begin2 != end2)
        {
            field1Count++;
            auto field1 = *begin2;
            if (field1Count == 1)
            {
                verifyEqual("sOne", field1->name());
            }
            else
            {
                verifyEqual("bOne", field1->name());
            }
            begin2++;
        }

        int message2Count = 0;
        auto begin3 = message1->messages()->cbegin();
        auto end3 = message1->messages()->cend();
        while (begin3 != end3)
        {
            message2Count++;
            auto message2 = *begin3;
            verifyEqual("messageTwo", message2->name());

            int field2Count = 0;
            auto begin4 = message2->fields()->cbegin();
            auto end4 = message2->fields()->cend();
            while (begin4 != end4)
            {
                field2Count++;
                auto field2 = *begin4;
                verifyEqual("sTwo", field2->name());
                begin4++;
            }
            verifyEqual(1, field2Count);
            begin3++;
        }
        verifyEqual(2, field1Count);
        verifyEqual(1, message2Count);
        begin1++;
    }
    verifyEqual(1, message1Count);
}

DESIGNER_SCENARIO( MessageFieldParser, "Parsing/Normal", "MessageFieldParser can parse multiple nested messages with fields." )
{
    shared_ptr<Protocol::ProtoModel> model;

    Protocol::ProtoParser parser("MessageNested.proto");
    model = parser.parse();

    int count1 = 0;
    auto begin1 = model->messages()->cbegin();
    auto end1 = model->messages()->cend();
    while (begin1 != end1)
    {
        count1++;
        auto message1 = *begin1;
        verifyEqual("one", message1->name());

        int count2 = 0;
        auto begin2 = message1->messages()->cbegin();
        auto end2 = message1->messages()->cend();
        while (begin2 != end2)
        {
            count2++;
            auto message2 = *begin2;
            verifyEqual("two", message2->name());

            int count3 = 0;
            auto begin3 = message2->messages()->cbegin();
            auto end3 = message2->messages()->cend();
            while (begin3 != end3)
            {
                count3++;
                auto message3 = *begin3;
                verifyEqual("three", message3->name());
                begin3++;
            }
            verifyEqual(1, count3);
            begin2++;
        }
        verifyEqual(1, count2);
        begin1++;
    }
    verifyEqual(1, count1);
}
