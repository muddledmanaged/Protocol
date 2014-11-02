//
//  OneofModel.h
//  Protocol
//
//  Created by Wahid Tanner on 10/5/14.
//

#ifndef Protocol_OneofModel_h
#define Protocol_OneofModel_h

#include <string>

#include "MessageFieldModel.h"
#include "Nameable.h"
#include "OptionModel.h"

// Every model header includes its container header.
#include "OneofModelContainer.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class OneofModel : public Nameable, public OptionModelContainer, public MessageFieldModelContainer
        {
        public:
            explicit OneofModel (const std::string & name);

            OneofModel (const OneofModel & src);

            OneofModel & operator = (const OneofModel & rhs);
        };
        
    } // namespace Protocol
    
} // namespace MuddledManaged

#endif // Protocol_OneofModel_h
