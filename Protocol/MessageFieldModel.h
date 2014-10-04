//
//  MessageFieldModel.h
//  Protocol
//
//  Created by Wahid Tanner on 10/3/14.
//

#ifndef Protocol_MessageFieldModel_h
#define Protocol_MessageFieldModel_h

#include <string>

namespace MuddledManaged
{
    namespace Protocol
    {
        class MessageFieldModel
        {
        public:
            enum class Requiredness
            {
                required = 0,
                optional = 1,
                repeated = 2
            };

            MessageFieldModel (Requiredness requiredness, const std::string & fieldType, const std::string & name, unsigned int index);

            Requiredness requiredness () const;

            std::string fieldType () const;

            std::string name () const;

            unsigned int index () const;

        private:
            Requiredness mRequiredness;
            std::string mFieldType;
            std::string mName;
            unsigned int mIndex;
        };

    } // namespace Protocol
    
} // namespace MuddledManaged

#endif // Protocol_MessageFieldModel_h
