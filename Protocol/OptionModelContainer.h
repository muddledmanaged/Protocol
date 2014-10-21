//
//  OptionModelContainer.h
//  Protocol
//
//  Created by Wahid Tanner on 10/19/14.
//

#ifndef Protocol_OptionModelContainer_h
#define Protocol_OptionModelContainer_h

#include <memory>
#include <vector>

#include "OptionModel.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class OptionModelContainer
        {
        public:
            typedef std::vector<std::shared_ptr<OptionModel>> OptionModelCollection;
            typedef std::shared_ptr<OptionModelCollection> SPOptionModelCollection;

            virtual ~OptionModelContainer ()
            { }

            virtual void addOption (const OptionModelCollection::value_type & option)
            {
                mOptions->push_back(option);
            }

            virtual const SPOptionModelCollection options () const
            {
                return mOptions;
            }

        protected:
            OptionModelContainer ()
            : mOptions(new OptionModelCollection())
            { }

            OptionModelContainer (const OptionModelContainer & src)
            : mOptions(src.mOptions)
            { }

            OptionModelContainer & operator = (const OptionModelContainer & rhs)
            {
                if (this == &rhs)
                {
                    return *this;
                }

                mOptions = rhs.mOptions;

                return *this;
            }

        private:
            SPOptionModelCollection mOptions;
        };

    } // namespace Protocol
    
} // namespace MuddledManaged

#endif // Protocol_OptionModelContainer_h
