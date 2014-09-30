//
//  ParserManager.h
//  Protocol
//
//  Created by Wahid Tanner on 9/29/14.
//

#ifndef Protocol_ParserManager_h
#define Protocol_ParserManager_h

#include <memory>
#include <list>

#include "ParserInterface.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class ParserManager
        {
        public:
            ~ParserManager ();

            static ParserManager * instance ();

            const std::list<std::shared_ptr<ParserInterface>> & parsers () const;

        private:
            ParserManager ();
            ParserManager (const ParserManager & src) = delete;
            ParserManager & operator = (const ParserManager & rhs) = delete;

            std::list<std::shared_ptr<ParserInterface>> mParsers;
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_ParserManager_h
