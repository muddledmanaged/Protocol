//
//  ProtoModelScenarios.cpp
//  Protocol
//
//  Created by Wahid Tanner on 9/24/14.
//

#include <string>

#include "../Submodules/Designer/Designer/Designer.h"

#include "../Protocol/ProtoModel.h"

using namespace std;
using namespace MuddledManaged;

DESIGNER_SCENARIO( ProtoModel, "Construction/Normal", "ProtoModel can be constructed." )
{
    Protocol::ProtoModel model;

    verifyEqual("", model.currentPackage());
}

DESIGNER_SCENARIO( ProtoModel, "Operation/Properties", "ProtoModel knows current package." )
{
    Protocol::ProtoModel model;
    string package = "MuddledManaged.Protocol";

    model.setCurrentPackage(package);
    verifyEqual(package, model.currentPackage());
}
