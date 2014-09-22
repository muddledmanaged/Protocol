//
//  ProtoParser.cpp
//  Protocol
//
//  Created by Wahid Tanner on 9/16/14.
//

#include "ProtoParser.h"
#include "TokenReader.h"

using namespace std;
using namespace MuddledManaged;

shared_ptr<Protocol::ProtoModel> Protocol::ProtoParser::parse (const string & protoFileName)
{
    shared_ptr<Protocol::ProtoModel> model(new Protocol::ProtoModel());
    Protocol::TokenReader reader(protoFileName);
    auto beginIter = reader.begin();
    auto endIter = reader.end();

    while (beginIter != endIter)
    {
        if (*beginIter == "package")
        {
            ++beginIter; // Get the package name.
            model->setPackage(*beginIter);
            ++beginIter; // Get the ending semicolon.
        }
        ++beginIter;
    }

    return model;
}
