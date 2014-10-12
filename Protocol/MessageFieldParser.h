//
//  MessageFieldParser.h
//  Protocol
//
//  Created by Wahid Tanner on 10/3/14.
//

#ifndef Protocol_MessageFieldParser_h
#define Protocol_MessageFieldParser_h

#include "ParserInterface.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class MessageFieldParser : public ParserInterface
        {
        public:
            MessageFieldParser ();

            virtual bool parse (TokenReader::iterator current, TokenReader::iterator end, bool firstChance, std::shared_ptr<ProtoModel> model);
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_MessageFieldParser_h
