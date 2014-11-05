//
//  CodeGeneratorCPP.cpp
//  Protocol
//
//  Created by Wahid Tanner on 10/17/14.
//

#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/filesystem/fstream.hpp>

#include "CodeGeneratorCPP.h"

using namespace std;
using namespace boost;
using namespace MuddledManaged;

const string Protocol::CodeGeneratorCPP::mHeaderFileExtension = ".protocol.h";
const string Protocol::CodeGeneratorCPP::mSourceFileExtension = ".protocol.cpp";
const string Protocol::CodeGeneratorCPP::mHeaderFileProlog =
"// This file was generated from the Protocol compiler.\n"
"// You should not edit this file directly.\n";
const string Protocol::CodeGeneratorCPP::mSourceFileProlog =
"// This file was generated from the Protocol compiler.\n"
"// You should not edit this file directly.\n";

Protocol::CodeGeneratorCPP::CodeGeneratorCPP ()
{ }

void Protocol::CodeGeneratorCPP::generateCode (const string & outputFolder, const ProtoModel & protoModel,
                                               const std::string & projectName) const
{
    generateHeaderFile(outputFolder, protoModel, projectName);
    generateSourceFile(outputFolder, protoModel, projectName);
}

void Protocol::CodeGeneratorCPP::generateHeaderFile (const std::string & outputFolder, const ProtoModel & protoModel,
                                                     const std::string & projectName) const
{
    filesystem::path outputPath(outputFolder);
    filesystem::path modelPath(protoModel.namePascal());
    filesystem::path headerPath(outputPath / filesystem::change_extension(modelPath, mHeaderFileExtension));

    filesystem::create_directory(outputFolder);
    filesystem::ofstream headerFile(headerPath, ios::out | ios::trunc);
    CodeWriter headerFileWriter(headerFile);

    headerFileWriter.writeLine(mHeaderFileProlog);
    headerFileWriter.writeHeaderIncludeBlockOpening(headerIncludeBlockText(protoModel, projectName));

    writeStandardIncludeFileNamesToHeader(headerFileWriter);
    writeIncludedProtoFileNamesToHeader(headerFileWriter, protoModel);

    writeProtoEnumsToHeader(headerFileWriter, protoModel);

    writeProtoMessagesToHeader(headerFileWriter, protoModel);

    headerFileWriter.writeHeaderIncludeBlockClosing();
}

void Protocol::CodeGeneratorCPP::generateSourceFile (const std::string & outputFolder, const ProtoModel & protoModel,
                                                     const std::string & projectName) const
{
    filesystem::path outputPath(outputFolder);
    filesystem::path modelPath(protoModel.namePascal());
    filesystem::path sourcePath(outputPath / filesystem::change_extension(modelPath, mSourceFileExtension));

    filesystem::create_directory(outputFolder);
    filesystem::ofstream sourceFile(sourcePath, ios::out | ios::trunc);
    CodeWriter sourceFileWriter(sourceFile);

    sourceFileWriter.writeLine(mSourceFileProlog);

    sourceFileWriter.writeIncludeProject(filesystem::change_extension(modelPath, mHeaderFileExtension).string());
    sourceFileWriter.writeBlankLine();

    writeProtoMessagesToSource(sourceFileWriter, protoModel);
}

string Protocol::CodeGeneratorCPP::headerIncludeBlockText (const ProtoModel & protoModel, const std::string & projectName) const
{
    string text = projectName;
    if (!text.empty())
    {
        text += "_";
    }

    filesystem::path modelPath(protoModel.namePascal());
    text += filesystem::basename(modelPath.filename());
    text += "_h";

    return text;
}

void Protocol::CodeGeneratorCPP::writeStandardIncludeFileNamesToHeader (CodeWriter & headerFileWriter) const
{
    headerFileWriter.writeIncludeLibrary("cstdint");
    headerFileWriter.writeIncludeLibrary("memory");
    headerFileWriter.writeIncludeLibrary("string");
    headerFileWriter.writeIncludeLibrary("vector");
    headerFileWriter.writeBlankLine();
}

