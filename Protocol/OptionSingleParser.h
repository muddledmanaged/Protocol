//
//  OptionSingleParser.h
//  Protocol
//
//  Created by Wahid Tanner on 10/9/14.
//

#ifndef Protocol_OptionSingleParser_h
#define Protocol_OptionSingleParser_h

#include "ParserInterface.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class OptionSingleParser : public ParserInterface
        {
        public:
            OptionSingleParser ();

            virtual bool parse (TokenReader::iterator current, TokenReader::iterator end, std::shared_ptr<ProtoModel> model);
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_OptionSingleParser_h
