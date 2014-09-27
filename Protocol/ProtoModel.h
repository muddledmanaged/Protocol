//
//  ProtoModel.h
//  Protocol
//
//  Created by Wahid Tanner on 9/16/14.
//

#ifndef Protocol_ProtoModel_h
#define Protocol_ProtoModel_h

#include <memory>
#include <string>

#include "Packageable.h"
#include "MessageModel.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class ProtoModel : private Packageable
        {
        public:
            ProtoModel ();

            std::string currentPackage () const;
            void setCurrentPackage (const std::string & package);

            void addMessage (std::shared_ptr<MessageModel> message);

        private:
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_ProtoModel_h
