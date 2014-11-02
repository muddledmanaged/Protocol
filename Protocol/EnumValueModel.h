//
//  EnumValueModel.h
//  Protocol
//
//  Created by Wahid Tanner on 10/6/14.
//

#ifndef Protocol_EnumValueModel_h
#define Protocol_EnumValueModel_h

#include <string>

#include "Nameable.h"
#include "OptionModel.h"

// Every model header includes its container header.
#include "EnumValueModelContainer.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class EnumValueModel : public Nameable, public OptionModelContainer
        {
        public:
            EnumValueModel (const std::string & name, unsigned int value);

            EnumValueModel (const EnumValueModel & src);

            unsigned int value () const;

            EnumValueModel & operator = (const EnumValueModel & rhs);

        private:
            unsigned int mValue;
        };

    } // namespace Protocol
    
} // namespace MuddledManaged

#endif // Protocol_EnumValueModel_h
