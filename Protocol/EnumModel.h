//
//  EnumModel.h
//  Protocol
//
//  Created by Wahid Tanner on 9/30/14.
//

#ifndef Protocol_EnumModel_h
#define Protocol_EnumModel_h

#include <string>

#include "Nameable.h"
#include "Packageable.h"
#include "EnumValueModel.h"
#include "OptionModel.h"

// Every model header includes its container header.
#include "EnumModelContainer.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class EnumModel : public Nameable, public Packageable, public OptionModelContainer, public EnumValueModelContainer
        {
        public:
            explicit EnumModel (const std::string & name, const std::string & package = "");

            EnumModel (const EnumModel & src);

            EnumModel & operator = (const EnumModel & rhs);
        };

    } // namespace Protocol
    
} // namespace MuddledManaged

#endif // Protocol_EnumModel_h
