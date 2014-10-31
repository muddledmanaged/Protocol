//
//  CodeWriter.h
//  Protocol
//
//  Created by Wahid Tanner on 10/26/14.
//

#ifndef Protocol_CodeWriter_h
#define Protocol_CodeWriter_h

#include <fstream>
#include <string>
#include <memory>
#include <vector>

#include "CodeIndenter.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class CodeWriter
        {
        public:
            CodeWriter (std::ofstream & stream)
            : mStream(stream)
            { }

            void writeCurlyBraceOpening ()
            {
                mStream << mIndenter.prefix() << "{" << std::endl;
                ++mIndenter;
            }

            void writeCurlyBraceClosing ()
            {
                --mIndenter;
                mStream << mIndenter.prefix() << "}" << std::endl;
            }

            void writeLine (const std::string & text)
            {
                mStream << text << std::endl;
            }

            void writeBlankLine ()
            {
                mStream << std::endl;
            }

            void writeLineIndented (const std::string & text)
            {
                mStream << mIndenter.prefix() << text << std::endl;
            }

            void writeLineComment (const std::string & comment)
            {
                mStream << "// " << comment << std::endl;
            }

            void writeLineCommentIndented (const std::string & comment)
            {
                mStream << mIndenter.prefix() << "// " << comment << std::endl;
            }

            void writeIfDef (const std::string & text)
            {
                mStream << "#ifdef " << text << std::endl;
            }

            void writeIfNotDef (const std::string & text)
            {
                mStream << "#ifndef " << text << std::endl;
            }

            void writeDefine (const std::string & text)
            {
                mStream << "#define " << text << std::endl;
            }

            void writeEndIf ()
            {
                mStream << "#endif" << std::endl;
            }

            void writeHeaderIncludeBlockOpening (const std::string & text)
            {
                writeIfNotDef(text);
                writeDefine(text);
                
                mStream << std::endl;
            }

            void writeHeaderIncludeBlockClosing ()
            {
                writeEndIf();
            }

            void writeIncludeLibrary (const std::string & fileName)
            {
                mStream << "#include <" << fileName << ">" << std::endl;
            }

            void writeIncludeProject (const std::string & fileName)
            {
                mStream << "#include \"" << fileName << "\"" << std::endl;
            }

            void writeNamespaceOpening (const std::string & namespaceName)
            {
                mStream << mIndenter.prefix() << "namespace " << namespaceName << std::endl;
                writeCurlyBraceOpening();
            }

            void writeNamespaceClosing ()
            {
                --mIndenter;
                mStream << mIndenter.prefix() << "} // namespace" << std::endl << std::endl;
            }

            void writeUsingNamespace (const std::string & namespaceName)
            {
                mStream << "using namespace " << namespaceName << ";" << std::endl;
            }

            void writeEnumOpening (const std::string & enumName)
            {
                mStream << mIndenter.prefix() << "enum class " << enumName << std::endl;
                writeCurlyBraceOpening();
            }

            void writeEnumClosing ()
            {
                --mIndenter;
                mStream << std::endl << mIndenter.prefix() << "};" << std::endl << std::endl;
            }

            void writeEnumValueFirst (const std::string & valueName, unsigned int valueValue)
            {
                mStream << mIndenter.prefix() << valueName << " = " << valueValue;
            }

            void writeEnumValueSubsequent (const std::string & valueName, unsigned int valueValue)
            {
                mStream << "," << std::endl << mIndenter.prefix() << valueName << " = " << valueValue;
            }

            void writeClassOpening (const std::string & className)
            {
                mStream << mIndenter.prefix() << "class " << className << std::endl;
                writeCurlyBraceOpening();
            }

            void writeClassClosing ()
            {
                --mIndenter;
                mStream << mIndenter.prefix() << "};" << std::endl << std::endl;
            }

            void writeClassPublic ()
            {
                --mIndenter;
                mStream << mIndenter.prefix() << "public:" << std::endl;
                ++mIndenter;
            }

            void writeClassProtected ()
            {
                --mIndenter;
                mStream << mIndenter.prefix() << "protected:" << std::endl;
                ++mIndenter;
            }

            void writeClassPrivate ()
            {
                --mIndenter;
                mStream << mIndenter.prefix() << "private:" << std::endl;
                ++mIndenter;
            }

            void writeClassFieldDeclaration (const std::string & fieldName,
                                             const std::string & fieldType,
                                             bool isStatic = false)
            {
                mStream << mIndenter.prefix();

                if (isStatic)
                {
                    mStream << "static ";
                }

                mStream << fieldType << " " << fieldName << std::endl;
            }

            void writeStaticFieldInitialization (const std::string & fieldName,
                                                 const std::string & fieldType,
                                                 const std::string & fieldValue)
            {
                mStream << fieldType << " " << fieldName << " = " << fieldValue << std::endl;
            }

            std::string getMethodParameterString (const std::vector<std::string> & methodParameters)
            {
                std::string parameterString;
                bool firstParameter = true;
                for (auto & param: methodParameters)
                {
                    if (!firstParameter)
                    {
                        parameterString += ", ";
                    }
                    firstParameter = false;
                    parameterString += param;
                }
                return parameterString;
            }

            void writeClassMethodDeclaration (const std::string & methodName,
                                              bool isConst = false,
                                              bool isVirtual = false,
                                              bool isStatic = false,
                                              bool isPureVirtual = false,
                                              bool isDelete = false)
            {
                writeClassMethodDeclaration(methodName, "", "", isConst, isVirtual, isStatic, isPureVirtual, isDelete);
            }

            void writeClassMethodDeclaration (const std::string & methodName,
                                              const std::string & methodReturn,
                                              bool isConst = false,
                                              bool isVirtual = false,
                                              bool isStatic = false,
                                              bool isPureVirtual = false,
                                              bool isDelete = false)
            {
                writeClassMethodDeclaration(methodName, methodReturn, "", isConst, isVirtual, isStatic, isPureVirtual, isDelete);
            }

            void writeClassMethodDeclaration (const std::string & methodName,
                                              const std::string & methodReturn,
                                              const std::string & methodParameters,
                                              bool isConst = false,
                                              bool isVirtual = false,
                                              bool isStatic = false,
                                              bool isPureVirtual = false,
                                              bool isDelete = false)
            {
                mStream << mIndenter.prefix();

                if (isVirtual)
                {
                    mStream << "virtual ";
                }
                else if (isStatic)
                {
                    mStream << "static ";
                }

                writeMethodSignature(methodName, methodReturn, methodParameters);

                if (isConst)
                {
                    mStream << " const";
                }

                if (isPureVirtual)
                {
                    mStream << " = 0";
                }
                else if (isDelete)
                {
                    mStream << " = delete";
                }

                mStream << ";" << std::endl << std::endl;
            }

            void writeClassMethodInlineOpening (const std::string & methodName,
                                                bool isConst = false,
                                                bool isVirtual = false)
            {
                writeClassMethodInlineOpening(methodName, "", "", isConst, isVirtual);
            }

            void writeClassMethodInlineOpening (const std::string & methodName,
                                                const std::string & methodReturn,
                                                bool isConst = false,
                                                bool isVirtual = false)
            {
                writeClassMethodInlineOpening(methodName, methodReturn, "", isConst, isVirtual);
            }

            void writeClassMethodInlineOpening (const std::string & methodName,
                                                const std::string & methodReturn,
                                                const std::string & methodParameters,
                                                bool isConst = false,
                                                bool isVirtual = false)
            {
                mStream << mIndenter.prefix();

                if (isVirtual)
                {
                    mStream << "virtual ";
                }

                writeMethodSignature(methodName, methodReturn, methodParameters);

                if (isConst)
                {
                    mStream << " const";
                }

                writeCurlyBraceOpening();
            }

            void writeClassMethodInlineClosing ()
            {
                --mIndenter;
                mStream << mIndenter.prefix() << "}" << std::endl << std::endl;
            }

            void writeMethodImplementationOpening (const std::string & methodName,
                                                   bool isConst = false)
            {
                writeMethodImplementationOpening(methodName, "", "", isConst);
            }

            void writeMethodImplementationOpening (const std::string & methodName,
                                                   const std::string & methodReturn,
                                                   bool isConst = false)
            {
                writeMethodImplementationOpening(methodName, methodReturn, "", isConst);
            }

            void writeMethodImplementationOpening (const std::string & methodName,
                                                   const std::string & methodReturn,
                                                   const std::string & methodParameters,
                                                   bool isConst = false)
            {
                mStream << mIndenter.prefix();

                writeMethodSignature(methodName, methodReturn, methodParameters);

                if (isConst)
                {
                    mStream << " const";
                }

                writeCurlyBraceOpening();
            }

            void writeMethodImplementationClosing ()
            {
                --mIndenter;
                mStream << mIndenter.prefix() << "}" << std::endl << std::endl;
            }

            void writeForLoopOpening (const std::string & forInitialization,
                                      const std::string & forEvaluation,
                                      const std::string & forPostOperation)
            {
                mStream << mIndenter.prefix() << "for (" << forInitialization << "; " << forEvaluation <<
                    "; " << forPostOperation << ")" << std::endl;
                writeCurlyBraceOpening();
            }

            void writeForLoopClosing ()
            {
                writeCurlyBraceClosing();
            }

            void writeForEachLoopOpening (const std::string & forValue,
                                          const std::string & forCollection)
            {
                mStream << mIndenter.prefix() << "for (" << forValue << ": " << forCollection << ")" << std::endl;
                writeCurlyBraceOpening();
            }

            void writeForEachLoopClosing ()
            {
                writeCurlyBraceClosing();
            }

            void writeWhileLoopOpening (const std::string & whileEvaluation)
            {
                mStream << mIndenter.prefix() << "while (" << whileEvaluation << ")" << std::endl;
                writeCurlyBraceOpening();
            }

            void writeWhileLoopClosing ()
            {
                writeCurlyBraceClosing();
            }

            void writeSwitchOpening (const std::string & switchValue)
            {
                mStream << mIndenter.prefix() << "switch (" << switchValue << ")" << std::endl;
                writeCurlyBraceOpening();
            }

            void writeSwitchClosing ()
            {
                writeCurlyBraceClosing();
            }

            void writeSwitchCase (const std::string & switchCaseValue)
            {
                --mIndenter;
                mStream << mIndenter.prefix() << "case " << switchCaseValue << ":" << std::endl;
                ++mIndenter;
            }

            void writeSwitchDefaultCase ()
            {
                --mIndenter;
                mStream << mIndenter.prefix() << "default:" << std::endl;
                ++mIndenter;
            }

            void writeIfOpening (const std::string & ifValue)
            {
                mStream << mIndenter.prefix() << "if (" << ifValue << ")" << std::endl;
                writeCurlyBraceOpening();
            }

            void writeElseIfOpening (const std::string & ifValue)
            {
                mStream << mIndenter.prefix() << "else if (" << ifValue << ")" << std::endl;
                writeCurlyBraceOpening();
            }

            void writeIfClosing ()
            {
                writeCurlyBraceClosing();
            }

        private:
            void writeMethodSignature (const std::string & methodName,
                                       const std::string & methodReturn,
                                       const std::string & methodParameters)
            {
                if (!methodReturn.empty())
                {
                    mStream << methodReturn << " ";
                }

                mStream << methodName << " (" << methodParameters << ")";
            }
            
            std::ofstream & mStream;
            CodeIndenter mIndenter;
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_CodeWriter_h
