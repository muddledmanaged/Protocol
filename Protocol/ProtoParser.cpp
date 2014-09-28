//
//  ProtoParser.cpp
//  Protocol
//
//  Created by Wahid Tanner on 9/16/14.
//

#include <memory>

#include "ProtoParser.h"
#include "TokenReader.h"
#include "PackageParser.h"
#include "MessageParser.h"

using namespace std;
using namespace MuddledManaged;

Protocol::ProtoParser::ProtoParser (const string & protoFileName)
: mReader(new TokenReader(protoFileName))
{
    mParsers.push_back(unique_ptr<ParserInterface>(new PackageParser()));
    mParsers.push_back(unique_ptr<ParserInterface>(new MessageParser()));
}

shared_ptr<Protocol::ProtoModel> Protocol::ProtoParser::parse ()
{
    mModel.reset(new Protocol::ProtoModel());
    auto current = mReader->begin();
    auto end = mReader->end();

    while (current != end)
    {
        for (auto & parser: mParsers)
        {
            if (parser->parse(current, end, mModel))
            {
                break;
            }
        }
        ++current;
    }

    return mModel;
}