void Protocol::CodeGeneratorCPP::writeIncludedProtoFileNamesToHeader (CodeWriter & headerFileWriter, const ProtoModel & protoModel) const
{
    auto importedProtoBegin = protoModel.importedProtoNames()->cbegin();
    auto importedProtoEnd = protoModel.importedProtoNames()->cend();
    bool importsFound = false;
    while (importedProtoBegin != importedProtoEnd)
    {
        importsFound = true;
        filesystem::path protoPath(*importedProtoBegin);
        filesystem::path headerPath(filesystem::change_extension(protoPath, mHeaderFileExtension));
        headerFileWriter.writeIncludeProject(headerPath.string());
        ++importedProtoBegin;
    }
    if (importsFound)
    {
        headerFileWriter.writeBlankLine();
    }
}

void Protocol::CodeGeneratorCPP::writeProtoEnumsToHeader (CodeWriter & headerFileWriter, const ProtoModel & protoModel) const
{
    string currentPackage;
    vector<string> enumNamespaces;
    auto protoEnumBegin = protoModel.enums()->cbegin();
    auto protoEnumEnd = protoModel.enums()->cend();
    while (protoEnumBegin != protoEnumEnd)
    {
        auto enumModel = *protoEnumBegin;

        string enumPackage = enumModel->package();
        if (enumPackage != currentPackage)
        {
            for (int i = 0; i < enumNamespaces.size(); i++)
            {
                headerFileWriter.writeNamespaceClosing();
            }
            currentPackage = enumPackage;
            boost::split(enumNamespaces, enumPackage, boost::is_any_of("."));
            for (auto & str: enumNamespaces)
            {
                headerFileWriter.writeNamespaceOpening(str);
            }
        }
        
        headerFileWriter.writeEnumOpening(enumModel->namePascal());

        auto enumValueBegin = enumModel->enumValues()->cbegin();
        auto enumValueEnd = enumModel->enumValues()->cend();
        bool firstEnumValue = true;
        while (enumValueBegin != enumValueEnd)
        {
            auto enumValueModel = *enumValueBegin;
            if (firstEnumValue)
            {
                headerFileWriter.writeEnumValueFirst(enumValueModel->name(), enumValueModel->value());
                firstEnumValue = false;
            }
            else
            {
                headerFileWriter.writeEnumValueSubsequent(enumValueModel->name(), enumValueModel->value());
            }
            ++enumValueBegin;
        }

        headerFileWriter.writeEnumClosing();
        ++protoEnumBegin;
    }
    for (int i = 0; i < enumNamespaces.size(); i++)
    {
        headerFileWriter.writeNamespaceClosing();
    }
}

void Protocol::CodeGeneratorCPP::writeProtoMessagesToHeader (CodeWriter & headerFileWriter, const ProtoModel & protoModel) const
{
    string currentPackage;
    vector<string> messageNamespaces;
    auto protoMessageBegin = protoModel.messages()->cbegin();
    auto protoMessageEnd = protoModel.messages()->cend();
    while (protoMessageBegin != protoMessageEnd)
    {
        auto messageModel = *protoMessageBegin;

        string messagePackage = messageModel->package();
        if (messagePackage != currentPackage)
        {
            for (int i = 0; i < messageNamespaces.size(); i++)
            {
                headerFileWriter.writeNamespaceClosing();
            }
            currentPackage = messagePackage;
            boost::split(messageNamespaces, messagePackage, boost::is_any_of("."));
            for (auto & str: messageNamespaces)
            {
                headerFileWriter.writeNamespaceOpening(str);
            }
        }
        writeMessageToHeader(headerFileWriter, protoModel, *messageModel, messageModel->namePascal());

        ++protoMessageBegin;
    }
    for (int i = 0; i < messageNamespaces.size(); i++)
    {
        headerFileWriter.writeNamespaceClosing();
    }
}


