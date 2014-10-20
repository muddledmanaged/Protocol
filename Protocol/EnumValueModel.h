//
//  EnumValueModel.h
//  Protocol
//
//  Created by Wahid Tanner on 10/6/14.
//

#ifndef Protocol_EnumValueModel_h
#define Protocol_EnumValueModel_h

#include <string>

#include "OptionModelContainer.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class EnumValueModel : public OptionModelContainer
        {
        public:
            EnumValueModel (const std::string & name, unsigned int value);

            EnumValueModel (const EnumValueModel & src);

            std::string name () const;

            unsigned int value () const;

            EnumValueModel & operator = (const EnumValueModel & rhs);

        private:
            std::string mName;
            unsigned int mValue;
        };

    } // namespace Protocol
    
} // namespace MuddledManaged

#endif // Protocol_EnumValueModel_h
