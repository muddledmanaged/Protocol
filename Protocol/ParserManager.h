//
//  ParserManager.h
//  Protocol
//
//  Created by Wahid Tanner on 9/29/14.
//

#ifndef Protocol_ParserManager_h
#define Protocol_ParserManager_h

#include <memory>
#include <vector>

#include "ParserInterface.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class ParserManager
        {
        public:
            typedef std::vector<std::shared_ptr<ParserInterface>> ParserCollection;

            ~ParserManager ();

            static ParserManager * instance ();

            const ParserCollection * parsers () const;

        private:
            ParserManager ();
            ParserManager (const ParserManager & src) = delete;
            ParserManager & operator = (const ParserManager & rhs) = delete;

            ParserCollection mParsers;
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_ParserManager_h
