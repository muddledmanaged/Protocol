//
//  MessageModel.h
//  Protocol
//
//  Created by Wahid Tanner on 9/26/14.
//

#ifndef Protocol_MessageModel_h
#define Protocol_MessageModel_h

#include <memory>
#include <string>
#include <vector>

#include "Packageable.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class MessageModel : public Packageable
        {
        public:
            typedef std::vector<std::shared_ptr<MessageModel>> MessageModelCollection;

            explicit MessageModel (const std::string & name, const std::string & package = "");

            std::string name () const;

            void addMessage (MessageModelCollection::value_type message);

            MessageModelCollection::const_iterator cbeginMessage () const;
            MessageModelCollection::const_iterator cendMessage () const;

        private:
            std::string mName;
            MessageModelCollection mMessages;
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_MessageModel_h
