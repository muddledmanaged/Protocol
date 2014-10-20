//
//  MessageFieldModelContainer.h
//  Protocol
//
//  Created by Wahid Tanner on 10/19/14.
//

#ifndef Protocol_MessageFieldModelContainer_h
#define Protocol_MessageFieldModelContainer_h

#include <memory>
#include <vector>

#include "MessageFieldModel.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class MessageFieldModelContainer
        {
        public:
            typedef std::vector<std::shared_ptr<MessageFieldModel>> MessageFieldModelCollection;

            virtual ~MessageFieldModelContainer ()
            { }

            virtual void addField (const MessageFieldModelCollection::value_type & field)
            {
                mFields.push_back(field);
            }

            virtual MessageFieldModelCollection fields () const
            {
                return mFields;
            }

        protected:
            MessageFieldModelContainer ()
            { }

            MessageFieldModelContainer (const MessageFieldModelContainer & src)
            : mFields(src.mFields)
            { }

            MessageFieldModelContainer & operator = (const MessageFieldModelContainer & rhs)
            {
                if (this == &rhs)
                {
                    return *this;
                }

                mFields = rhs.mFields;

                return *this;
            }

        private:
            MessageFieldModelCollection mFields;
        };
        
    } // namespace Protocol
    
} // namespace MuddledManaged

#endif // Protocol_MessageFieldModelContainer_h
