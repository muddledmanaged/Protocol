//
//  OneofModel.h
//  Protocol
//
//  Created by Wahid Tanner on 10/5/14.
//

#ifndef Protocol_OneofModel_h
#define Protocol_OneofModel_h

#include <string>

#include "MessageFieldModelContainer.h"
#include "OptionModelContainer.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class OneofModel : public OptionModelContainer, public MessageFieldModelContainer
        {
        public:
            explicit OneofModel (const std::string & name);

            OneofModel (const OneofModel & src);

            std::string name () const;

            OneofModel & operator = (const OneofModel & rhs);

        private:
            std::string mName;
        };
        
    } // namespace Protocol
    
} // namespace MuddledManaged

#endif // Protocol_OneofModel_h
