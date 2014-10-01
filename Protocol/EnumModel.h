//
//  EnumModel.h
//  Protocol
//
//  Created by Wahid Tanner on 9/30/14.
//

#ifndef Protocol_EnumModel_h
#define Protocol_EnumModel_h

#include <memory>
#include <string>
#include <vector>

#include "Packageable.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class EnumModel : public Packageable
        {
        public:
            explicit EnumModel (const std::string & name, const std::string & package = "");

            std::string name () const;

        private:
            std::string mName;
        };

    } // namespace Protocol
    
} // namespace MuddledManaged

#endif // Protocol_EnumModel_h
