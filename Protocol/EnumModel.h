//
//  EnumModel.h
//  Protocol
//
//  Created by Wahid Tanner on 9/30/14.
//

#ifndef Protocol_EnumModel_h
#define Protocol_EnumModel_h

#include <string>

#include "Packageable.h"
#include "Nestable.h"
#include "EnumValueModelContainer.h"
#include "OptionModelContainer.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class EnumModel : public Packageable, public Nestable, public OptionModelContainer, public EnumValueModelContainer
        {
        public:
            explicit EnumModel (const std::string & name, const std::string & package = "", const std::string & parentTypes = "");

            EnumModel (const EnumModel & src);

            std::string name () const;

            std::string fullName () const;

            EnumModel & operator = (const EnumModel & rhs);

        private:
            std::string mName;
        };

    } // namespace Protocol
    
} // namespace MuddledManaged

#endif // Protocol_EnumModel_h
