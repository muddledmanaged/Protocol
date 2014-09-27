//
//  MessageModel.h
//  Protocol
//
//  Created by Wahid Tanner on 9/26/14.
//

#ifndef Protocol_MessageModel_h
#define Protocol_MessageModel_h

#include <string>

#include "Packageable.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class MessageModel : public Packageable
        {
        public:
            explicit MessageModel (const std::string & name, const std::string & package = "");

            std::string name () const;

        private:
            std::string mName;
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_MessageModel_h
