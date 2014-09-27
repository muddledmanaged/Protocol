//
//  MessageParserScenarios.cpp
//  Protocol
//
//  Created by Wahid Tanner on 9/27/14.
//

#include <string>

#include "../Submodules/Designer/Designer/Designer.h"

#include "../Protocol/ProtoParser.h"
#include "../Protocol/MessageParser.h"

using namespace std;
using namespace MuddledManaged;

DESIGNER_SCENARIO( MessageParser, "Construction/Normal", "MessageParser can be constructed." )
{
    Protocol::MessageParser parser;
}

DESIGNER_SCENARIO( MessageParser, "Operation/Normal", "ProtoParser can parse empty message." )
{
    shared_ptr<Protocol::ProtoModel> model;
    string name = "empty";

    Protocol::ProtoParser parser("Message.proto");
    model = parser.parse();

    int count = 0;
    auto begin = model->cbeginMessage();
    auto end = model->cendMessage();
    while (begin != end)
    {
        count++;
        auto message = *begin;
        verifyEqual(name, message->name());
        begin++;
    }

    verifyEqual(1, count);
}
