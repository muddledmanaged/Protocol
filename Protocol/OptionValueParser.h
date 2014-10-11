//
//  OptionValueParser.h
//  Protocol
//
//  Created by Wahid Tanner on 10/9/14.
//

#ifndef Protocol_OptionValueParser_h
#define Protocol_OptionValueParser_h

#include "ParserInterface.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class OptionValueParser : public ParserInterface
        {
        public:
            OptionValueParser ();

            virtual bool parse (TokenReader::iterator current, TokenReader::iterator end, std::shared_ptr<ProtoModel> model);
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_OptionValueParser_h
