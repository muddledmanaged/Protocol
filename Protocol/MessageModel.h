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
#include "Nestable.h"
#include "EnumModel.h"
#include "MessageFieldModelContainer.h"
#include "OneofModel.h"
#include "OptionModelContainer.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class MessageModel : public Packageable, public Nestable, public OptionModelContainer, public MessageFieldModelContainer
        {
        public:
            typedef std::vector<std::shared_ptr<EnumModel>> EnumModelCollection;
            typedef std::vector<std::shared_ptr<MessageModel>> MessageModelCollection;
            typedef std::vector<std::shared_ptr<OneofModel>> OneofModelCollection;

            explicit MessageModel (const std::string & name, const std::string & package = "", const std::string & parentTypes = "");

            MessageModel (const MessageModel & src);

            std::string name () const;

            std::string fullName () const;

            void addEnum (EnumModelCollection::value_type & enumeration);

            void addMessage (MessageModelCollection::value_type & message);

            void addOneof (OneofModelCollection::value_type & oneof);

            const EnumModelCollection * enums () const;

            const MessageModelCollection * messages () const;

            const OneofModelCollection * oneofs () const;

            MessageModel & operator = (const MessageModel & rhs);

        private:
            std::string mName;
            EnumModelCollection mEnums;
            MessageModelCollection mMessages;
            OneofModelCollection mOneofs;
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_MessageModel_h
