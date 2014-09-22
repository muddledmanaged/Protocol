//
//  ProtoModel.h
//  Protocol
//
//  Created by Wahid Tanner on 9/16/14.
//

#ifndef Protocol_ProtoModel_h
#define Protocol_ProtoModel_h

#include <string>

namespace MuddledManaged
{
    namespace Protocol
    {
        class ProtoModel
        {
        public:
            ProtoModel ();

            std::string package () const;
            void setPackage (const std::string & package);

        private:
            std::string mPackage;
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_ProtoModel_h
