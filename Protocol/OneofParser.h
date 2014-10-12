//
//  OneofParser.h
//  Protocol
//
//  Created by Wahid Tanner on 10/5/14.
//

#ifndef Protocol_OneofParser_h
#define Protocol_OneofParser_h

#include "ParserInterface.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class OneofParser : public ParserInterface
        {
        public:
            OneofParser ();

            virtual bool parse (TokenReader::iterator current, TokenReader::iterator end, bool firstChance, std::shared_ptr<ProtoModel> model);
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_OneofParser_h
