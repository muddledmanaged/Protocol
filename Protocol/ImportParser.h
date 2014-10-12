//
//  ImportParser.h
//  Protocol
//
//  Created by Wahid Tanner on 10/12/14.
//

#ifndef Protocol_ImportParser_h
#define Protocol_ImportParser_h

#include "ParserInterface.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class ImportParser : public ParserInterface
        {
        public:
            ImportParser ();

            virtual bool parse (TokenReader::iterator current, TokenReader::iterator end, bool firstChance, std::shared_ptr<ProtoModel> model);
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_ImportParser_h
