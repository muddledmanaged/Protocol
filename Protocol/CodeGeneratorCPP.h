//
//  CodeGeneratorCPP.h
//  Protocol
//
//  Created by Wahid Tanner on 10/17/14.
//

#ifndef Protocol_CodeGeneratorCPP_h
#define Protocol_CodeGeneratorCPP_h

#include "CodeGeneratorInterface.h"
#include "CodeWriterCPP.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class CodeGeneratorCPP : public CodeGeneratorInterface
        {
        public:
            CodeGeneratorCPP ();

            virtual void generateCode (const std::string & outputFolder, const ProtoModel & model);

        private:
            void writeProtoEnumsToHeader (CodeWriter & headerFileWriter, const ProtoModel & model);

            static const std::string mHeaderFileExtension;
            static const std::string mSourceFileExtension;
            static const std::string mHeaderFileProlog;
            static const std::string mSourceFileProlog;
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_CodeGeneratorCPP_h
