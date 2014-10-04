//
//  ProtoModel.h
//  Protocol
//
//  Created by Wahid Tanner on 9/16/14.
//

#ifndef Protocol_ProtoModel_h
#define Protocol_ProtoModel_h

#include <memory>
#include <string>
#include <vector>

#include "TokenReader.h"
#include "Packageable.h"
#include "EnumModel.h"
#include "MessageModel.h"
#include "MessageFieldModel.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class ProtoModel : private Packageable
        {
        public:
            typedef MessageModel::MessageFieldModelCollection MessageFieldModelCollection;
            typedef std::vector<std::shared_ptr<EnumModel>> EnumModelCollection;
            typedef std::vector<std::shared_ptr<MessageModel>> MessageModelCollection;

            ProtoModel ();

            std::string currentPackage () const;
            void setCurrentPackage (const std::string & package);

            void addField (TokenReader::iterator current, MessageFieldModelCollection::value_type field);

            void addEnum (TokenReader::iterator current, EnumModelCollection::value_type enumeration);
            void completeEnum ();

            void addMessage (TokenReader::iterator current, MessageModelCollection::value_type message);
            void completeMessage ();

            const EnumModelCollection * enums () const;

            const MessageModelCollection * messages () const;

        private:
            EnumModelCollection mEnums;
            MessageModelCollection mMessages;
            MessageModelCollection mMessageQueue;
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_ProtoModel_h
