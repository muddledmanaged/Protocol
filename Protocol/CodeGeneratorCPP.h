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

            void generateHeaderFile (const std::string & outputFolder, const ProtoModel & protoModel, const std::string & projectName) const;

            void generateSourceFile (const std::string & outputFolder, const ProtoModel & protoModel, const std::string & projectName) const;

            std::string headerIncludeBlockText (const ProtoModel & protoModel, const std::string & projectName) const;

            std::string fullTypeName (const MessageFieldModel & messageFieldModel) const;

            void writeStandardIncludeFileNamesToHeader (CodeWriter & headerFileWriter) const;

            void writeIncludedProtoFileNamesToHeader (CodeWriter & headerFileWriter, const ProtoModel & protoModel) const;

            void writeProtoEnumsToHeader (CodeWriter & headerFileWriter, const ProtoModel & protoModel) const;

            void writeEnumToHeader (CodeWriter & headerFileWriter, const ProtoModel & protoModel,
                                       const EnumModel & enumModel, const std::string & enumName) const;

            void writeProtoMessagesToHeader (CodeWriter & headerFileWriter, const ProtoModel & protoModel) const;

            void writeMessageDeclarationToHeader (CodeWriter & headerFileWriter, const ProtoModel & protoModel,
                                                  const MessageModel & messageModel, const std::string & className) const;

            void writeMessageEnumToHeader (CodeWriter & headerFileWriter, const ProtoModel & protoModel,
                                           const MessageModel & messageModel, const std::string & className) const;

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

            void writeProtoMessagesToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel) const;

            void writeMessageToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                       const MessageModel & messageModel, const std::string & className) const;

            void writeMessageDataConstructorToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                  const MessageModel & messageModel, const std::string & className,
                                                  const std::string & fullScope) const;

            void writeMessageDataDestructorToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                 const MessageModel & messageModel, const std::string & className,
                                                 const std::string & fullScope) const;

            void writeMessageFieldConstructionToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                        const MessageFieldModel & messageFieldModel, bool writeSetFlag) const;

            void writeMessageFieldDestructionToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                       const MessageFieldModel & messageFieldModel) const;

            void writeMessageConstructorToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                  const MessageModel & messageModel, const std::string & className,
                                                  const std::string & fullScope) const;

            void writeMessageCopyConstructorToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                      const MessageModel & messageModel, const std::string & className,
                                                      const std::string & fullScope) const;

            void writeMessageDestructorToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                 const MessageModel & messageModel, const std::string & className,
                                                 const std::string & fullScope) const;

            void writeMessageAssignmentOperatorToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                         const MessageModel & messageModel, const std::string & className,
                                                         const std::string & fullScope) const;

            void writeMessageSwapToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                           const MessageModel & messageModel, const std::string & className,
                                           const std::string & fullScope) const;

            void writeMessageClearToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                            const MessageModel & messageModel, const std::string & className,
                                            const std::string & fullScope) const;

            void writeMessageParseToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                            const MessageModel & messageModel, const std::string & className,
                                            const std::string & fullScope) const;

            void writeMessageSerializeToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                const MessageModel & messageModel, const std::string & className,
                                                const std::string & fullScope) const;

            void writeMessageSizeToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                           const MessageModel & messageModel, const std::string & className,
                                           const std::string & fullScope) const;

            void writeMessageIsValidToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                              const MessageModel & messageModel, const std::string & className,
                                              const std::string & fullScope) const;

            static const std::string mHeaderFileExtension;
            static const std::string mSourceFileExtension;
            static const std::string mHeaderFileProlog;
            static const std::string mSourceFileProlog;
            static const std::string mBaseClassesSourceFileName;
            static const std::string mBaseClassesDestinationFileName;
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_CodeGeneratorCPP_h
