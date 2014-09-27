//
//  ProtoModel.h
//  Protocol
//
//  Created by Wahid Tanner on 9/16/14.
//

#ifndef Protocol_ProtoModel_h
#define Protocol_ProtoModel_h

#include <list>
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
            typedef std::list<std::shared_ptr<MessageModel>> MessageModelCollection;

            ProtoModel ();

            std::string currentPackage () const;
            void setCurrentPackage (const std::string & package);

            void addMessage (MessageModelCollection::value_type message);

            MessageModelCollection::const_iterator cbeginMessage () const;
            MessageModelCollection::const_iterator cendMessage () const;

        private:
            MessageModelCollection mMessages;
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_ProtoModel_h
