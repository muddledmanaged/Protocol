//
//  EnumModelContainer.h
//  Protocol
//
//  Created by Wahid Tanner on 10/20/14.
//

#ifndef Protocol_EnumModelContainer_h
#define Protocol_EnumModelContainer_h

#include <memory>
#include <vector>

#include "EnumModel.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class EnumModelContainer
        {
        public:
            typedef std::vector<std::shared_ptr<EnumModel>> EnumModelCollection;
            typedef std::shared_ptr<EnumModelCollection> SPEnumModelCollection;

            virtual ~EnumModelContainer ()
            { }

            virtual void addEnum (const EnumModelCollection::value_type & enumeration)
            {
                mEnums->push_back(enumeration);
            }

            virtual const SPEnumModelCollection enums () const
            {
                return mEnums;
            }

        protected:
            EnumModelContainer ()
            : mEnums(new EnumModelCollection())
            { }

            EnumModelContainer (const EnumModelContainer & src)
            : mEnums(src.mEnums)
            { }

            EnumModelContainer & operator = (const EnumModelContainer & rhs)
            {
                if (this == &rhs)
                {
                    return *this;
                }

                mEnums = rhs.mEnums;

                return *this;
            }

        private:
            SPEnumModelCollection mEnums;
        };

    } // namespace Protocol
    
} // namespace MuddledManaged

#endif // Protocol_EnumModelContainer_h
