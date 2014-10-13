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

namespace MuddledManaged
{
    namespace Protocol
    {
        class EnumModel : public Packageable, public Nestable
        {
        public:
            typedef std::vector<std::shared_ptr<EnumValueModel>> EnumValueModelCollection;
            typedef std::vector<std::shared_ptr<OptionModel>> OptionModelCollection;

            explicit EnumModel (const std::string & name, const std::string & package = "", const std::string & parentTypes = "");

            std::string name () const;

            std::string fullName () const;

            void addEnumValue (EnumValueModelCollection::value_type value);

            void addOption (OptionModelCollection::value_type option);

            const EnumValueModelCollection * values () const;

            const OptionModelCollection * options () const;

        private:
            std::string mName;
            EnumValueModelCollection mValues;
            OptionModelCollection mOptions;
        };

    } // namespace Protocol
    
} // namespace MuddledManaged

#endif // Protocol_EnumModel_h
