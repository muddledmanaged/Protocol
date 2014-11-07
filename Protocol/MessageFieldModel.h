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
#include "Packageable.h"

// Every model header includes its container header.
#include "MessageFieldModelContainer.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class ProtoModel;
        
        class MessageFieldModel : public Nameable, public Packageable, public OptionModelContainer
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
                unknown = 0,
                numericType = 1,
                stringType = 2,
                bytesType = 3,
                enumType = 4,
                messageType = 5
            };

            MessageFieldModel (Requiredness requiredness, const std::string & fieldType,
                               const std::string & name, unsigned int index);

            MessageFieldModel (const MessageFieldModel & src);

            Requiredness requiredness () const;

            std::string fieldType () const;

            std::string fieldTypeFull () const;

            FieldCategory fieldCategory () const;

            void updateFieldCategoryToEnum (const std::string & fullFieldType);
            void updateFieldCategoryToMessage (const std::string & fullFieldType);

            unsigned int index () const;

            MessageFieldModel & operator = (const MessageFieldModel & rhs);

        private:
            void setFieldCategoryAndFullType ();

            Requiredness mRequiredness;
            std::string mFieldType;
            std::string mFieldTypeFull;
            FieldCategory mFieldCategory;
            unsigned int mIndex;
        };

    } // namespace Protocol
    
} // namespace MuddledManaged

#endif // Protocol_MessageFieldModel_h
