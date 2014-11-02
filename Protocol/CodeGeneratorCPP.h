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
#include "MessageModel.h"
#include "MessageFieldModel.h"
#include "OneofModel.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class CodeGeneratorCPP : public CodeGeneratorInterface
        {
        public:
            virtual void generateCode (const std::string & outputFolder, const ProtoModel & protoModel, const std::string & projectName) const;

        private:
            friend class CodeGeneratorManager;
            
            CodeGeneratorCPP ();

            std::string headerIncludeBlockText (const ProtoModel & protoModel, const std::string & projectName) const;

            std::string fullTypeName (const ProtoModel & protoModel, const std::string & protoTypeName) const;

            void writeStandardIncludeFileNamesToHeader (CodeWriter & headerFileWriter) const;

            void writeIncludedProtoFileNamesToHeader (CodeWriter & headerFileWriter, const ProtoModel & protoModel) const;

            void writeProtoEnumsToHeader (CodeWriter & headerFileWriter, const ProtoModel & protoModel) const;

            void writeProtoMessagesToHeader (CodeWriter & headerFileWriter, const ProtoModel & protoModel) const;

            void writeMessageToHeader (CodeWriter & headerFileWriter, const ProtoModel & protoModel,
                                       const MessageModel & messageModel, const std::string & className) const;

            void writeMessageFieldToHeader (CodeWriter & headerFileWriter, const ProtoModel & protoModel,
                                            const MessageFieldModel & messageFieldModel) const;

            void writeMessageFieldBackingFieldsToHeader (CodeWriter & headerFileWriter, const ProtoModel & protoModel,
                                                         const MessageFieldModel & messageFieldModel, bool writeSetFlag) const;

            void writeMessageFieldIndexToHeader (CodeWriter & headerFileWriter,
                                                 const MessageFieldModel & messageFieldModel) const;

            void writeOneofToHeader (CodeWriter & headerFileWriter, const ProtoModel & protoModel,
                                            const OneofModel & oneofModel) const;

            void writeOneofBackingFieldsToHeader (CodeWriter & headerFileWriter, const ProtoModel & protoModel,
                                                  const OneofModel & oneofModel) const;

            void writeMessageFieldIndexesToHeader (CodeWriter & headerFileWriter,
                                                 const OneofModel & oneofModel) const;

            static const std::string mHeaderFileExtension;
            static const std::string mSourceFileExtension;
            static const std::string mHeaderFileProlog;
            static const std::string mSourceFileProlog;
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_CodeGeneratorCPP_h
