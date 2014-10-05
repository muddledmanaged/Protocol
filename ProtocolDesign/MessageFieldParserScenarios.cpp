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

    Protocol::ProtoParser parser("MessageField.proto");
    model = parser.parse();

    int messageCount = 0;
    auto begin1 = model->messages()->cbegin();
    auto end1 = model->messages()->cend();
    while (begin1 != end1)
    {
        messageCount++;
        auto message = *begin1;
        verifyEqual("messageOne", message->name());

        int fieldCount = 0;
        auto begin2 = message->fields()->cbegin();
        auto end2 = message->fields()->cend();
        while (begin2 != end2)
        {
            fieldCount++;
            auto field = *begin2;
            if (fieldCount == 1)
            {
                verifyTrue(Protocol::MessageFieldModel::Requiredness::required == field->requiredness());
                verifyEqual("string", field->fieldType());
                verifyEqual("sOne", field->name());
                verifyEqual(1, field->index());
            }
            else if (fieldCount == 2)
            {
                verifyTrue(Protocol::MessageFieldModel::Requiredness::optional == field->requiredness());
                verifyEqual("bool", field->fieldType());
                verifyEqual("bOne", field->name());
                verifyEqual(2, field->index());
            }
            else if (fieldCount == 3)
            {
                verifyTrue(Protocol::MessageFieldModel::Requiredness::repeated == field->requiredness());
                verifyEqual("int32", field->fieldType());
                verifyEqual("iOne", field->name());
                verifyEqual(3, field->index());
            }
            begin2++;
        }
        verifyEqual(3, fieldCount);
        begin1++;
    }
    verifyEqual(1, messageCount);
}

DESIGNER_SCENARIO( MessageFieldParser, "Parsing/Normal", "MessageFieldParser can parse multiple nested messages with fields." )
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
