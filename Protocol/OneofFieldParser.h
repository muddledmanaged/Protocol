//
//  OneofFieldParser.h
//  Protocol
//
//  Created by Wahid Tanner on 10/5/14.
//

#ifndef Protocol_OneofFieldParser_h
#define Protocol_OneofFieldParser_h

#include "ParserInterface.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class OneofFieldParser : public ParserInterface
        {
        public:
            OneofFieldParser ();

            virtual bool parse (TokenReader::iterator current, TokenReader::iterator end, bool firstChance, std::shared_ptr<ProtoModel> model);
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_OneofFieldParser_h
