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
#include "EnumModelContainer.h"
#include "MessageModelContainer.h"
#include "MessageFieldModelContainer.h"
#include "OneofModel.h"
#include "OptionModelContainer.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class MessageModel : public Packageable, public Nestable, public OptionModelContainer, public MessageFieldModelContainer,
                             public EnumModelContainer, public MessageModelContainer
        {
        public:
            typedef std::vector<std::shared_ptr<OneofModel>> OneofModelCollection;

            explicit MessageModel (const std::string & name, const std::string & package = "", const std::string & parentTypes = "");

            MessageModel (const MessageModel & src);

            std::string name () const;

            std::string fullName () const;

            void addOneof (OneofModelCollection::value_type & oneof);

            const OneofModelCollection * oneofs () const;

            MessageModel & operator = (const MessageModel & rhs);

        private:
            std::string mName;
            OneofModelCollection mOneofs;
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_MessageModel_h
