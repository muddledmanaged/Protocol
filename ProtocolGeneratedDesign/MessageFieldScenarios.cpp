//
//  MessageFieldScenarios.cpp
//  Protocol
//
//  Created by Wahid Tanner on 12/25/14.
//

#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <iterator>
#include <iomanip>

#include "../Submodules/Designer/Designer/Designer.h"

#include "../ProtocolDesign/Messages/Generated/MessageField.protocol.h"

using namespace std;
using namespace MuddledManaged;

DESIGNER_SCENARIO( MessageField, "Serialization/Normal", "Generated class can be serialized." )
{
    MessageOne originalMessage;
    string stringValue = "managed";

    originalMessage.setSOne(stringValue);
    originalMessage.addIOne(42);

    string serialized = originalMessage.serialize();

    ostringstream result;
    result << hex;
    copy(serialized.begin(), serialized.end(), ostream_iterator<unsigned int>(result, " "));
    cout << "serialized message: " << result.str() << endl;

    MessageOne parsedMessage;
    parsedMessage.parse(reinterpret_cast<const unsigned char *>(serialized.data()));

    verifyTrue(parsedMessage.hasSOne());
    verifyFalse(parsedMessage.hasBOne());
    //verifyTrue(parsedMessage.sizeIOne() == 1);

    verifyEqual(stringValue, parsedMessage.sOne());
    verifyEqual(42, parsedMessage.iOne(0));
}
