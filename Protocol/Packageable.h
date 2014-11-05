//
//  Packageable.h
//  Protocol
//
//  Created by Wahid Tanner on 9/27/14.
//

#ifndef Protocol_Packageable_h
#define Protocol_Packageable_h

#include <string>

namespace MuddledManaged
{
    namespace Protocol
    {
        class Packageable
        {
        public:
            virtual ~Packageable ()
            { }

            virtual std::string package () const
            {
                return mPackage;
            }

            virtual void setPackage (const std::string & package)
            {
                mPackage = package;
            }

        protected:
            Packageable (const std::string & package = "")
            : mPackage(package)
            { }

            Packageable (const Packageable & src)
            : mPackage(src.mPackage)
            { }

            Packageable & operator = (const Packageable & rhs)
            {
                if (this == &rhs)
                {
                    return *this;
                }

                mPackage = rhs.mPackage;
                
                return *this;
            }

        private:
            std::string mPackage;
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_Packageable_h
