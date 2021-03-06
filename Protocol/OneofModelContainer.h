//
//  OneofModelContainer.h
//  Protocol
//
//  Created by Wahid Tanner on 10/24/14.
//

#ifndef Protocol_OneofModelContainer_h
#define Protocol_OneofModelContainer_h

#include <memory>
#include <vector>

namespace MuddledManaged
{
    namespace Protocol
    {
        // The container classes really only need to know that the contained class exists.
        class OneofModel;

        class OneofModelContainer
        {
        public:
            typedef std::vector<std::shared_ptr<OneofModel>> OneofModelCollection;
            typedef std::shared_ptr<OneofModelCollection> SPOneofModelCollection;

            virtual ~OneofModelContainer ()
            { }

            virtual void addOneof (const OneofModelCollection::value_type & oneof)
            {
                mOneofs->push_back(oneof);
            }

            virtual const SPOneofModelCollection oneofs () const
            {
                return mOneofs;
            }

        protected:
            OneofModelContainer ()
            : mOneofs(new OneofModelCollection())
            { }

            OneofModelContainer (const OneofModelContainer & src)
            : mOneofs(src.mOneofs)
            { }

            OneofModelContainer & operator = (const OneofModelContainer & rhs)
            {
                if (this == &rhs)
                {
                    return *this;
                }

                mOneofs = rhs.mOneofs;

                return *this;
            }

        private:
            SPOneofModelCollection mOneofs;
        };
        
    } // namespace Protocol
    
} // namespace MuddledManaged

#endif // Protocol_OneofModelContainer_h