void Protocol::CodeGeneratorCPP::writeMessageToHeader (CodeWriter & headerFileWriter,
                                                       const ProtoModel & protoModel,
                                                       const MessageModel & messageModel,
                                                       const std::string & className) const
{
    headerFileWriter.writeClassOpening(className);

    headerFileWriter.writeClassPublic();

    // Generate all the nested classes first, then generate a typedef for the simpler name.
    bool subMessageFound = false;
    auto messageMessageBegin = messageModel.messages()->cbegin();
    auto messageMessageEnd = messageModel.messages()->cend();
    while (messageMessageBegin != messageMessageEnd)
    {
        subMessageFound = true;
        auto messageSubModel = *messageMessageBegin;

        string subClassName = className + "_" + messageSubModel->namePascal();
        writeMessageToHeader(headerFileWriter, protoModel, *messageSubModel, subClassName);

        ++messageMessageBegin;
    }
    messageMessageBegin = messageModel.messages()->cbegin();
    messageMessageEnd = messageModel.messages()->cend();
    while (messageMessageBegin != messageMessageEnd)
    {
        auto messageSubModel = *messageMessageBegin;

        string subClassName = className + "_" + messageSubModel->namePascal();
        headerFileWriter.writeTypedef(subClassName, messageSubModel->namePascal());

        ++messageMessageBegin;
    }
    if (subMessageFound)
    {
        headerFileWriter.writeBlankLine();
        headerFileWriter.writeClassPublic();
    }

    string methodName = className;
    headerFileWriter.writeClassMethodDeclaration(methodName);

    string methodReturn = "";
    string methodParameters = "const ";
    methodParameters += className + " & src";
    headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters);

    methodName = "~";
    methodName += className;
    headerFileWriter.writeClassMethodDeclaration(methodName);

    methodName = "operator =";
    methodReturn = className + " &";
    methodParameters = "const ";
    methodParameters += className + " & rhs";
    headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters);

    methodName = "swap";
    methodReturn = "void";
    methodParameters = className + " * other";
    headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters);

    methodName = "clear";
    methodReturn = "void";
    headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn);

    methodName = "parse";
    methodReturn = "void";
    methodParameters = "const std::string & data";
    headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters);

    methodName = "serialize";
    methodReturn = "std::string";
    headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, true);

    methodName = "size";
    methodReturn = "size_t";
    headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, true);

    methodName = "isValid";
    methodReturn = "bool";
    headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, true);

    auto messageFieldBegin = messageModel.fields()->cbegin();
    auto messageFieldEnd = messageModel.fields()->cend();
    while (messageFieldBegin != messageFieldEnd)
    {
        auto messageFieldModel = *messageFieldBegin;

        writeMessageFieldToHeader(headerFileWriter, protoModel, *messageFieldModel);

        ++messageFieldBegin;
    }

    auto oneofBegin = messageModel.oneofs()->cbegin();
    auto oneofEnd = messageModel.oneofs()->cend();
    while (oneofBegin != oneofEnd)
    {
        auto oneofModel = *oneofBegin;

        writeOneofToHeader(headerFileWriter, protoModel, *oneofModel);

        ++oneofBegin;
    }

    headerFileWriter.writeClassPrivate();

    messageFieldBegin = messageModel.fields()->cbegin();
    messageFieldEnd = messageModel.fields()->cend();
    while (messageFieldBegin != messageFieldEnd)
    {
        auto messageFieldModel = *messageFieldBegin;

        writeMessageFieldIndexToHeader(headerFileWriter, *messageFieldModel);

        ++messageFieldBegin;
    }

    oneofBegin = messageModel.oneofs()->cbegin();
    oneofEnd = messageModel.oneofs()->cend();
    while (oneofBegin != oneofEnd)
    {
        auto oneofModel = *oneofBegin;

        writeMessageFieldIndexesToHeader(headerFileWriter, *oneofModel);

        ++oneofBegin;
    }

    headerFileWriter.writeBlankLine();

    messageFieldBegin = messageModel.fields()->cbegin();
    messageFieldEnd = messageModel.fields()->cend();
    while (messageFieldBegin != messageFieldEnd)
    {
        auto messageFieldModel = *messageFieldBegin;

        writeMessageFieldBackingFieldsToHeader(headerFileWriter, protoModel, *messageFieldModel, true);

        ++messageFieldBegin;
    }

    oneofBegin = messageModel.oneofs()->cbegin();
    oneofEnd = messageModel.oneofs()->cend();
    while (oneofBegin != oneofEnd)
    {
        auto oneofModel = *oneofBegin;

        writeOneofBackingFieldsToHeader(headerFileWriter, protoModel, *oneofModel);
        
        ++oneofBegin;
    }

    headerFileWriter.writeClassClosing();
}

