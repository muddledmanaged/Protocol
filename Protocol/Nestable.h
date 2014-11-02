//
//  Nestable.h
//  Protocol
//
//  Created by Wahid Tanner on 10/12/14.
//

#ifndef Protocol_Nestable_h
#define Protocol_Nestable_h

#include <string>

#include "Nameable.h"
#include "Packageable.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class Nestable : public Nameable, public Packageable
        {
        public:
            virtual ~Nestable ()
            { }

            std::string parentTypes () const
            {
                return mParentTypes;
            }

            std::string fullName () const
            {
                std::string fullName = package();
                if (!fullName.empty())
                {
                    fullName += ".";
                }

                fullName += parentTypes();
                if (!parentTypes().empty())
                {
                    fullName += ".";
                }
                fullName += name();

                return fullName;
            }

        protected:
            Nestable (const std::string & name, const std::string & package = "", const std::string & namedTypes = "")
            : Nameable(name), Packageable(package), mParentTypes(namedTypes)
            { }

            Nestable (const Nestable & src)
            : Nameable(src), Packageable(src), mParentTypes(src.mParentTypes)
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

                Nameable::operator=(rhs);
                Packageable::operator=(rhs);

                mParentTypes = rhs.mParentTypes;

                return *this;
            }

        private:
            std::string mParentTypes;
        };

    } // namespace Protocol
    
} // namespace MuddledManaged

#endif // Protocol_Nestable_h
