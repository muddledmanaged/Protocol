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

namespace MuddledManaged
{
    namespace Protocol
    {
        class ProtoParser
        {
        public:
            static std::shared_ptr<ProtoModel> parse (const std::string & protoFileName);
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_ProtoParser_h
