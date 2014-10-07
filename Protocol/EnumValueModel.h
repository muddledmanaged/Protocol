//
//  EnumValueModel.h
//  Protocol
//
//  Created by Wahid Tanner on 10/6/14.
//

#ifndef Protocol_EnumValueModel_h
#define Protocol_EnumValueModel_h

#include <string>

namespace MuddledManaged
{
    namespace Protocol
    {
        class EnumValueModel
        {
        public:
            EnumValueModel (const std::string & name, unsigned int value);

            std::string name () const;

            unsigned int value () const;

        private:
            std::string mName;
            unsigned int mValue;
        };

    } // namespace Protocol
    
} // namespace MuddledManaged

#endif // Protocol_EnumValueModel_h
