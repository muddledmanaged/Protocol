//
//  Nestable.h
//  Protocol
//
//  Created by Wahid Tanner on 11/8/14.
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

            virtual Nestable * parent () const
            {
                return mParent;
            }

            virtual void setParent (Nestable * parent)
            {
                mParent = parent;
            }

            virtual std::string nameFull () const
            {
                std::string messagePath;
                Nestable * pParentMessage = parent();
                while (pParentMessage != nullptr)
                {
                    if (messagePath.empty())
                    {
                        messagePath = pParentMessage->namePascal();
                    }
                    else
                    {
                        messagePath = pParentMessage->namePascal() + "." + messagePath;
                    }
                    pParentMessage = pParentMessage->parent();
                }

                std::string fullName = package();
                if (!fullName.empty() && !messagePath.empty())
                {
                    fullName += ".";
                }
                fullName += messagePath;
                if (!fullName.empty())
                {
                    fullName += ".";
                }
                fullName += namePascal();
                
                return fullName;
            }

        protected:
            Nestable (const std::string & name = "", const std::string & package = "")
            : Nameable(name), Packageable(package), mParent(nullptr)
            { }

            Nestable (const Nestable & src)
            : Nameable(src), Packageable(src), mParent(src.mParent)
            { }

            Nestable & operator = (const Nestable & rhs)
            {
                if (this == &rhs)
                {
                    return *this;
                }

                Nameable::operator=(rhs);
                Packageable::operator=(rhs);

                mParent = rhs.mParent;

                return *this;
            }

        private:
            Nestable * mParent;
        };
        
    } // namespace Protocol
    
} // namespace MuddledManaged

#endif // Protocol_Nestable_h
