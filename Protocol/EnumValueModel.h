//
//  EnumValueModel.h
//  Protocol
//
//  Created by Wahid Tanner on 10/6/14.
//

#ifndef Protocol_EnumValueModel_h
#define Protocol_EnumValueModel_h

#include <memory>
#include <string>
#include <vector>

#include "OptionModel.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class EnumValueModel
        {
        public:
            typedef std::vector<std::shared_ptr<OptionModel>> OptionModelCollection;

            EnumValueModel (const std::string & name, unsigned int value);

            std::string name () const;

            unsigned int value () const;

            void addOption (OptionModelCollection::value_type & option);

            const OptionModelCollection * options () const;

        private:
            std::string mName;
            unsigned int mValue;
            OptionModelCollection mOptions;
        };

    } // namespace Protocol
    
} // namespace MuddledManaged

#endif // Protocol_EnumValueModel_h