void Protocol::CodeGeneratorCPP::writeMessageFieldToHeader (CodeWriter & headerFileWriter, const ProtoModel & protoModel,
                                                            const MessageFieldModel & messageFieldModel) const
{
    string methodName;
    string methodReturn;
    string methodParameters;
    string fieldType = fullTypeName(protoModel, messageFieldModel.fieldType());

    switch (messageFieldModel.fieldCategory())
    {
        case MessageFieldModel::FieldCategory::numericType:
        case MessageFieldModel::FieldCategory::enumType:
        {
            if (messageFieldModel.requiredness() == MessageFieldModel::Requiredness::repeated)
            {
                methodName = messageFieldModel.name();
                methodReturn = fieldType;
                methodParameters = "size_t index";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters, true);

                methodName = "size";
                methodName += messageFieldModel.namePascal();
                methodReturn = "size_t";
                methodParameters = "";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters, true);

                methodName = "set";
                methodName += messageFieldModel.namePascal();
                methodReturn = "void";
                methodParameters = "size_t index, ";
                methodParameters += fieldType + " value";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters);

                methodName = "add";
                methodName += messageFieldModel.namePascal();
                methodReturn = "void";
                methodParameters = fieldType + " value";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters);

                methodName = "clear";
                methodName += messageFieldModel.namePascal();
                methodReturn = "void";
                methodParameters = "";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters);
            }
            else
            {
                methodName = messageFieldModel.name();
                methodReturn = fieldType;
                methodParameters = "";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters, true);

                methodName = "set";
                methodName += messageFieldModel.namePascal();
                methodReturn = "void";
                methodParameters = fieldType + " value";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters);

                methodName = "has";
                methodName += messageFieldModel.namePascal();
                methodReturn = "bool";
                methodParameters = "";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters, true);

                methodName = "clear";
                methodName += messageFieldModel.namePascal();
                methodReturn = "void";
                methodParameters = "";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters);
            }
            break;
        }

        case MessageFieldModel::FieldCategory::stringType:
        case MessageFieldModel::FieldCategory::bytesType:
        case MessageFieldModel::FieldCategory::messageType:
        {
            if (messageFieldModel.requiredness() == MessageFieldModel::Requiredness::repeated)
            {
                methodName = messageFieldModel.name();
                methodReturn = "const ";
                methodReturn += fieldType + " &";
                methodParameters = "size_t index";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters, true);

                methodName = "size";
                methodName += messageFieldModel.namePascal();
                methodReturn = "size_t";
                methodParameters = "";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters, true);

                methodName = "mutable";
                methodName += messageFieldModel.namePascal();
                methodReturn = fieldType + " *";
                methodParameters = "size_t index";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters);

                methodName = "set";
                methodName += messageFieldModel.namePascal();
                methodReturn = "void";
                methodParameters = "size_t index, ";
                methodParameters += "const ";
                methodParameters += fieldType + " & value";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters);

                methodName = "add";
                methodName += messageFieldModel.namePascal();
                methodReturn = "void";
                methodParameters = "const ";
                methodParameters += fieldType + " & value";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters);

                methodName = "clear";
                methodName += messageFieldModel.namePascal();
                methodReturn = "void";
                methodParameters = "";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters);

                methodName = "reset";
                methodName += messageFieldModel.namePascal();
                methodReturn = "void";
                methodParameters = "size_t index, ";
                methodParameters += fieldType + " * value";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters);

                methodName = "release";
                methodName += messageFieldModel.namePascal();
                methodReturn = fieldType + " *";
                methodParameters = "size_t index";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters);
            }
            else
            {
                methodName = messageFieldModel.name();
                methodReturn = "const ";
                methodReturn += fieldType + " &";
                methodParameters = "";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters, true);

                methodName = "mutable";
                methodName += messageFieldModel.namePascal();
                methodReturn = fieldType + " *";
                methodParameters = "";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters);

                methodName = "set";
                methodName += messageFieldModel.namePascal();
                methodReturn = "void";
                methodParameters = "const ";
                methodParameters += fieldType + " & value";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters);

                methodName = "has";
                methodName += messageFieldModel.namePascal();
                methodReturn = "bool";
                methodParameters = "";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters, true);

                methodName = "clear";
                methodName += messageFieldModel.namePascal();
                methodReturn = "void";
                methodParameters = "";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters);

                methodName = "reset";
                methodName += messageFieldModel.namePascal();
                methodReturn = "void";
                methodParameters = fieldType + " * value";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters);

                methodName = "release";
                methodName += messageFieldModel.namePascal();
                methodReturn = fieldType + " *";
                methodParameters = "";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters);
            }
            break;
        }

        default:
            break;
    }
}

