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

DESIGNER_SCENARIO( ProtoParser, "Operation/Normal", "ProtoParser can parse package." )
{
    shared_ptr<Protocol::ProtoModel> model;
    string package = "MuddledManaged.Platform";

    Protocol::ProtoParser parser("Package.proto");
    model = parser.parse();

    verifyEqual(package, model->currentPackage());
}
