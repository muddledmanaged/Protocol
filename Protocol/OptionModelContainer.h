//
//  OptionModelContainer.h
//  Protocol
//
//  Created by Wahid Tanner on 10/19/14.
//

#ifndef Protocol_OptionModelContainer_h
#define Protocol_OptionModelContainer_h

#include <string>

namespace MuddledManaged
{
    namespace Protocol
    {
        class OptionModelContainer
        {
        public:
            typedef std::vector<std::shared_ptr<OptionModel>> OptionModelCollection;

            virtual ~OptionModelContainer ()
            { }

            virtual void addOption (const OptionModelCollection::value_type & option)
            {
                mOptions.push_back(option);
            }

            virtual OptionModelCollection options () const
            {
                return mOptions;
            }

        protected:
            OptionModelContainer ()
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
            OptionModelCollection mOptions;
        };

    } // namespace Protocol
    
} // namespace MuddledManaged

#endif // Protocol_OptionModelContainer_h
