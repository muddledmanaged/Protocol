//
//  ParserInterface.h
//  Protocol
//
//  Created by Wahid Tanner on 9/26/14.
//

#ifndef Protocol_ParserInterface_h
#define Protocol_ParserInterface_h

#include <memory>
#include <string>

#include "ProtoModel.h"
#include "TokenReader.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class ParserInterface
        {
        public:
            virtual ~ParserInterface ()
            { }

            virtual bool parse (TokenReader::iterator current, TokenReader::iterator end, bool firstChance, std::shared_ptr<ProtoModel> model) = 0;

        protected:
            ParserInterface ()
            { }

        private:
            ParserInterface (const ParserInterface & src) = delete;
            ParserInterface & operator = (const ParserInterface & rhs) = delete;
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_ParserInterface_h
