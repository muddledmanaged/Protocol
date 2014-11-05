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

#include "Nameable.h"
#include "EnumModel.h"
#include "MessageFieldModel.h"
#include "OneofModel.h"
#include "OptionModel.h"
#include "Packageable.h"

// Every model header includes its container header.
#include "MessageModelContainer.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class MessageModelContainer;

        class MessageModel : public Nameable, public Packageable, public OptionModelContainer,
                             public MessageFieldModelContainer, public EnumModelContainer,
                             public MessageModelContainer, public OneofModelContainer
        {
        public:
            explicit MessageModel (const std::string & name);

            MessageModel (const MessageModel & src);

            MessageModel & operator = (const MessageModel & rhs);
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_MessageModel_h
