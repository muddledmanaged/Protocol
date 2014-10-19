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
#include <unordered_set>

#include "TokenReader.h"
#include "Packageable.h"
#include "EnumModel.h"
#include "EnumValueModel.h"
#include "MessageModel.h"
#include "MessageFieldModel.h"
#include "OptionModel.h"
#include "OptionModelContainer.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class ProtoModel : private Packageable, public OptionModelContainer
        {
        public:
            typedef MessageModel::MessageFieldModelCollection MessageFieldModelCollection;
            typedef EnumModel::EnumValueModelCollection EnumValueModelCollection;
            typedef MessageModel::OneofModelCollection OneofModelCollection;
            typedef std::vector<std::shared_ptr<EnumModel>> EnumModelCollection;
            typedef std::vector<std::shared_ptr<MessageModel>> MessageModelCollection;
            typedef std::unordered_set<std::string> NamedTypeCollection;

            explicit ProtoModel (const std::string & fileName);

            ProtoModel (const ProtoModel & src);

            std::string fileName () const;

            std::string currentNestedType () const;

            std::string currentPackage () const;
            void setCurrentPackage (const std::string & package);

            void addField (TokenReader::iterator current, MessageFieldModelCollection::value_type & field);
            void completeField ();

            void addEnum (TokenReader::iterator current, EnumModelCollection::value_type & enumeration);
            void completeEnum ();

            void addEnumValue (TokenReader::iterator current, EnumValueModelCollection::value_type & value);
            void completeEnumValue ();

            void addMessage (TokenReader::iterator current, MessageModelCollection::value_type & message);
            void completeMessage ();

            void addOneof (TokenReader::iterator current, OneofModelCollection::value_type & oneof);
            void completeOneof ();

            virtual void addOption (TokenReader::iterator current, const OptionModelCollection::value_type & option);

            void addPrivateEnumType (TokenReader::iterator current, const std::string & namedType);

            void addPublicEnumType (TokenReader::iterator current, const std::string & namedType);

            void addPrivateMessageType (TokenReader::iterator current, const std::string & namedType);

            void addPublicMessageType (TokenReader::iterator current, const std::string & namedType);

            const EnumModelCollection * enums () const;

            const MessageModelCollection * messages () const;

            const NamedTypeCollection * privateEnumTypes () const;

            const NamedTypeCollection * publicEnumTypes () const;

            const NamedTypeCollection * privateMessageTypes () const;

            const NamedTypeCollection * publicMessageTypes () const;

            ProtoModel & operator = (const ProtoModel & rhs);

        private:
            bool typeExists (std::string namedType) const;
            void updateCurrentNestedType ();

            std::string mFileName;
            std::string mCurrentNestedType;
            EnumModelCollection mEnums;
            MessageModelCollection mMessages;
            MessageModelCollection mMessageQueue;
            MessageFieldModelCollection::value_type mCurrentField;
            OneofModelCollection::value_type mCurrentOneof;
            EnumModelCollection::value_type mCurrentEnum;
            EnumValueModelCollection::value_type mCurrentEnumValue;
            NamedTypeCollection mPrivateEnumTypes;
            NamedTypeCollection mPublicEnumTypes;
            NamedTypeCollection mPrivateMessageTypes;
            NamedTypeCollection mPublicMessageTypes;
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_ProtoModel_h
