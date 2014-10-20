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
#include "OptionModelContainer.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class OneofModel : public OptionModelContainer
        {
        public:
            typedef std::vector<std::shared_ptr<MessageFieldModel>> MessageFieldModelCollection;

            explicit OneofModel (const std::string & name);

            OneofModel (const OneofModel & src);

            std::string name () const;

            void addField (MessageFieldModelCollection::value_type & field);

            const MessageFieldModelCollection * fields () const;

            OneofModel & operator = (const OneofModel & rhs);

        private:
            std::string mName;
            MessageFieldModelCollection mFields;
        };
        
    } // namespace Protocol
    
} // namespace MuddledManaged

#endif // Protocol_OneofModel_h
