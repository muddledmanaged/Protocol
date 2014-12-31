//
//  MessageOneofScenarios.cpp
//  Protocol
//
//  Created by Wahid Tanner on 12/30/14.
//

#include <string>

#include "../Submodules/Designer/Designer/Designer.h"

#include "../ProtocolDesign/Messages/Generated/MessageOneof.protocol.h"

using namespace std;
using namespace MuddledManaged;

DESIGNER_SCENARIO( MessageOneof, "Serialization/Normal", "Generated class can be serialized with oneof." )
{
    MessageOneof originalMessage;
    string stringValue = "managed";

    originalMessage.setSOne(stringValue);

    string serialized = originalMessage.serialize();

    MessageOneof parsedMessage;
    parsedMessage.parse(serialized.data());

    verifyTrue(parsedMessage.hasSOne());
    verifyFalse(parsedMessage.hasBOne());
    verifyFalse(parsedMessage.hasIOne());

    verifyEqual(stringValue, parsedMessage.sOne());
}
