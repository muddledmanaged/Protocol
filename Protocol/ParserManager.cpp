//
//  ParserManager.cpp
//  Protocol
//
//  Created by Wahid Tanner on 9/29/14.
//

#include "ParserManager.h"
#include "EnumParser.h"
#include "EnumValueParser.h"
#include "MessageParser.h"
#include "MessageFieldParser.h"
#include "OneofParser.h"
#include "OneofFieldParser.h"
#include "OptionInlineParser.h"
#include "OptionStandaloneParser.h"
#include "PackageParser.h"

using namespace std;
using namespace MuddledManaged;

Protocol::ParserManager::ParserManager ()
{
    mParserMap.emplace("none", shared_ptr<ParserCollection>(new ParserCollection()));
    mParserMap.emplace("all", shared_ptr<ParserCollection>(new ParserCollection()));
    mParserMap.emplace("general", shared_ptr<ParserCollection>(new ParserCollection()));
    mParserMap.emplace("oneof", shared_ptr<ParserCollection>(new ParserCollection()));
    mParserMap.emplace("enum", shared_ptr<ParserCollection>(new ParserCollection()));
    mParserMap.emplace("optionInline", shared_ptr<ParserCollection>(new ParserCollection()));

    shared_ptr<ParserInterface> packageParser(new PackageParser());
    shared_ptr<ParserInterface> messageParser(new MessageParser());
    shared_ptr<ParserInterface> enumParser(new EnumParser());
    shared_ptr<ParserInterface> enumValueParser(new EnumValueParser());
    shared_ptr<ParserInterface> messageFieldParser(new MessageFieldParser());
    shared_ptr<ParserInterface> oneofParser(new OneofParser());
    shared_ptr<ParserInterface> oneofFieldParser(new OneofFieldParser());
    shared_ptr<ParserInterface> optionInlineParser(new OptionInlineParser());
    shared_ptr<ParserInterface> optionStandaloneParser(new OptionStandaloneParser());

    auto parserIter = mParserMap.find("all");
    if (parserIter != mParserMap.end())
    {
        parserIter->second->push_back(packageParser);
        parserIter->second->push_back(messageParser);
        parserIter->second->push_back(enumParser);
        parserIter->second->push_back(enumValueParser);
        parserIter->second->push_back(messageFieldParser);
        parserIter->second->push_back(oneofParser);
        parserIter->second->push_back(oneofFieldParser);
        parserIter->second->push_back(optionInlineParser);
        parserIter->second->push_back(optionStandaloneParser);
    }

    parserIter = mParserMap.find("general");
    if (parserIter != mParserMap.end())
    {
        parserIter->second->push_back(packageParser);
        parserIter->second->push_back(messageParser);
        parserIter->second->push_back(enumParser);
        parserIter->second->push_back(messageFieldParser);
        parserIter->second->push_back(oneofParser);
        parserIter->second->push_back(optionStandaloneParser);
    }

    parserIter = mParserMap.find("oneof");
    if (parserIter != mParserMap.end())
    {
        parserIter->second->push_back(oneofFieldParser);
    }

    parserIter = mParserMap.find("enum");
    if (parserIter != mParserMap.end())
    {
        parserIter->second->push_back(enumValueParser);
    }

    parserIter = mParserMap.find("optionInline");
    if (parserIter != mParserMap.end())
    {
        parserIter->second->push_back(optionInlineParser);
    }
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

const Protocol::ParserManager::ParserCollection * Protocol::ParserManager::parsers (const std::string & category) const
{
    ParserCollection *pCollection = nullptr;
    auto parserIter = mParserMap.find(category);
    if (parserIter != mParserMap.end())
    {
        pCollection = parserIter->second.get();
    }
    else
    {
        parserIter = mParserMap.find("none");
        if (parserIter != mParserMap.end())
        {
            pCollection = parserIter->second.get();
        }
    }

    return pCollection;
}
