//
//  MessageFieldModel.h
//  Protocol
//
//  Created by Wahid Tanner on 10/3/14.
//

#ifndef Protocol_MessageFieldModel_h
#define Protocol_MessageFieldModel_h

#include <string>

#include "Nameable.h"
#include "OptionModel.h"

// Every model header includes its container header.
#include "MessageFieldModelContainer.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class ProtoModel;
        
        class MessageFieldModel : public Nameable, public OptionModelContainer
        {
        public:
            enum class Requiredness
            {
                required = 0,
                optional = 1,
                repeated = 2
            };

            enum class FieldCategory
            {
                numericType = 0,
                stringType = 1,
                bytesType = 2,
                enumType = 3,
                messageType = 4
            };

            MessageFieldModel (Requiredness requiredness, const std::string & fieldType, FieldCategory fieldCategory,
                               const std::string & name, unsigned int index);

            MessageFieldModel (const MessageFieldModel & src);

            Requiredness requiredness () const;

            std::string fieldType () const;

            FieldCategory fieldCategory () const;

            unsigned int index () const;

            MessageFieldModel & operator = (const MessageFieldModel & rhs);

            static FieldCategory fieldCategoryFromType (const std::string & fieldType, const ProtoModel * protoModel);

        private:
            Requiredness mRequiredness;
            std::string mFieldType;
            FieldCategory mFieldCategory;
            unsigned int mIndex;
        };

    } // namespace Protocol
    
} // namespace MuddledManaged

#endif // Protocol_MessageFieldModel_h
