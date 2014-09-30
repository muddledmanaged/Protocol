//
//  ParserManager.cpp
//  Protocol
//
//  Created by Wahid Tanner on 9/29/14.
//

#include "ParserManager.h"
#include "PackageParser.h"
#include "MessageParser.h"

using namespace std;
using namespace MuddledManaged;

Protocol::ParserManager::ParserManager ()
{
    mParsers.push_back(unique_ptr<ParserInterface>(new PackageParser()));
    mParsers.push_back(unique_ptr<ParserInterface>(new MessageParser()));
}

Protocol::ParserManager::~ParserManager ()
{
}

Protocol::ParserManager * Protocol::ParserManager::instance ()
{
    static ParserManager * singleton = nullptr;
    if (singleton == nullptr)
    {
        singleton = new ParserManager();
    }

    return singleton;
}

const std::list<std::shared_ptr<Protocol::ParserInterface>> & Protocol::ParserManager::parsers () const
{
    return mParsers;
}
