//
//  EnumModel.h
//  Protocol
//
//  Created by Wahid Tanner on 9/30/14.
//

#ifndef Protocol_EnumModel_h
#define Protocol_EnumModel_h

#include <memory>
#include <string>
#include <vector>

#include "Packageable.h"
#include "Nestable.h"
#include "EnumValueModel.h"
#include "OptionModel.h"
#include "OptionModelContainer.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class EnumModel : public Packageable, public Nestable, public OptionModelContainer
        {
        public:
            typedef std::vector<std::shared_ptr<EnumValueModel>> EnumValueModelCollection;

            explicit EnumModel (const std::string & name, const std::string & package = "", const std::string & parentTypes = "");

            EnumModel (const EnumModel & src);

            std::string name () const;

            std::string fullName () const;

            void addEnumValue (EnumValueModelCollection::value_type & value);

            EnumValueModelCollection values () const;

            EnumModel & operator = (const EnumModel & rhs);

        private:
            std::string mName;
            EnumValueModelCollection mValues;
        };

    } // namespace Protocol
    
} // namespace MuddledManaged

#endif // Protocol_EnumModel_h