void Protocol::CodeGeneratorCPP::writeMessageFieldBackingFieldsToHeader (CodeWriter & headerFileWriter, const ProtoModel & protoModel,
                                                                         const MessageFieldModel & messageFieldModel, bool writeSetFlag) const
{
    string backingFieldName;
    string backingFieldType;
    string fieldType = fullTypeName(protoModel, messageFieldModel.fieldType());

    switch (messageFieldModel.fieldCategory())
    {
        case MessageFieldModel::FieldCategory::numericType:
        case MessageFieldModel::FieldCategory::enumType:
        {
            if (messageFieldModel.requiredness() == MessageFieldModel::Requiredness::repeated)
            {
                backingFieldName = "m";
                backingFieldName += messageFieldModel.namePascal() + "Collection";
                backingFieldType = "std::vector<";
                backingFieldType += fieldType + ">";
                headerFileWriter.writeClassFieldDeclaration(backingFieldName, backingFieldType);
            }
            else
            {
                if (writeSetFlag)
                {
                    backingFieldName = "m";
                    backingFieldName += messageFieldModel.namePascal() + "Set";
                    backingFieldType = "bool";
                    headerFileWriter.writeClassFieldDeclaration(backingFieldName, backingFieldType);
                }

                backingFieldName = "m";
                backingFieldName += messageFieldModel.namePascal() + "Value";
                backingFieldType = fieldType;
                headerFileWriter.writeClassFieldDeclaration(backingFieldName, backingFieldType);
            }
            break;
        }

        case MessageFieldModel::FieldCategory::stringType:
        case MessageFieldModel::FieldCategory::bytesType:
        case MessageFieldModel::FieldCategory::messageType:
        {
            if (messageFieldModel.requiredness() == MessageFieldModel::Requiredness::repeated)
            {
                backingFieldName = "m";
                backingFieldName += messageFieldModel.namePascal() + "Collection";
                backingFieldType = "std::vector<std::unique_ptr<";
                backingFieldType += fieldType + ">>";
                headerFileWriter.writeClassFieldDeclaration(backingFieldName, backingFieldType);
            }
            else
            {
                if (writeSetFlag)
                {
                    backingFieldName = "m";
                    backingFieldName += messageFieldModel.namePascal() + "Set";
                    backingFieldType = "bool";
                    headerFileWriter.writeClassFieldDeclaration(backingFieldName, backingFieldType);
                }

                backingFieldName = "m";
                backingFieldName += messageFieldModel.namePascal() + "Value";
                backingFieldType = "std::unique_ptr<";
                backingFieldType += fieldType + ">";
                headerFileWriter.writeClassFieldDeclaration(backingFieldName, backingFieldType);
            }
            break;
        }
            
        default:
            break;
    }
}

void Protocol::CodeGeneratorCPP::writeMessageFieldIndexToHeader (CodeWriter & headerFileWriter,
                                                                 const MessageFieldModel & messageFieldModel) const
{
    string constantName = "m";
    constantName += messageFieldModel.namePascal() + "Index";
    string fieldType = "const unsigned int";
    headerFileWriter.writeClassFieldDeclaration(constantName, fieldType, to_string(messageFieldModel.index()), true);
}

