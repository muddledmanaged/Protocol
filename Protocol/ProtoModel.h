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
#include "EnumValueModel.h"
#include "MessageModel.h"
#include "MessageFieldModel.h"
#include "OptionModel.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class ProtoModel : private Packageable
        {
        public:
            typedef MessageModel::MessageFieldModelCollection MessageFieldModelCollection;
            typedef EnumModel::EnumValueModelCollection EnumValueModelCollection;
            typedef MessageModel::OneofModelCollection OneofModelCollection;
            typedef std::vector<std::shared_ptr<EnumModel>> EnumModelCollection;
            typedef std::vector<std::shared_ptr<MessageModel>> MessageModelCollection;
            typedef std::vector<std::shared_ptr<OptionModel>> OptionModelCollection;

            ProtoModel ();

            std::string currentPackage () const;
            void setCurrentPackage (const std::string & package);
            void addToCurrentPackage (const std::string & additionalPackage);

            void addField (TokenReader::iterator current, MessageFieldModelCollection::value_type field);
            void completeField ();

            void addEnum (TokenReader::iterator current, EnumModelCollection::value_type enumeration);
            void completeEnum ();

            void addEnumValue (TokenReader::iterator current, EnumValueModelCollection::value_type value);
            void completeEnumValue ();

            void addMessage (TokenReader::iterator current, MessageModelCollection::value_type message);
            void completeMessage ();

            void addOneof (TokenReader::iterator current, OneofModelCollection::value_type oneof);
            void completeOneof ();

            void addOption (TokenReader::iterator current, OptionModelCollection::value_type option);

            const EnumModelCollection * enums () const;

            const MessageModelCollection * messages () const;

            const OptionModelCollection * options () const;

        private:
            EnumModelCollection mEnums;
            MessageModelCollection mMessages;
            OptionModelCollection mOptions;
            MessageModelCollection mMessageQueue;
            MessageFieldModelCollection::value_type mCurrentField;
            OneofModelCollection::value_type mCurrentOneof;
            EnumModelCollection::value_type mCurrentEnum;
            EnumValueModelCollection::value_type mCurrentEnumValue;
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_ProtoModel_h
