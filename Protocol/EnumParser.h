//
//  EnumParser.h
//  Protocol
//
//  Created by Wahid Tanner on 9/30/14.
//

#ifndef Protocol_EnumParser_h
#define Protocol_EnumParser_h

#include "ParserInterface.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class EnumParser : public ParserInterface
        {
        public:
            EnumParser ();

            virtual bool parse (TokenReader::iterator current, TokenReader::iterator end, std::shared_ptr<ProtoModel> model);
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_EnumParser_h
