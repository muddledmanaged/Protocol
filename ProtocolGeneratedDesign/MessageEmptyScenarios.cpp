//
//  MessageEmptyScenarios.cpp
//  Protocol
//
//  Created by Wahid Tanner on 12/20/14.
//

#include <string>

#include "../Submodules/Designer/Designer/Designer.h"

#include "../ProtocolDesign/Messages/Generated/Message.protocol.h"

using namespace std;
using namespace MuddledManaged;

DESIGNER_SCENARIO( ProtoParser, "Generation/Normal", "Generated class can be constructed." )
{
    Empty message;
}
