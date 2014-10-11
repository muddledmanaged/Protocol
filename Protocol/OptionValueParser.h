//
//  OptionInlineParser.h
//  Protocol
//
//  Created by Wahid Tanner on 10/9/14.
//

#ifndef Protocol_OptionInlineParser_h
#define Protocol_OptionInlineParser_h

#include "ParserInterface.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class OptionInlineParser : public ParserInterface
        {
        public:
            OptionInlineParser ();

            virtual bool parse (TokenReader::iterator current, TokenReader::iterator end, std::shared_ptr<ProtoModel> model);
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_OptionInlineParser_h
