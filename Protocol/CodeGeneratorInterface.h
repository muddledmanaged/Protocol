//
//  CodeGeneratorInterface.h
//  Protocol
//
//  Created by Wahid Tanner on 10/16/14.
//

#ifndef Protocol_CodeGeneratorInterface_h
#define Protocol_CodeGeneratorInterface_h

#include <memory>
#include <string>

#include "ProtoModel.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class CodeGeneratorInterface
        {
        public:
            virtual ~CodeGeneratorInterface ()
            { }

            virtual void generateCode (const std::string & outputFolder, const ProtoModel & model) = 0;

        protected:
            CodeGeneratorInterface ()
            { }

        private:
            CodeGeneratorInterface (const CodeGeneratorInterface & src) = delete;
            CodeGeneratorInterface & operator = (const CodeGeneratorInterface & rhs) = delete;
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_CodeGeneratorInterface_h
