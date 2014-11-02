//
//  CodeGeneratorCPP.cpp
//  Protocol
//
//  Created by Wahid Tanner on 10/17/14.
//

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

void Protocol::CodeGeneratorCPP::generateCode (const string & outputFolder, const ProtoModel & protoModel, const std::string & projectName) const
{
    filesystem::path outputPath(outputFolder);
    filesystem::path modelPath(protoModel.name());
    filesystem::path headerPath(outputPath / filesystem::change_extension(modelPath, mHeaderFileExtension));
    filesystem::path sourcePath(outputPath / filesystem::change_extension(modelPath, mSourceFileExtension));

    filesystem::create_directory(outputFolder);
    filesystem::ofstream headerFile(headerPath, ios::out | ios::trunc);
    CodeWriter headerFileWriter(headerFile);
    filesystem::ofstream sourceFile(sourcePath, ios::out | ios::trunc);
    CodeWriter sourceFileWriter(sourceFile);

    headerFileWriter.writeLine(mHeaderFileProlog);
    headerFileWriter.writeHeaderIncludeBlockOpening(headerIncludeBlockText(protoModel, projectName));

    writeStandardIncludFileNamesToHeader(headerFileWriter);
    writeIncludedProtoFileNamesToHeader(headerFileWriter, protoModel);

    writeProtoEnumsToHeader(headerFileWriter, protoModel);

    writeProtoMessagesToHeader(headerFileWriter, protoModel);

    headerFileWriter.writeHeaderIncludeBlockClosing();

    sourceFileWriter.writeLine(mSourceFileProlog);
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

void Protocol::CodeGeneratorCPP::writeStandardIncludFileNamesToHeader (CodeWriter & headerFileWriter) const
{
    headerFileWriter.writeIncludeLibrary("cstdint");
    headerFileWriter.writeIncludeLibrary("string");
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
    auto protoEnumBegin = protoModel.enums()->cbegin();
    auto protoEnumEnd = protoModel.enums()->cend();
    while (protoEnumBegin != protoEnumEnd)
    {
        auto enumModel = *protoEnumBegin;
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
}

void Protocol::CodeGeneratorCPP::writeProtoMessagesToHeader (CodeWriter & headerFileWriter, const ProtoModel & protoModel) const
{
    auto protoMessageBegin = protoModel.messages()->cbegin();
    auto protoMessageEnd = protoModel.messages()->cend();
    while (protoMessageBegin != protoMessageEnd)
    {
        auto messageModel = *protoMessageBegin;

        writeMessageToHeader(headerFileWriter, protoModel, *messageModel, messageModel->namePascal());

        ++protoMessageBegin;
    }
}


void Protocol::CodeGeneratorCPP::writeMessageToHeader (CodeWriter & headerFileWriter,
                                                       const ProtoModel & protoModel,
                                                       const MessageModel & messageModel,
                                                       const std::string & className) const
{
    headerFileWriter.writeClassOpening(className);

    headerFileWriter.writeClassPublic();

    // Generate all the typedefs for nested classes first, then generate each class.
    bool subMessageFound = false;
    auto messageMessageBegin = messageModel.messages()->cbegin();
    auto messageMessageEnd = messageModel.messages()->cend();
    while (messageMessageBegin != messageMessageEnd)
    {
        subMessageFound = true;
        auto messageSubModel = *messageMessageBegin;

        string subClassName = className + messageSubModel->namePascal();
        headerFileWriter.writeTypedef(subClassName, messageSubModel->namePascal());

        ++messageMessageBegin;
    }
    if (subMessageFound)
    {
        headerFileWriter.writeBlankLine();
    }
    messageMessageBegin = messageModel.messages()->cbegin();
    messageMessageEnd = messageModel.messages()->cend();
    while (messageMessageBegin != messageMessageEnd)
    {
        auto messageSubModel = *messageMessageBegin;

        string subClassName = className + messageSubModel->namePascal();
        writeMessageToHeader(headerFileWriter, protoModel, *messageSubModel, subClassName);

        ++messageMessageBegin;
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

    auto messageFieldBegin = messageModel.fields()->cbegin();
    auto messageFieldEnd = messageModel.fields()->cend();
    while (messageFieldBegin != messageFieldEnd)
    {
        auto messageFieldModel = *messageFieldBegin;

        methodName = messageFieldModel->name();
        string fieldType = fullTypeName(protoModel, messageFieldModel->fieldType());
        methodReturn = fieldType;
        methodParameters = "";
        headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters, true);

        methodName = "set";
        methodName += messageFieldModel->namePascal();
        methodReturn = "void";
        methodParameters = fieldType + " value";
        headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters);

        methodName = "has";
        methodName += messageFieldModel->namePascal();
        methodReturn = "bool";
        methodParameters = "";
        headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters, true);

        methodName = "clear";
        methodName += messageFieldModel->namePascal();
        methodReturn = "void";
        methodParameters = "";
        headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters);

        ++messageFieldBegin;
    }

    headerFileWriter.writeClassPrivate();

    messageFieldBegin = messageModel.fields()->cbegin();
    messageFieldEnd = messageModel.fields()->cend();
    while (messageFieldBegin != messageFieldEnd)
    {
        auto messageFieldModel = *messageFieldBegin;

        string constantName = "m";
        constantName += messageFieldModel->namePascal() + "Index";
        string fieldType = "const unsigned int";
        headerFileWriter.writeClassFieldDeclaration(constantName, fieldType, to_string(messageFieldModel->index()), true);

        ++messageFieldBegin;
    }

    headerFileWriter.writeClassClosing();
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
