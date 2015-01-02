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
            virtual void generateCode (const std::string & outputFolder, const ProtoModel * protoModel,
                                       const std::string & projectName, bool generateCommonCode) const;

        private:
            friend class CodeGeneratorManager;
            
            CodeGeneratorCPP ();

            void generateHeaderFile (const std::string & outputFolder, const ProtoModel & protoModel, const std::string & projectName) const;

            void generateHeaderFileCommon (const std::string & outputFolder, const std::string & projectName) const;

            void generateSourceFile (const std::string & outputFolder, const ProtoModel & protoModel, const std::string & projectName) const;

            std::string headerIncludeBlockText (const ProtoModel & protoModel, const std::string & projectName) const;

            std::string headerIncludeBlockText (const std::string & headerBaseName, const std::string & projectName) const;

            std::string fullTypeName (const MessageFieldModel & messageFieldModel) const;

            std::string fullTypeNameInternal (const MessageFieldModel & messageFieldModel) const;

            void writeStandardIncludeFileNamesToHeader (CodeWriter & headerFileWriter, bool includeBase) const;

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
                                                         const MessageFieldModel & messageFieldModel) const;

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

            void writeMessageDataFieldInitializationToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                              const MessageFieldModel & messageFieldModel, const std::string & className,
                                                              const std::string & fullScope) const;

            std::string messageFieldInitialization (const MessageFieldModel & messageFieldModel) const;

            void writeMessageDataDestructorToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                 const MessageModel & messageModel, const std::string & className,
                                                 const std::string & fullScope) const;

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

            void writeMessageByteSizeToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                               const MessageModel & messageModel, const std::string & className,
                                               const std::string & fullScope) const;

            void writeMessageValidToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                            const MessageModel & messageModel, const std::string & className,
                                            const std::string & fullScope) const;

            void writeMessageFieldToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                            const MessageFieldModel & messageFieldModel, const std::string & className,
                                            const std::string & fullScope) const;

            void writeOneofToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                     const OneofModel & oneofModel, const std::string & className,
                                     const std::string & fullScope) const;

            void writeMessageOneofClearToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                 const OneofModel & oneofModel, const std::string & className,
                                                 const std::string & fullScope) const;

            void writeMessageFieldSizeRepeatedToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                        const MessageFieldModel & messageFieldModel, const std::string & className,
                                                        const std::string & fullScope) const;

            void writeMessageFieldGetRepeatedToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                       const MessageFieldModel & messageFieldModel, const std::string & className,
                                                       const std::string & fullScope) const;

            void writeMessageFieldSetRepeatedToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                       const MessageFieldModel & messageFieldModel, const std::string & className,
                                                       const std::string & fullScope) const;

            void writeMessageFieldAddRepeatedToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                       const MessageFieldModel & messageFieldModel, const std::string & className,
                                                       const std::string & fullScope) const;

            void writeMessageFieldAddNewRepeatedToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                          const MessageFieldModel & messageFieldModel, const std::string & className,
                                                          const std::string & fullScope) const;

            void writeMessageFieldClearRepeatedToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                         const MessageFieldModel & messageFieldModel, const std::string & className,
                                                         const std::string & fullScope) const;

            void writeMessageFieldHasToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                               const MessageFieldModel & messageFieldModel, const std::string & className,
                                               const std::string & fullScope) const;

            void writeMessageFieldGetToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                               const MessageFieldModel & messageFieldModel, const std::string & className,
                                               const std::string & fullScope) const;

            void writeMessageFieldSetToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                               const MessageFieldModel & messageFieldModel, const std::string & className,
                                               const std::string & fullScope) const;

            void writeMessageFieldCreateNewToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                     const MessageFieldModel & messageFieldModel, const std::string & className,
                                                     const std::string & fullScope) const;

            void writeMessageFieldClearToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                 const MessageFieldModel & messageFieldModel, const std::string & className,
                                                 const std::string & fullScope) const;

            static const std::string mHeaderFileExtension;
            static const std::string mSourceFileExtension;
            static const std::string mGeneratedFileProlog;
            static const std::string mProtoBaseHeaderFileTemplate;
            static const std::string mBaseClassesNamespace;
            static const std::string mBaseClassesFileName;
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_CodeGeneratorCPP_h
