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

namespace MuddledManaged
{
    namespace Protocol
    {
        // The container classes really only need to know that the contained class exists.
        class MessageFieldModel;

        class MessageFieldModelContainer
        {
        public:
            typedef std::vector<std::shared_ptr<MessageFieldModel>> MessageFieldModelCollection;
            typedef std::shared_ptr<MessageFieldModelCollection> SPMessageFieldModelCollection;

            virtual ~MessageFieldModelContainer ()
            { }

            virtual void addField (const MessageFieldModelCollection::value_type & field)
            {
                mFields->push_back(field);
            }

            virtual const SPMessageFieldModelCollection fields () const
            {
                return mFields;
            }

        protected:
            MessageFieldModelContainer ()
            : mFields(new MessageFieldModelCollection())
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
            SPMessageFieldModelCollection mFields;
        };
        
    } // namespace Protocol
    
} // namespace MuddledManaged

#endif // Protocol_MessageFieldModelContainer_h
