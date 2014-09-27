//
//  ProtoParserScenarios.cpp
//  Protocol
//
//  Created by Wahid Tanner on 9/24/14.
//

#include <string>

#include "../Submodules/Designer/Designer/Designer.h"

#include "../Protocol/ProtoParser.h"

using namespace std;
using namespace MuddledManaged;

DESIGNER_SCENARIO( ProtoParser, "Construction/Normal", "ProtoParser can be constructed." )
{
    Protocol::ProtoParser parser("Package.proto");
}
