//
//  OptionGroupParser.h
//  Protocol
//
//  Created by Wahid Tanner on 10/10/14.
//

#ifndef Protocol_OptionGroupParser_h
#define Protocol_OptionGroupParser_h

#include "ParserInterface.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class OptionGroupParser : public ParserInterface
        {
        public:
            OptionGroupParser ();

            virtual bool parse (TokenReader::iterator current, TokenReader::iterator end, std::shared_ptr<ProtoModel> model);
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_OptionGroupParser_h
