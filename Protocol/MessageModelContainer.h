//
//  MessageModelContainer.h
//  Protocol
//
//  Created by Wahid Tanner on 10/22/14.
//

#ifndef Protocol_MessageModelContainer_h
#define Protocol_MessageModelContainer_h

#include <memory>
#include <vector>

#include "MessageModel.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        // Since messages can contain messages, the message model class needs to be declared.
        class MessageModel;

        class MessageModelContainer
        {
        public:
            typedef std::vector<std::shared_ptr<MessageModel>> MessageModelCollection;
            typedef std::shared_ptr<MessageModelCollection> SPMessageModelCollection;

            virtual ~MessageModelContainer ()
            { }

            virtual void addMessage (const MessageModelCollection::value_type & message)
            {
                mMessages->push_back(message);
            }

            virtual const SPMessageModelCollection messages () const
            {
                return mMessages;
            }

        protected:
            MessageModelContainer ()
            : mMessages(new MessageModelCollection())
            { }

            MessageModelContainer (const MessageModelContainer & src)
            : mMessages(src.mMessages)
            { }

            MessageModelContainer & operator = (const MessageModelContainer & rhs)
            {
                if (this == &rhs)
                {
                    return *this;
                }

                mMessages = rhs.mMessages;

                return *this;
            }

        private:
            SPMessageModelCollection mMessages;
        };

    } // namespace Protocol
    
} // namespace MuddledManaged

#endif // Protocol_MessageModelContainer_h
