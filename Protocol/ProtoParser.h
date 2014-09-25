//
//  ProtoParser.h
//  Protocol
//
//  Created by Wahid Tanner on 9/16/14.
//

#ifndef Protocol_ProtoParser_h
#define Protocol_ProtoParser_h

#include <memory>
#include <string>

#include "ProtoModel.h"
#include "TokenReader.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class ProtoParser
        {
        public:
            ProtoParser (const std::string & protoFileName);

            std::shared_ptr<ProtoModel> parse ();

        private:
            void parsePackage (Protocol::TokenReader::iterator begin, Protocol::TokenReader::iterator end);

            std::shared_ptr<ProtoModel> mModel;
            std::unique_ptr<TokenReader> mReader;
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_ProtoParser_h
