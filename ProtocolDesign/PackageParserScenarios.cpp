//
//  PackageParserScenarios.cpp
//  Protocol
//
//  Created by Wahid Tanner on 9/27/14.
//

#include <string>

#include "../Submodules/Designer/Designer/Designer.h"

#include "../Protocol/ProtoParser.h"
#include "../Protocol/PackageParser.h"

using namespace std;
using namespace MuddledManaged;

DESIGNER_SCENARIO( PackageParser, "Construction/Normal", "PackageParser can be constructed." )
{
    Protocol::PackageParser parser;
}

DESIGNER_SCENARIO( PackageParser, "Parsing/Normal", "PackageParser can parse package." )
{
    shared_ptr<Protocol::ProtoModel> model;
    string package = "MuddledManaged.Platform";

    Protocol::ProtoParser parser("Package.proto");
    model = parser.parse();

    verifyEqual(package, model->currentPackage());
}

DESIGNER_SCENARIO( PackageParser, "Parsing/Normal", "PackageParser can parse multiple packages." )
{
    shared_ptr<Protocol::ProtoModel> model;
    string package = "MuddledManaged.Platform";

    Protocol::ProtoParser parser("PackageRedefined.proto");
    model = parser.parse();

    verifyEqual(package, model->currentPackage());
}
