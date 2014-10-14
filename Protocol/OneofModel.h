//
//  OneofModel.h
//  Protocol
//
//  Created by Wahid Tanner on 10/5/14.
//

#ifndef Protocol_OneofModel_h
#define Protocol_OneofModel_h

#include <memory>
#include <string>
#include <vector>

#include "MessageFieldModel.h"
#include "OptionModel.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class OneofModel
        {
        public:
            typedef std::vector<std::shared_ptr<MessageFieldModel>> MessageFieldModelCollection;
            typedef std::vector<std::shared_ptr<OptionModel>> OptionModelCollection;

            explicit OneofModel (const std::string & name);

            std::string name () const;

            void addField (MessageFieldModelCollection::value_type & field);

            void addOption (OptionModelCollection::value_type & option);

            const MessageFieldModelCollection * fields () const;

            const OptionModelCollection * options () const;

        private:
            std::string mName;
            MessageFieldModelCollection mFields;
            OptionModelCollection mOptions;
        };
        
    } // namespace Protocol
    
} // namespace MuddledManaged

#endif // Protocol_OneofModel_h
