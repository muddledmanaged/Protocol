//
//  Nestable.h
//  Protocol
//
//  Created by Wahid Tanner on 10/12/14.
//

#ifndef Protocol_Nestable_h
#define Protocol_Nestable_h

#include <string>

namespace MuddledManaged
{
    namespace Protocol
    {
        class Nestable
        {
        public:
            virtual ~Nestable ()
            { }

            std::string parentTypes () const
            {
                return mParentTypes;
            }

        protected:
            Nestable (const std::string & namedTypes = "")
            : mParentTypes(namedTypes)
            { }

            Nestable (const Nestable & src)
            : mParentTypes(src.mParentTypes)
            { }

            void setParentTypes (const std::string & namedTypes)
            {
                mParentTypes = namedTypes;
            }

            Nestable & operator = (const Nestable & rhs)
            {
                if (this == &rhs)
                {
                    return *this;
                }

                mParentTypes = rhs.mParentTypes;

                return *this;
            }

        private:
            std::string mParentTypes;
        };

    } // namespace Protocol
    
} // namespace MuddledManaged

#endif // Protocol_Nestable_h