void Protocol::CodeGeneratorCPP::writeOneofToHeader (CodeWriter & headerFileWriter, const ProtoModel & protoModel,
                                                     const OneofModel & oneofModel) const
{
    string enumName = oneofModel.namePascal() + "Choices";
    headerFileWriter.writeEnumOpening(enumName);
    headerFileWriter.writeEnumValueFirst("none", 0);

    auto messageFieldBegin = oneofModel.fields()->cbegin();
    auto messageFieldEnd = oneofModel.fields()->cend();
    string enumValueName;
    int enumValueValue = 1;
    while (messageFieldBegin != messageFieldEnd)
    {
        auto messageFieldModel = *messageFieldBegin;

        enumValueName = messageFieldModel->name();
        headerFileWriter.writeEnumValueSubsequent(enumValueName, enumValueValue);
        enumValueValue++;

        ++messageFieldBegin;
    }

    headerFileWriter.writeEnumClosing();

    string methodName = "current";
    methodName += oneofModel.namePascal() + "Choice";
    string methodReturn = enumName;
    string methodParameters = "";
    headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters);

    methodName = "clear";
    methodName += oneofModel.namePascal();
    methodReturn = "void";
    methodParameters = "";
    headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters);

    messageFieldBegin = oneofModel.fields()->cbegin();
    messageFieldEnd = oneofModel.fields()->cend();
    while (messageFieldBegin != messageFieldEnd)
    {
        auto messageFieldModel = *messageFieldBegin;

        writeMessageFieldToHeader(headerFileWriter, protoModel, *messageFieldModel);

        ++messageFieldBegin;
    }
}

void Protocol::CodeGeneratorCPP::writeOneofBackingFieldsToHeader (CodeWriter & headerFileWriter, const ProtoModel & protoModel,
                                                                  const OneofModel & oneofModel) const
{
    string backingFieldName;
    string backingFieldType;

    backingFieldName = "mCurrent";
    backingFieldName += oneofModel.namePascal() + "Choice";
    backingFieldType = oneofModel.namePascal() + "Choices";
    headerFileWriter.writeClassFieldDeclaration(backingFieldName, backingFieldType);

    auto messageFieldBegin = oneofModel.fields()->cbegin();
    auto messageFieldEnd = oneofModel.fields()->cend();
    while (messageFieldBegin != messageFieldEnd)
    {
        auto messageFieldModel = *messageFieldBegin;

        writeMessageFieldBackingFieldsToHeader(headerFileWriter, protoModel, *messageFieldModel, false);

        ++messageFieldBegin;
    }
}

void Protocol::CodeGeneratorCPP::writeMessageFieldIndexesToHeader (CodeWriter & headerFileWriter,
                                                                   const OneofModel & oneofModel) const
{
    auto messageFieldBegin = oneofModel.fields()->cbegin();
    auto messageFieldEnd = oneofModel.fields()->cend();
    while (messageFieldBegin != messageFieldEnd)
    {
        auto messageFieldModel = *messageFieldBegin;

        writeMessageFieldIndexToHeader(headerFileWriter, *messageFieldModel);

        ++messageFieldBegin;
    }
}

void Protocol::CodeGeneratorCPP::writeProtoMessagesToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel) const
{
    auto protoMessageBegin = protoModel.messages()->cbegin();
    auto protoMessageEnd = protoModel.messages()->cend();
    while (protoMessageBegin != protoMessageEnd)
    {
        auto messageModel = *protoMessageBegin;

        string messageNamespace = messageModel->package();
        boost::replace_all(messageNamespace, ".", "::");
        writeMessageToSource(sourceFileWriter, protoModel, *messageModel, messageModel->namePascal(), messageNamespace);

        ++protoMessageBegin;
    }
}

