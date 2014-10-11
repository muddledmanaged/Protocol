//
//  OptionStandaloneParser.h
//  Protocol
//
//  Created by Wahid Tanner on 10/9/14.
//

#ifndef Protocol_OptionStandaloneParser_h
#define Protocol_OptionStandaloneParser_h

#include "ParserInterface.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class OptionStandaloneParser : public ParserInterface
        {
        public:
            OptionStandaloneParser ();

            virtual bool parse (TokenReader::iterator current, TokenReader::iterator end, std::shared_ptr<ProtoModel> model);
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_OptionStandaloneParser_h
