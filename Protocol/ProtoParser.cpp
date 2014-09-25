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

Protocol::ProtoParser::ProtoParser (const string & protoFileName)
: mReader(new TokenReader(protoFileName))
{
}

shared_ptr<Protocol::ProtoModel> Protocol::ProtoParser::parse ()
{
    mModel.reset(new Protocol::ProtoModel());
    auto begin = mReader->begin();
    auto end = mReader->end();

    while (begin != end)
    {
        if (*begin == "package")
        {
            parsePackage(begin, end);
        }
        ++begin;
    }

    return mModel;
}

void Protocol::ProtoParser::parsePackage (Protocol::TokenReader::iterator begin, Protocol::TokenReader::iterator end)
{
    ++begin; // Get the package name.
    mModel->setPackage(*begin);
    ++begin; // Get the ending semicolon.
}