void Protocol::CodeGeneratorCPP::writeMessageToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                       const MessageModel & messageModel, const std::string & className,
                                                       const std::string & classScope) const
{
    string fullScope = classScope;
    if (!fullScope.empty())
    {
        fullScope += "::";
    }
    fullScope += className;

    auto messageMessageBegin = messageModel.messages()->cbegin();
    auto messageMessageEnd = messageModel.messages()->cend();
    while (messageMessageBegin != messageMessageEnd)
    {
        auto messageSubModel = *messageMessageBegin;

        string subClassName = className + "_" + messageSubModel->namePascal();
        writeMessageToSource(sourceFileWriter, protoModel, *messageSubModel, subClassName, fullScope);

        ++messageMessageBegin;
    }

    string methodName = fullScope + "::" + className;
    sourceFileWriter.writeMethodImplementationOpening(methodName);
    sourceFileWriter.writeMethodImplementationClosing();

    string methodReturn = "";
    string methodParameters = "const ";
    methodParameters += className + " & src";
    sourceFileWriter.writeMethodImplementationOpening(methodName, methodReturn, methodParameters);
    sourceFileWriter.writeMethodImplementationClosing();

    methodName = fullScope + "::~" + className;
    sourceFileWriter.writeMethodImplementationOpening(methodName);
    sourceFileWriter.writeMethodImplementationClosing();

    methodName = fullScope + "::operator =";
    methodReturn = fullScope + "::" + className + " &";
    methodParameters = "const ";
    methodParameters += className + " & rhs";
    sourceFileWriter.writeMethodImplementationOpening(methodName, methodReturn, methodParameters);
    sourceFileWriter.writeMethodImplementationClosing();

    methodName = fullScope + "::swap";
    methodReturn = "void";
    methodParameters = className + " * other";
    sourceFileWriter.writeMethodImplementationOpening(methodName, methodReturn, methodParameters);
    sourceFileWriter.writeMethodImplementationClosing();

    methodName = fullScope + "::clear";
    methodReturn = "void";
    sourceFileWriter.writeMethodImplementationOpening(methodName, methodReturn);
    sourceFileWriter.writeMethodImplementationClosing();

    methodName = fullScope + "::parse";
    methodReturn = "void";
    methodParameters = "const std::string & data";
    sourceFileWriter.writeMethodImplementationOpening(methodName, methodReturn, methodParameters);
    sourceFileWriter.writeMethodImplementationClosing();

    methodName = fullScope + "::serialize";
    methodReturn = "std::string";
    sourceFileWriter.writeMethodImplementationOpening(methodName, methodReturn, true);
    sourceFileWriter.writeMethodImplementationClosing();

    methodName = fullScope + "::size";
    methodReturn = "size_t";
    sourceFileWriter.writeMethodImplementationOpening(methodName, methodReturn, true);
    sourceFileWriter.writeMethodImplementationClosing();

    methodName = fullScope + "::isValid";
    methodReturn = "bool";
    sourceFileWriter.writeMethodImplementationOpening(methodName, methodReturn, true);
    sourceFileWriter.writeMethodImplementationClosing();
}

string Protocol::CodeGeneratorCPP::fullTypeName (const ProtoModel & protoModel, const std::string & protoTypeName) const
{
    if (protoTypeName == "bool")
    {
        return "bool";
    }
    if (protoTypeName == "string")
    {
        return "std::string";
    }
    if (protoTypeName == "double")
    {
        return "double";
    }
    if (protoTypeName == "float")
    {
        return "float";
    }
    if (protoTypeName == "int32")
    {
        return "int32_t";
    }
    if (protoTypeName == "int64")
    {
        return "int64_t";
    }
    if (protoTypeName == "uint32")
    {
        return "uint32_t";
    }
    if (protoTypeName == "uint64")
    {
        return "uint64_t";
    }
    if (protoTypeName == "sint32")
    {
        return "int32_t";
    }
    if (protoTypeName == "sint64")
    {
        return "int64_t";
    }
    if (protoTypeName == "fixed32")
    {
        return "int32_t";
    }
    if (protoTypeName == "fixed64")
    {
        return "int64_t";
    }
    if (protoTypeName == "sfixed32")
    {
        return "int32_t";
    }
    if (protoTypeName == "sfixed64")
    {
        return "int64_t";
    }
    if (protoTypeName == "bytes")
    {
        return "std::string";
    }
    return "";
}
