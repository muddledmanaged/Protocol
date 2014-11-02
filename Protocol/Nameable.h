//
//  Nameable.h
//  Protocol
//
//  Created by Wahid Tanner on 11/1/14.
//

#ifndef Protocol_Nameable_h
#define Protocol_Nameable_h

#include <locale>
#include <string>

namespace MuddledManaged
{
    namespace Protocol
    {
        class Nameable
        {
        public:
            virtual ~Nameable ()
            { }

            std::string name () const
            {
                return mNameCamel;
            }

            std::string namePascal () const
            {
                return mNamePascal;
            }

        protected:
            Nameable (const std::string & name = "")
            : mNameCamel(name), mNamePascal(name)
            {
                mNameCamel[0] = std::tolower(mNameCamel[0]);
                mNamePascal[0] = std::toupper(mNamePascal[0]);
            }

            Nameable (const Nameable & src)
            : mNameCamel(src.mNameCamel), mNamePascal(src.mNamePascal)
            { }

            Nameable & operator = (const Nameable & rhs)
            {
                if (this == &rhs)
                {
                    return *this;
                }

                mNameCamel = rhs.mNameCamel;
                mNamePascal = rhs.mNamePascal;

                return *this;
            }

        private:
            std::string mNameCamel;
            std::string mNamePascal;
        };

    } // namespace Protocol
    
} // namespace MuddledManaged

#endif // Protocol_Nameable_h
