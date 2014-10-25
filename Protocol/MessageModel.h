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
#include "MessageFieldModel.h"
#include "OneofModel.h"
#include "OptionModel.h"

// Every model header includes its container header.
#include "MessageModelContainer.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class MessageModelContainer;

        class MessageModel : public Packageable, public Nestable, public OptionModelContainer, public MessageFieldModelContainer,
                             public EnumModelContainer, public MessageModelContainer, public OneofModelContainer
        {
        public:
            explicit MessageModel (const std::string & name, const std::string & package = "", const std::string & parentTypes = "");

            MessageModel (const MessageModel & src);

            std::string name () const;

            std::string fullName () const;

            MessageModel & operator = (const MessageModel & rhs);

        private:
            std::string mName;
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_MessageModel_h
