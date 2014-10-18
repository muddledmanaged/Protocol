//
//  CodeGeneratorCPP.h
//  Protocol
//
//  Created by Wahid Tanner on 10/17/14.
//

#ifndef Protocol_CodeGeneratorCPP_h
#define Protocol_CodeGeneratorCPP_h

#include "CodeGeneratorInterface.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class CodeGeneratorCPP : public CodeGeneratorInterface
        {
        public:
            CodeGeneratorCPP ();

            virtual void generateCode (const std::string & outputFolder, const ProtoModel & model);
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_CodeGeneratorCPP_h
