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
#include "EnumValueModel.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class EnumModel : public Packageable
        {
        public:
            typedef std::vector<std::shared_ptr<EnumValueModel>> EnumValueModelCollection;

            explicit EnumModel (const std::string & name, const std::string & package = "");

            std::string name () const;

            void addEnumValue (EnumValueModelCollection::value_type value);

            const EnumValueModelCollection * values () const;

        private:
            std::string mName;
            EnumValueModelCollection mValues;
        };

    } // namespace Protocol
    
} // namespace MuddledManaged

#endif // Protocol_EnumModel_h
