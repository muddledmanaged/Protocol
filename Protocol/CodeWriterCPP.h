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
            CodeWriter ()
            { }

            void writeCurlyBraceOpening (std::ofstream & stream)
            {
                stream << mIndenter.prefix() << "{" << std::endl;
                ++mIndenter;
            }

            void writeCurlyBraceClosing (std::ofstream & stream)
            {
                --mIndenter;
                stream << mIndenter.prefix() << "}" << std::endl;
            }

            void writeLine (std::ofstream & stream, const std::string & text)
            {
                stream << mIndenter.prefix() << text << std::endl;
            }

            void writeLineComment (std::ofstream & stream, const std::string & comment)
            {
                stream << mIndenter.prefix() << "// " << comment << std::endl;
            }

            void writeIfDef (std::ofstream & stream, const std::string & text)
            {
                stream << "#ifdef " << text << std::endl;
            }

            void writeIfNotDef (std::ofstream & stream, const std::string & text)
            {
                stream << "#ifndef " << text << std::endl;
            }

            void writeDefine (std::ofstream & stream, const std::string & text)
            {
                stream << "#define " << text << std::endl;
            }

            void writeEndIf (std::ofstream & stream)
            {
                stream << "#endif" << std::endl;
            }

            void writeIncludeLibrary (std::ofstream & stream, const std::string & fileName)
            {
                stream << "#include <" << fileName << ">" << std::endl;
            }

            void writeIncludeProject (std::ofstream & stream, const std::string & fileName)
            {
                stream << "#include \"" << fileName << "\"" << std::endl;
            }

            void writeNamespaceOpening (std::ofstream & stream, const std::string & namespaceName)
            {
                stream << mIndenter.prefix() << "namespace " << namespaceName << std::endl;
                writeCurlyBraceOpening();
            }

            void writeNamespaceClosing (std::ofstream & stream)
            {
                --mIndenter;
                stream << mIndenter.prefix() << "} // namespace" << std::endl << std::endl;
            }

            void writeUsingNamespace (std::ofstream & stream, const std::string & namespaceName)
            {
                stream << "using namespace " << namespaceName << ";" << std::endl;
            }

            void writeClassOpening (std::ofstream & stream, const std::string & className)
            {
                stream << mIndenter.prefix() << "class " << className << std::endl;
                writeCurlyBraceOpening();
            }

            void writeClassClosing (std::ofstream & stream)
            {
                --mIndenter;
                stream << mIndenter.prefix() << "};" << std::endl << std::endl;
            }

            void writeClassPublic (std::ofstream & stream)
            {
                --mIndenter;
                stream << mIndenter.prefix() << "public:" << std::endl;
                ++mIndenter;
            }

            void writeClassProtected (std::ofstream & stream)
            {
                --mIndenter;
                stream << mIndenter.prefix() << "protected:" << std::endl;
                ++mIndenter;
            }

            void writeClassPrivate (std::ofstream & stream)
            {
                --mIndenter;
                stream << mIndenter.prefix() << "private:" << std::endl;
                ++mIndenter;
            }

            void writeClassFieldDeclaration (std::ofstream & stream, const std::string & fieldName,
                                             const std::string & fieldType, bool isStatic = false)
            {
                stream << mIndenter.prefix();

                if (isStatic)
                {
                    stream << "static ";
                }

                stream << fieldType << " " << fieldName << std::endl;
            }

            void writeStaticFieldInitialization (std::ofstream & stream, const std::string & fieldName,
                                                      const std::string & fieldType, const std::string & fieldValue)
            {
                stream << fieldType << " " << fieldName << " = " << fieldValue << std::endl;
            }

            void writeClassMethodDeclaration (std::ofstream & stream, const std::string & methodName,
                                              const std::string & methodReturn, const std::vector<std::string> & methodParameters,
                                              bool isConst = false, bool isVirtual = false, bool isStatic = false,
                                              bool isPureVirtual = false, bool isDelete = false)
            {
                stream << mIndenter.prefix();

                if (isVirtual)
                {
                    stream << "virtual ";
                }
                else if (isStatic)
                {
                    stream << "static ";
                }

                writeMethodSignature(stream, methodName, methodReturn, methodParameters);

                if (isConst)
                {
                    stream << " const";
                }
                else if (isPureVirtual)
                {
                    stream << " = 0";
                }
                else if (isDelete)
                {
                    stream << " = delete";
                }

                stream << ";" << std::endl << std::endl;
            }

            void writeClassMethodInlineOpening (std::ofstream & stream, const std::string & methodName,
                                                const std::string & methodReturn, const std::vector<std::string> & methodParameters,
                                                bool isConst = false, bool isVirtual = false)
            {
                stream << mIndenter.prefix();

                if (isVirtual)
                {
                    stream << "virtual ";
                }

                writeMethodSignature(stream, methodName, methodReturn, methodParameters);

                if (isConst)
                {
                    stream << " const";
                }

                writeCurlyBraceOpening();
            }

            void writeClassMethodInlineClosing (std::ofstream & stream)
            {
                --mIndenter;
                stream << mIndenter.prefix() << "}" << std::endl << std::endl;
            }

            void writeMethodImplementationOpening (std::ofstream & stream, const std::string & methodName,
                                                   const std::string & methodReturn, const std::vector<std::string> & methodParameters,
                                                   bool isConst = false)
            {
                stream << mIndenter.prefix();

                writeMethodSignature(stream, methodName, methodReturn, methodParameters);

                if (isConst)
                {
                    stream << " const";
                }

                writeCurlyBraceOpening();
            }

            void writeMethodImplementationClosing (std::ofstream & stream)
            {
                --mIndenter;
                stream << mIndenter.prefix() << "}" << std::endl << std::endl;
            }

            void writeForLoopOpening (std::ofstream & stream, const std::string & forInitialization,
                                      const std::string & forEvaluation, const std::string & forPostOperation)
            {
                stream << mIndenter.prefix() << "for (" << forInitialization << "; " << forEvaluation <<
                    "; " << forPostOperation << ")" << std::endl;
                writeCurlyBraceOpening();
            }

            void writeForLoopClosing (std::ofstream & stream)
            {
                writeCurlyBraceClosing();
            }

            void writeForEachLoopOpening (std::ofstream & stream, const std::string & forValue,
                                          const std::string & forCollection)
            {
                stream << mIndenter.prefix() << "for (" << forValue << ": " << forCollection << ")" << std::endl;
                writeCurlyBraceOpening();
            }

            void writeForEachLoopClosing (std::ofstream & stream)
            {
                writeCurlyBraceClosing();
            }

            void writeWhileLoopOpening (std::ofstream & stream, const std::string & whileEvaluation)
            {
                stream << mIndenter.prefix() << "while (" << whileEvaluation ")" << std::endl;
                writeCurlyBraceOpening();
            }

            void writeWhileLoopClosing (std::ofstream & stream)
            {
                writeCurlyBraceClosing();
            }

            void writeSwitchOpening (std::ofstream & stream, const std::string & switchValue)
            {
                stream << mIndenter.prefix() << "switch (" << switchValue ")" << std::endl;
                writeCurlyBraceOpening();
            }

            void writeSwitchClosing (std::ofstream & stream)
            {
                writeCurlyBraceClosing();
            }

            void writeSwitchCase (std::ofstream & stream, const std::string & switchCaseValue)
            {
                --mIndenter;
                stream << mIndenter.prefix() << "case " << switchCaseValue ":" << std::endl;
                ++mIndenter;
            }

            void writeSwitchDefaultCase (std::ofstream & stream)
            {
                --mIndenter;
                stream << mIndenter.prefix() << "default:" << std::endl;
                ++mIndenter;
            }

            void writeIfOpening (std::ofstream & stream, const std::string & ifValue)
            {
                stream << mIndenter.prefix() << "if (" << ifValue ")" << std::endl;
                writeCurlyBraceOpening();
            }

            void writeElseIfOpening (std::ofstream & stream, const std::string & ifValue)
            {
                stream << mIndenter.prefix() << "else if (" << ifValue ")" << std::endl;
                writeCurlyBraceOpening();
            }

            void writeIfClosing (std::ofstream & stream)
            {
                writeCurlyBraceClosing();
            }

        private:
            void writeMethodSignature (std::ofstream & stream, const std::string & methodName,
                                       const std::string & methodReturn, const std::vector<std::string> & methodParameters)
            {
                if (!methodReturn.empty())
                {
                    stream << methodReturn << " ";
                }

                stream << methodName << " (";

                bool firstParameter = true;
                for (auto & param: methodParameters)
                {
                    if (!firstParameter)
                    {
                        stream << ", ";
                    }
                    firstParameter = false;
                    stream << param;
                }

                stream << ")";
            }
            
            CodeIndenter mIndenter;
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_CodeWriter_h
