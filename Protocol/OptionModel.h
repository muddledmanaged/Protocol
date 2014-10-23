//
//  OptionModel.h
//  Protocol
//
//  Created by Wahid Tanner on 10/9/14.
//

#ifndef Protocol_OptionModel_h
#define Protocol_OptionModel_h

#include <string>

// Every model header includes its container header.
#include "OptionModelContainer.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class OptionModel
        {
        public:
            OptionModel (const std::string & name, const std::string & value);

            std::string name () const;

            std::string value () const;

        private:
            std::string mName;
            std::string mValue;
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_OptionModel_h
