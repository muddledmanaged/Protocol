//
//  OptionModel.h
//  Protocol
//
//  Created by Wahid Tanner on 10/9/14.
//

#ifndef Protocol_OptionModel_h
#define Protocol_OptionModel_h

#include <string>

#include "Nameable.h"

// Every model header includes its container header.
#include "OptionModelContainer.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class OptionModel : public Nameable
        {
        public:
            OptionModel (const std::string & name, const std::string & value);

            OptionModel (const OptionModel & src);

            std::string value () const;

            OptionModel & operator = (const OptionModel & rhs);

        private:
            std::string mValue;
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_OptionModel_h
