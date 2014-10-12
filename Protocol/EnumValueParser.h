//
//  EnumValueParser.h
//  Protocol
//
//  Created by Wahid Tanner on 10/6/14.
//

#ifndef Protocol_EnumValueParser_h
#define Protocol_EnumValueParser_h

#include "ParserInterface.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class EnumValueParser : public ParserInterface
        {
        public:
            EnumValueParser ();

            virtual bool parse (TokenReader::iterator current, TokenReader::iterator end, bool firstChance, std::shared_ptr<ProtoModel> model);
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_EnumValueParser_h
