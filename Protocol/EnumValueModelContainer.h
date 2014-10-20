//
//  EnumValueModelContainer.h
//  Protocol
//
//  Created by Wahid Tanner on 10/19/14.
//

#ifndef Protocol_EnumValueModelContainer_h
#define Protocol_EnumValueModelContainer_h

#include <memory>
#include <vector>

#include "EnumValueModel.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class EnumValueModelContainer
        {
        public:
            typedef std::vector<std::shared_ptr<EnumValueModel>> EnumValueModelCollection;

            virtual ~EnumValueModelContainer ()
            { }

            virtual void addEnumValue (const EnumValueModelCollection::value_type & enumValue)
            {
                mValues.push_back(enumValue);
            }

            virtual EnumValueModelCollection enumValues () const
            {
                return mValues;
            }

        protected:
            EnumValueModelContainer ()
            { }

            EnumValueModelContainer (const EnumValueModelContainer & src)
            : mValues(src.mValues)
            { }

            EnumValueModelContainer & operator = (const EnumValueModelContainer & rhs)
            {
                if (this == &rhs)
                {
                    return *this;
                }

                mValues = rhs.mValues;

                return *this;
            }

        private:
            EnumValueModelCollection mValues;
        };
        
    } // namespace Protocol
    
} // namespace MuddledManaged

#endif // Protocol_EnumValueModelContainer_h
