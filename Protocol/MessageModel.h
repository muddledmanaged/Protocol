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
#include "EnumModel.h"
#include "MessageFieldModel.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class MessageModel : public Packageable
        {
        public:
            typedef std::vector<std::shared_ptr<MessageFieldModel>> MessageFieldModelCollection;
            typedef std::vector<std::shared_ptr<EnumModel>> EnumModelCollection;
            typedef std::vector<std::shared_ptr<MessageModel>> MessageModelCollection;

            explicit MessageModel (const std::string & name, const std::string & package = "");

            std::string name () const;

            void addField (MessageFieldModelCollection::value_type field);

            void addEnum (EnumModelCollection::value_type enumeration);

            void addMessage (MessageModelCollection::value_type message);

            const MessageFieldModelCollection * fields () const;

            const EnumModelCollection * enums () const;

            const MessageModelCollection * messages () const;

        private:
            std::string mName;
            MessageFieldModelCollection mFields;
            EnumModelCollection mEnums;
            MessageModelCollection mMessages;
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_MessageModel_h
