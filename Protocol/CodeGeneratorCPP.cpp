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
#include "CodeGeneratorUtilityCPP.h"

using namespace std;
using namespace boost;
using namespace MuddledManaged;

const string Protocol::CodeGeneratorCPP::mHeaderFileExtension = ".protocol.h";
const string Protocol::CodeGeneratorCPP::mSourceFileExtension = ".protocol.cpp";
const string Protocol::CodeGeneratorCPP::mBaseClassesNamespace = "MuddledManaged::Protocol";
const string Protocol::CodeGeneratorCPP::mBaseClassesFileName = "ProtoBase";
#include "CodeGeneratorPrologCPP.cpp"
#include "ProtoBaseTemplateCPP.h"

Protocol::CodeGeneratorCPP::CodeGeneratorCPP ()
{ }

void Protocol::CodeGeneratorCPP::generateCode (const string & outputFolder, const ProtoModel & protoModel,
                                               const std::string & projectName, bool generateCommonCode) const
{
    generateHeaderFile(outputFolder, protoModel, projectName);
    generateSourceFile(outputFolder, protoModel, projectName);
    if (generateCommonCode)
    {
        generateHeaderFileCommon(outputFolder, projectName);
    }
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

    headerFileWriter.writeLine(mGeneratedFileProlog);
    headerFileWriter.writeHeaderIncludeBlockOpening(headerIncludeBlockText(protoModel, projectName));

    writeStandardIncludeFileNamesToHeader(headerFileWriter, true);
    writeIncludedProtoFileNamesToHeader(headerFileWriter, protoModel);

    writeProtoEnumsToHeader(headerFileWriter, protoModel);

    writeProtoMessagesToHeader(headerFileWriter, protoModel);

    headerFileWriter.writeHeaderIncludeBlockClosing();
}

void Protocol::CodeGeneratorCPP::generateHeaderFileCommon (const std::string & outputFolder, const std::string & projectName) const
{
    filesystem::path outputPath(outputFolder);
    filesystem::path protoBasePath(mBaseClassesFileName);
    filesystem::path headerPath(outputPath / filesystem::change_extension(protoBasePath, mHeaderFileExtension));

    filesystem::create_directory(outputFolder);
    filesystem::ofstream headerFile(headerPath, ios::out | ios::trunc);
    CodeWriter headerFileWriter(headerFile);

    headerFileWriter.writeLine(mGeneratedFileProlog);
    headerFileWriter.writeHeaderIncludeBlockOpening(headerIncludeBlockText(mBaseClassesFileName, projectName));

    writeStandardIncludeFileNamesToHeader(headerFileWriter, false);

    headerFileWriter.writeLine(mProtoBaseHeaderFileTemplate);

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

    sourceFileWriter.writeLine(mGeneratedFileProlog);

    sourceFileWriter.writeIncludeProject(filesystem::change_extension(modelPath, mHeaderFileExtension).string());
    sourceFileWriter.writeBlankLine();
    sourceFileWriter.writeUsingNamespace("std");
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

string Protocol::CodeGeneratorCPP::headerIncludeBlockText (const std::string & headerBaseName, const std::string & projectName) const
{
    string text = projectName;
    if (!text.empty())
    {
        text += "_";
    }

    text += headerBaseName;
    text += "_h";

    return text;
}

void Protocol::CodeGeneratorCPP::writeStandardIncludeFileNamesToHeader (CodeWriter & headerFileWriter, bool includeBase) const
{
    headerFileWriter.writeIncludeLibrary("cstdint");
    headerFileWriter.writeIncludeLibrary("memory");
    headerFileWriter.writeIncludeLibrary("stdexcept");
    headerFileWriter.writeIncludeLibrary("string");
    headerFileWriter.writeIncludeLibrary("type_traits");
    headerFileWriter.writeIncludeLibrary("vector");
    headerFileWriter.writeBlankLine();

    if (includeBase)
    {
        filesystem::path protoBasePath(mBaseClassesFileName);
        filesystem::path headerPath(filesystem::change_extension(protoBasePath, mHeaderFileExtension));
        headerFileWriter.writeIncludeProject(headerPath.string());
        headerFileWriter.writeBlankLine();
    }
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

        writeEnumToHeader(headerFileWriter, protoModel, *enumModel, enumModel->namePascal());

        ++protoEnumBegin;
    }
    for (int i = 0; i < enumNamespaces.size(); i++)
    {
        headerFileWriter.writeNamespaceClosing();
    }
}

void Protocol::CodeGeneratorCPP::writeEnumToHeader (CodeWriter & headerFileWriter, const ProtoModel & protoModel,
                                                    const EnumModel & enumModel, const std::string & enumName) const
{
    headerFileWriter.writeEnumOpening(enumName);

    auto enumValueBegin = enumModel.enumValues()->cbegin();
    auto enumValueEnd = enumModel.enumValues()->cend();
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
        writeMessageDeclarationToHeader(headerFileWriter, protoModel, *messageModel, messageModel->namePascal());

        ++protoMessageBegin;
    }
    headerFileWriter.writeBlankLine();

    protoMessageBegin = protoModel.messages()->cbegin();
    protoMessageEnd = protoModel.messages()->cend();
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
        writeMessageEnumToHeader(headerFileWriter, protoModel, *messageModel, messageModel->namePascal());

        ++protoMessageBegin;
    }
    
    protoMessageBegin = protoModel.messages()->cbegin();
    protoMessageEnd = protoModel.messages()->cend();
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

void Protocol::CodeGeneratorCPP::writeMessageDeclarationToHeader (CodeWriter & headerFileWriter,
                                                                  const ProtoModel & protoModel,
                                                                  const MessageModel & messageModel,
                                                                  const std::string & className) const
{
    // Generate forward declarations for all the nested classes first.
    auto messageMessageBegin = messageModel.messages()->cbegin();
    auto messageMessageEnd = messageModel.messages()->cend();
    while (messageMessageBegin != messageMessageEnd)
    {
        auto messageSubModel = *messageMessageBegin;

        string subClassName = className + "_" + messageSubModel->namePascal();
        writeMessageDeclarationToHeader(headerFileWriter, protoModel, *messageSubModel, subClassName);

        ++messageMessageBegin;
    }
    headerFileWriter.writeClassForwardDeclaration(className);
}

void Protocol::CodeGeneratorCPP::writeMessageEnumToHeader (CodeWriter & headerFileWriter,
                                                           const ProtoModel & protoModel,
                                                           const MessageModel & messageModel,
                                                           const std::string & className) const
{
    // Generate nested enums for all the nested messages first.
    auto messageMessageBegin = messageModel.messages()->cbegin();
    auto messageMessageEnd = messageModel.messages()->cend();
    while (messageMessageBegin != messageMessageEnd)
    {
        auto messageSubModel = *messageMessageBegin;

        string subClassName = className + "_" + messageSubModel->namePascal();
        writeMessageEnumToHeader(headerFileWriter, protoModel, *messageSubModel, subClassName);

        ++messageMessageBegin;
    }

    // Then generate the nested enums with modified names for this message.
    auto messageEnumBegin = messageModel.enums()->cbegin();
    auto messageEnumEnd = messageModel.enums()->cend();
    while (messageEnumBegin != messageEnumEnd)
    {
        auto enumSubModel = *messageEnumBegin;

        string subEnumName = className + "_" + enumSubModel->namePascal();
        writeEnumToHeader(headerFileWriter, protoModel, *enumSubModel, subEnumName);

        ++messageEnumBegin;
    }
}

void Protocol::CodeGeneratorCPP::writeMessageToHeader (CodeWriter & headerFileWriter,
                                                       const ProtoModel & protoModel,
                                                       const MessageModel & messageModel,
                                                       const std::string & className) const
{
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
    if (subMessageFound)
    {
        headerFileWriter.writeBlankLine();
    }

    string baseClass = "public " + mBaseClassesNamespace + "::ProtoMessage";
    headerFileWriter.writeClassOpening(className, baseClass);

    headerFileWriter.writeClassPublic();

    bool subEnumFound = false;
    auto messageEnumBegin = messageModel.enums()->cbegin();
    auto messageEnumEnd = messageModel.enums()->cend();
    while (messageEnumBegin != messageEnumEnd)
    {
        subEnumFound = true;
        auto enumSubModel = *messageEnumBegin;

        string subEnumName = className + "_" + enumSubModel->namePascal();
        headerFileWriter.writeTypedef(subEnumName, enumSubModel->namePascal());

        ++messageEnumBegin;
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
    
    if (subEnumFound || subMessageFound)
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
    headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, false, true);

    methodName = "parse";
    methodReturn = "size_t";
    methodParameters = "const unsigned char * pData";
    headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters, false, true);

    methodName = "serialize";
    methodReturn = "std::string";
    headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, true, true);

    methodName = "size";
    methodReturn = "size_t";
    headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, true, true);

    methodName = "valid";
    methodReturn = "bool";
    headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, true, true);

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

    string classDataName = className + "Data";
    headerFileWriter.writeStructOpening(classDataName);

    methodName = classDataName;
    headerFileWriter.writeClassMethodDeclaration(methodName);

    methodName = "~";
    methodName += classDataName;
    headerFileWriter.writeClassMethodDeclaration(methodName);

    messageFieldBegin = messageModel.fields()->cbegin();
    messageFieldEnd = messageModel.fields()->cend();
    while (messageFieldBegin != messageFieldEnd)
    {
        auto messageFieldModel = *messageFieldBegin;

        writeMessageFieldBackingFieldsToHeader(headerFileWriter, protoModel, *messageFieldModel);

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

    headerFileWriter.writeBlankLine();

    headerFileWriter.writeClassPrivate();

    methodName = classDataName;
    methodReturn = "";
    methodParameters = "const ";
    methodParameters += classDataName + " & src";
    headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters, false, false, false, false, true);

    methodName = "operator =";
    methodReturn = classDataName + " &";
    methodParameters = "const ";
    methodParameters += classDataName + " & rhs";
    headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters, false, false, false, false, true);

    headerFileWriter.writeStructClosing();

    string backingFieldName = "mData";
    string backingFieldType = "std::shared_ptr<";
    backingFieldType += className + "Data>";
    headerFileWriter.writeClassFieldDeclaration(backingFieldName, backingFieldType);

    headerFileWriter.writeClassClosing();
}

void Protocol::CodeGeneratorCPP::writeMessageFieldToHeader (CodeWriter & headerFileWriter, const ProtoModel & protoModel,
                                                            const MessageFieldModel & messageFieldModel) const
{
    string methodName;
    string methodReturn;
    string methodParameters;
    string fieldType = fullTypeName(messageFieldModel);

    switch (messageFieldModel.fieldCategory())
    {
        case MessageFieldModel::FieldCategory::numericType:
        case MessageFieldModel::FieldCategory::enumType:
        {
            if (messageFieldModel.requiredness() == MessageFieldModel::Requiredness::repeated)
            {
                methodName = "size";
                methodName += messageFieldModel.namePascal();
                methodReturn = "size_t";
                methodParameters = "";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters, true);

                methodName = messageFieldModel.name();
                methodReturn = fieldType;
                methodParameters = "size_t index";
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
                methodName = "has";
                methodName += messageFieldModel.namePascal();
                methodReturn = "bool";
                methodParameters = "";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters, true);

                methodName = messageFieldModel.name();
                methodReturn = fieldType;
                methodParameters = "";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters, true);

                methodName = "set";
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
            break;
        }

        case MessageFieldModel::FieldCategory::stringType:
        case MessageFieldModel::FieldCategory::bytesType:
        case MessageFieldModel::FieldCategory::messageType:
        {
            if (messageFieldModel.requiredness() == MessageFieldModel::Requiredness::repeated)
            {
                methodName = "size";
                methodName += messageFieldModel.namePascal();
                methodReturn = "size_t";
                methodParameters = "";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters, true);

                methodName = messageFieldModel.name();
                methodReturn = "const ";
                methodReturn += fieldType + " &";
                methodParameters = "size_t index";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters, true);

                methodName = "mutable";
                methodName += messageFieldModel.namePascal();
                methodReturn = fieldType + " &";
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
            }
            else
            {
                methodName = "has";
                methodName += messageFieldModel.namePascal();
                methodReturn = "bool";
                methodParameters = "";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters, true);

                methodName = messageFieldModel.name();
                methodReturn = "const ";
                methodReturn += fieldType + " &";
                methodParameters = "";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters, true);

                methodName = "mutable";
                methodName += messageFieldModel.namePascal();
                methodReturn = fieldType + " &";
                methodParameters = "";
                headerFileWriter.writeClassMethodDeclaration(methodName, methodReturn, methodParameters);

                methodName = "set";
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
            }
            break;
        }

        default:
            break;
    }
}

void Protocol::CodeGeneratorCPP::writeMessageFieldBackingFieldsToHeader (CodeWriter & headerFileWriter, const ProtoModel & protoModel,
                                                                         const MessageFieldModel & messageFieldModel) const
{
    string backingFieldName;
    string backingFieldType;
    string fieldType = fullTypeNameInternal(messageFieldModel);

    switch (messageFieldModel.fieldCategory())
    {
        case MessageFieldModel::FieldCategory::boolType:
        case MessageFieldModel::FieldCategory::numericType:
        case MessageFieldModel::FieldCategory::enumType:
        {
            if (messageFieldModel.requiredness() == MessageFieldModel::Requiredness::repeated)
            {
                backingFieldName = "m";
                backingFieldName += messageFieldModel.namePascal() + "Collection";
                backingFieldType = fieldType;
                headerFileWriter.writeClassFieldDeclaration(backingFieldName, backingFieldType);
            }
            else
            {
                backingFieldName = "m";
                backingFieldName += messageFieldModel.namePascal() + "Value";
                backingFieldType = fieldType;
                headerFileWriter.writeClassFieldDeclaration(backingFieldName, backingFieldType);
            }
            break;
        }

        case MessageFieldModel::FieldCategory::stringType:
        case MessageFieldModel::FieldCategory::bytesType:
        {
            if (messageFieldModel.requiredness() == MessageFieldModel::Requiredness::repeated)
            {
                backingFieldName = "m";
                backingFieldName += messageFieldModel.namePascal() + "Collection";
                backingFieldType = fieldType;
                headerFileWriter.writeClassFieldDeclaration(backingFieldName, backingFieldType);
            }
            else
            {
                backingFieldName = "m";
                backingFieldName += messageFieldModel.namePascal() + "Value";
                backingFieldType += fieldType;
                headerFileWriter.writeClassFieldDeclaration(backingFieldName, backingFieldType);
            }
            break;
        }

        case MessageFieldModel::FieldCategory::messageType:
        {
            if (messageFieldModel.requiredness() == MessageFieldModel::Requiredness::repeated)
            {
                backingFieldName = "m";
                backingFieldName += messageFieldModel.namePascal() + "Collection";
                backingFieldType = fieldType;
                headerFileWriter.writeClassFieldDeclaration(backingFieldName, backingFieldType);
            }
            else
            {
                backingFieldName = "m";
                backingFieldName += messageFieldModel.namePascal() + "Value";
                backingFieldType = "std::shared_ptr<";
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

        writeMessageFieldBackingFieldsToHeader(headerFileWriter, protoModel, *messageFieldModel);

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

        writeMessageToSource(sourceFileWriter, protoModel, *messageModel, messageModel->namePascal());

        ++protoMessageBegin;
    }
}

void Protocol::CodeGeneratorCPP::writeMessageToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                       const MessageModel & messageModel, const std::string & className) const
{
    auto messageMessageBegin = messageModel.messages()->cbegin();
    auto messageMessageEnd = messageModel.messages()->cend();
    while (messageMessageBegin != messageMessageEnd)
    {
        auto messageSubModel = *messageMessageBegin;

        string subClassName = className + "_" + messageSubModel->namePascal();
        writeMessageToSource(sourceFileWriter, protoModel, *messageSubModel, subClassName);

        ++messageMessageBegin;
    }

    string fullScope = messageModel.package();
    boost::replace_all(fullScope, ".", "::");
    if (!fullScope.empty())
    {
        fullScope += "::";
    }
    fullScope += className;

    string classDataName = className + "Data";
    string fullDataScope = fullScope + "::";
    fullDataScope += classDataName;

    writeMessageDataConstructorToSource(sourceFileWriter, protoModel, messageModel, classDataName, fullDataScope);

    writeMessageDataDestructorToSource(sourceFileWriter, protoModel, messageModel, classDataName, fullDataScope);

    writeMessageConstructorToSource(sourceFileWriter, protoModel, messageModel, className, fullScope);

    writeMessageCopyConstructorToSource(sourceFileWriter, protoModel, messageModel, className, fullScope);

    writeMessageDestructorToSource(sourceFileWriter, protoModel, messageModel, className, fullScope);

    writeMessageAssignmentOperatorToSource(sourceFileWriter, protoModel, messageModel, className, fullScope);

    writeMessageSwapToSource(sourceFileWriter, protoModel, messageModel, className, fullScope);

    writeMessageClearToSource(sourceFileWriter, protoModel, messageModel, className, fullScope);

    writeMessageParseToSource(sourceFileWriter, protoModel, messageModel, className, fullScope);

    writeMessageSerializeToSource(sourceFileWriter, protoModel, messageModel, className, fullScope);

    writeMessageSizeToSource(sourceFileWriter, protoModel, messageModel, className, fullScope);

    writeMessageValidToSource(sourceFileWriter, protoModel, messageModel, className, fullScope);

    auto messageFieldBegin = messageModel.fields()->cbegin();
    auto messageFieldEnd = messageModel.fields()->cend();
    while (messageFieldBegin != messageFieldEnd)
    {
        auto messageFieldModel = *messageFieldBegin;

        writeMessageFieldToSource(sourceFileWriter, protoModel, *messageFieldModel, className, fullScope);

        ++messageFieldBegin;
    }

    auto oneofBegin = messageModel.oneofs()->cbegin();
    auto oneofEnd = messageModel.oneofs()->cend();
    while (oneofBegin != oneofEnd)
    {
        auto oneofModel = *oneofBegin;

        writeOneofToSource(sourceFileWriter, protoModel, *oneofModel, className, fullScope);
        
        ++oneofBegin;
    }
}

void Protocol::CodeGeneratorCPP::writeMessageDataConstructorToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                                  const MessageModel & messageModel, const std::string & className,
                                                                  const std::string & fullScope) const
{
    string initializationParameters = "";
    bool firstParameter = true;
    auto messageFieldBegin = messageModel.fields()->cbegin();
    auto messageFieldEnd = messageModel.fields()->cend();
    while (messageFieldBegin != messageFieldEnd)
    {
        auto messageFieldModel = *messageFieldBegin;

        string fieldInitialization = messageFieldInitialization(*messageFieldModel);
        if (!fieldInitialization.empty())
        {
            if (!firstParameter)
            {
                initializationParameters += ", ";
            }
            firstParameter = false;

            initializationParameters += fieldInitialization;
        }

        ++messageFieldBegin;
    }

    auto oneofBegin = messageModel.oneofs()->cbegin();
    auto oneofEnd = messageModel.oneofs()->cend();
    while (oneofBegin != oneofEnd)
    {
        auto oneofModel = *oneofBegin;

        messageFieldBegin = oneofModel->fields()->cbegin();
        messageFieldEnd = oneofModel->fields()->cend();
        while (messageFieldBegin != messageFieldEnd)
        {
            auto messageFieldModel = *messageFieldBegin;

            string fieldInitialization = messageFieldInitialization(*messageFieldModel);
            if (!fieldInitialization.empty())
            {
                if (!firstParameter)
                {
                    initializationParameters += ", ";
                }
                firstParameter = false;

                initializationParameters += fieldInitialization;
            }
            
            ++messageFieldBegin;
        }

        ++oneofBegin;
    }

    string methodName = fullScope + "::" + className;
    string methodParameters = "";
    sourceFileWriter.writeConstructorImplementationOpening(methodName, methodParameters, initializationParameters);

    sourceFileWriter.writeMethodImplementationClosing();
}

std::string Protocol::CodeGeneratorCPP::messageFieldInitialization (const MessageFieldModel & messageFieldModel) const
{
    string fieldInitialization;

    if (messageFieldModel.requiredness() == MessageFieldModel::Requiredness::repeated)
    {
        fieldInitialization = "m" + messageFieldModel.namePascal() + "Collection";
    }
    else
    {
        fieldInitialization = "m" + messageFieldModel.namePascal() + "Value";
    }

    switch (messageFieldModel.fieldCategory())
    {
        case MessageFieldModel::FieldCategory::boolType:
        case MessageFieldModel::FieldCategory::numericType:
        {
            if (messageFieldModel.defaultValue().empty())
            {
                return "";
            }
            fieldInitialization += "(" + messageFieldModel.defaultValue() + ")";
            break;
        }

        case MessageFieldModel::FieldCategory::enumType:
        {
            if (messageFieldModel.defaultValue().empty())
            {
                return "";
            }
            string defaultValue = fullTypeName(messageFieldModel) + "::" + messageFieldModel.defaultValue();
            fieldInitialization += "(" + defaultValue + ")";
            break;
        }

        case MessageFieldModel::FieldCategory::stringType:
        {
            if (messageFieldModel.defaultValue().empty())
            {
                return "";
            }
            fieldInitialization += "(\"" + messageFieldModel.defaultValue() + "\")";
            break;
        }

        case MessageFieldModel::FieldCategory::bytesType:
        case MessageFieldModel::FieldCategory::messageType:
        {
            return "";
        }

        default:
            break;
    }

    return fieldInitialization;
}

void Protocol::CodeGeneratorCPP::writeMessageDataDestructorToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                                 const MessageModel & messageModel, const std::string & className,
                                                                 const std::string & fullScope) const
{
    string methodName = fullScope + "::~" + className;
    sourceFileWriter.writeMethodImplementationOpening(methodName);

    sourceFileWriter.writeMethodImplementationClosing();
}

void Protocol::CodeGeneratorCPP::writeMessageConstructorToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                                  const MessageModel & messageModel, const std::string & className,
                                                                  const std::string & fullScope) const
{
    string methodName = fullScope + "::" + className;
    string methodParameters = "";
    string initializationParameters = "mData(new ";
    initializationParameters += className + "Data())";
    sourceFileWriter.writeConstructorImplementationOpening(methodName, methodParameters, initializationParameters);
    
    sourceFileWriter.writeMethodImplementationClosing();
}

void Protocol::CodeGeneratorCPP::writeMessageCopyConstructorToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                                      const MessageModel & messageModel, const std::string & className,
                                                                      const std::string & fullScope) const
{
    string methodName = fullScope + "::" + className;
    string methodReturn = "";
    string methodParameters = "const ";
    methodParameters += className + " & src";
    string initializationParameters = "mData(src.mData)";
    sourceFileWriter.writeConstructorImplementationOpening(methodName, methodParameters, initializationParameters);
    sourceFileWriter.writeMethodImplementationClosing();
}

void Protocol::CodeGeneratorCPP::writeMessageDestructorToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                                 const MessageModel & messageModel, const std::string & className,
                                                                 const std::string & fullScope) const
{
    string methodName = fullScope + "::~" + className;
    sourceFileWriter.writeMethodImplementationOpening(methodName);
    sourceFileWriter.writeMethodImplementationClosing();
}

void Protocol::CodeGeneratorCPP::writeMessageAssignmentOperatorToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                                         const MessageModel & messageModel, const std::string & className,
                                                                         const std::string & fullScope) const
{
    string methodName = fullScope + "::operator =";
    string methodReturn = fullScope + " &";
    string methodParameters = "const ";
    methodParameters += className + " & rhs";
    sourceFileWriter.writeMethodImplementationOpening(methodName, methodReturn, methodParameters);

    string statement = "this == &rhs";
    sourceFileWriter.writeIfOpening(statement);
    statement = "return *this;";
    sourceFileWriter.writeLineIndented(statement);
    sourceFileWriter.writeIfClosing();

    sourceFileWriter.writeBlankLine();

    statement = "mData = rhs.mData;";
    sourceFileWriter.writeLineIndented(statement);

    sourceFileWriter.writeBlankLine();

    statement = "return *this;";
    sourceFileWriter.writeLineIndented(statement);

    sourceFileWriter.writeMethodImplementationClosing();
}

void Protocol::CodeGeneratorCPP::writeMessageSwapToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                           const MessageModel & messageModel, const std::string & className,
                                                           const std::string & fullScope) const
{
    string methodName = fullScope + "::swap";
    string methodReturn = "void";
    string methodParameters = className + " * other";
    sourceFileWriter.writeMethodImplementationOpening(methodName, methodReturn, methodParameters);

    string dataType = "shared_ptr<";
    dataType += className + "Data>";
    string statement = dataType + " thisData(mData);";
    sourceFileWriter.writeLineIndented(statement);
    statement = dataType + " otherData(other->mData);";
    sourceFileWriter.writeLineIndented(statement);

    sourceFileWriter.writeBlankLine();

    statement = "mData = otherData;";
    sourceFileWriter.writeLineIndented(statement);
    statement = "other->mData = thisData;";
    sourceFileWriter.writeLineIndented(statement);

    sourceFileWriter.writeMethodImplementationClosing();
}

void Protocol::CodeGeneratorCPP::writeMessageClearToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                            const MessageModel & messageModel, const std::string & className,
                                                            const std::string & fullScope) const
{
    string methodName = fullScope + "::clear";
    string methodReturn = "void";
    sourceFileWriter.writeMethodImplementationOpening(methodName, methodReturn);

    string statement = "mData.reset(new ";
    statement += className + "Data());";
    sourceFileWriter.writeLineIndented(statement);

    sourceFileWriter.writeMethodImplementationClosing();
}

void Protocol::CodeGeneratorCPP::writeMessageParseToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                            const MessageModel & messageModel, const std::string & className,
                                                            const std::string & fullScope) const
{
    string methodName = fullScope + "::parse";
    string methodReturn = "size_t";
    string methodParameters = "const unsigned char * pData";
    sourceFileWriter.writeMethodImplementationOpening(methodName, methodReturn, methodParameters);

    string statement = "pData == nullptr";
    sourceFileWriter.writeIfOpening(statement);
    statement = "throw std::invalid_argument(\"pData cannot be null.\");";
    sourceFileWriter.writeLineIndented(statement);
    sourceFileWriter.writeIfClosing();

    sourceFileWriter.writeBlankLine();

    statement = "size_t bytesParsed = 0;";
    sourceFileWriter.writeLineIndented(statement);

    statement = "return bytesParsed;";
    sourceFileWriter.writeLineIndented(statement);

    sourceFileWriter.writeMethodImplementationClosing();
}

void Protocol::CodeGeneratorCPP::writeMessageSerializeToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                                const MessageModel & messageModel, const std::string & className,
                                                                const std::string & fullScope) const
{
    string methodName = fullScope + "::serialize";
    string methodReturn = "std::string";
    sourceFileWriter.writeMethodImplementationOpening(methodName, methodReturn, true);

    string statement = "std::string result;";
    sourceFileWriter.writeLineIndented(statement);
    sourceFileWriter.writeBlankLine();

    auto messageFieldBegin = messageModel.fields()->cbegin();
    auto messageFieldEnd = messageModel.fields()->cend();
    while (messageFieldBegin != messageFieldEnd)
    {
        auto messageFieldModel = *messageFieldBegin;

        string fieldValueName = "mData->m";
        fieldValueName += messageFieldModel->namePascal();
        if (messageFieldModel->requiredness() == MessageFieldModel::Requiredness::repeated)
        {
            fieldValueName += "Collection";
        }
        else
        {
            fieldValueName += "Value";
        }

        if (messageFieldModel->fieldCategory() == MessageFieldModel::FieldCategory::messageType &&
            messageFieldModel->requiredness() != MessageFieldModel::Requiredness::repeated)
        {
            statement = fieldValueName + " != nullptr";
            sourceFileWriter.writeIfOpening(statement);
            statement = "result += ";
            statement += fieldValueName + "->serialize();";
            sourceFileWriter.writeLineIndented(statement);
            sourceFileWriter.writeIfClosing();
        }
        else
        {
            statement = "result += ";
            statement += fieldValueName + ".serialize();";
            sourceFileWriter.writeLineIndented(statement);
        }

        sourceFileWriter.writeBlankLine();

        ++messageFieldBegin;
    }

    statement = "result = MuddledManaged::Protocol::PrimitiveEncoding::serializeVariableUnsignedInt32(key()) +";
    sourceFileWriter.writeLineIndented(statement);

    statement = "    MuddledManaged::Protocol::PrimitiveEncoding::serializeVariableUnsignedInt32(static_cast<std::uint32_t>(result.length())) +";
    sourceFileWriter.writeLineIndented(statement);

    statement = "    result;";
    sourceFileWriter.writeLineIndented(statement);

    sourceFileWriter.writeBlankLine();

    statement = "return result;";
    sourceFileWriter.writeLineIndented(statement);

    sourceFileWriter.writeMethodImplementationClosing();
}

void Protocol::CodeGeneratorCPP::writeMessageSizeToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                           const MessageModel & messageModel, const std::string & className,
                                                           const std::string & fullScope) const
{
    string methodName = fullScope + "::size";
    string methodReturn = "size_t";
    sourceFileWriter.writeMethodImplementationOpening(methodName, methodReturn, true);

    string statement = "size_t result = 0;";
    sourceFileWriter.writeLineIndented(statement);
    sourceFileWriter.writeBlankLine();

    auto messageFieldBegin = messageModel.fields()->cbegin();
    auto messageFieldEnd = messageModel.fields()->cend();
    while (messageFieldBegin != messageFieldEnd)
    {
        auto messageFieldModel = *messageFieldBegin;

        string fieldValueName = "mData->m";
        fieldValueName += messageFieldModel->namePascal();
        if (messageFieldModel->requiredness() == MessageFieldModel::Requiredness::repeated)
        {
            fieldValueName += "Collection";
        }
        else
        {
            fieldValueName += "Value";
        }

        if (messageFieldModel->fieldCategory() == MessageFieldModel::FieldCategory::messageType &&
            messageFieldModel->requiredness() != MessageFieldModel::Requiredness::repeated)
        {
            statement = fieldValueName + " != nullptr";
            sourceFileWriter.writeIfOpening(statement);
            statement = "result += ";
            statement += fieldValueName + "->size();";
            sourceFileWriter.writeLineIndented(statement);
            sourceFileWriter.writeIfClosing();
        }
        else
        {
            statement = "result += ";
            statement += fieldValueName + ".size();";
            sourceFileWriter.writeLineIndented(statement);
        }

        sourceFileWriter.writeBlankLine();
        
        ++messageFieldBegin;
    }

    statement = "result += MuddledManaged::Protocol::PrimitiveEncoding::sizeVariableUnsignedInt32(static_cast<std::uint32_t>(result));";
    sourceFileWriter.writeLineIndented(statement);

    statement = "result += MuddledManaged::Protocol::PrimitiveEncoding::sizeVariableUnsignedInt32(key());";
    sourceFileWriter.writeLineIndented(statement);

    sourceFileWriter.writeBlankLine();

    statement = "return result;";
    sourceFileWriter.writeLineIndented(statement);
    
    sourceFileWriter.writeMethodImplementationClosing();
}

void Protocol::CodeGeneratorCPP::writeMessageValidToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                              const MessageModel & messageModel, const std::string & className,
                                                              const std::string & fullScope) const
{
    string methodName = fullScope + "::valid";
    string methodReturn = "bool";
    sourceFileWriter.writeMethodImplementationOpening(methodName, methodReturn, true);

    string statement;
    auto messageFieldBegin = messageModel.fields()->cbegin();
    auto messageFieldEnd = messageModel.fields()->cend();
    while (messageFieldBegin != messageFieldEnd)
    {
        auto messageFieldModel = *messageFieldBegin;

        string fieldValueName = "mData->m";
        fieldValueName += messageFieldModel->namePascal();
        if (messageFieldModel->requiredness() == MessageFieldModel::Requiredness::repeated)
        {
            fieldValueName += "Collection";
        }
        else
        {
            fieldValueName += "Value";
        }

        if (messageFieldModel->fieldCategory() == MessageFieldModel::FieldCategory::messageType &&
            messageFieldModel->requiredness() != MessageFieldModel::Requiredness::repeated)
        {
            statement = fieldValueName + " != nullptr && ";
            statement += "!" + fieldValueName + "->valid()";
            sourceFileWriter.writeIfOpening(statement);
            statement = "return false;";
            sourceFileWriter.writeLineIndented(statement);
            sourceFileWriter.writeIfClosing();
        }
        else
        {
            statement = "!" + fieldValueName + ".valid()";
            sourceFileWriter.writeIfOpening(statement);
            statement = "return false;";
            sourceFileWriter.writeLineIndented(statement);
            sourceFileWriter.writeIfClosing();
        }

        ++messageFieldBegin;
    }
    statement = "return true;";
    sourceFileWriter.writeLineIndented(statement);

    sourceFileWriter.writeMethodImplementationClosing();
}

void Protocol::CodeGeneratorCPP::writeMessageFieldToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                            const MessageFieldModel & messageFieldModel, const std::string & className,
                                                            const std::string & fullScope) const
{
    if (messageFieldModel.requiredness() == MessageFieldModel::Requiredness::repeated)
    {
        writeMessageFieldSizeRepeatedToSource(sourceFileWriter, protoModel, messageFieldModel, className, fullScope);

        writeMessageFieldGetRepeatedToSource(sourceFileWriter, protoModel, messageFieldModel, className, fullScope);

        writeMessageFieldGetMutableRepeatedToSource(sourceFileWriter, protoModel, messageFieldModel, className, fullScope);

        writeMessageFieldSetRepeatedToSource(sourceFileWriter, protoModel, messageFieldModel, className, fullScope);

        writeMessageFieldAddRepeatedToSource(sourceFileWriter, protoModel, messageFieldModel, className, fullScope);

        writeMessageFieldClearRepeatedToSource(sourceFileWriter, protoModel, messageFieldModel, className, fullScope);
    }
    else
    {
        writeMessageFieldHasToSource(sourceFileWriter, protoModel, messageFieldModel, className, fullScope);

        writeMessageFieldGetToSource(sourceFileWriter, protoModel, messageFieldModel, className, fullScope);

        writeMessageFieldGetMutableToSource(sourceFileWriter, protoModel, messageFieldModel, className, fullScope);

        writeMessageFieldSetToSource(sourceFileWriter, protoModel, messageFieldModel, className, fullScope);

        writeMessageFieldClearToSource(sourceFileWriter, protoModel, messageFieldModel, className, fullScope);
    }
}

void Protocol::CodeGeneratorCPP::writeOneofToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                     const OneofModel & oneofModel, const std::string & className,
                                                     const std::string & fullScope) const
{
    auto messageFieldBegin = oneofModel.fields()->cbegin();
    auto messageFieldEnd = oneofModel.fields()->cend();
    while (messageFieldBegin != messageFieldEnd)
    {
        auto messageFieldModel = *messageFieldBegin;

        writeMessageFieldToSource(sourceFileWriter, protoModel, *messageFieldModel, className, fullScope);

        ++messageFieldBegin;
    }
}

void Protocol::CodeGeneratorCPP::writeMessageFieldSizeRepeatedToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                                        const MessageFieldModel & messageFieldModel, const std::string & className,
                                                                        const std::string & fullScope) const
{
    string methodName = fullScope + "::size";
    methodName += messageFieldModel.namePascal();
    string methodReturn = "size_t";
    string methodParameters = "";
    sourceFileWriter.writeMethodImplementationOpening(methodName, methodReturn, methodParameters, true);

    switch (messageFieldModel.fieldCategory())
    {
        case MessageFieldModel::FieldCategory::numericType:
        case MessageFieldModel::FieldCategory::enumType:
        {
            break;
        }

        case MessageFieldModel::FieldCategory::stringType:
        case MessageFieldModel::FieldCategory::bytesType:
        case MessageFieldModel::FieldCategory::messageType:
        {
            break;
        }
            
        default:
            break;
    }
    
    sourceFileWriter.writeMethodImplementationClosing();
}

void Protocol::CodeGeneratorCPP::writeMessageFieldGetRepeatedToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                                       const MessageFieldModel & messageFieldModel, const std::string & className,
                                                                       const std::string & fullScope) const
{
    string fieldType = fullTypeName(messageFieldModel);
    string methodName = fullScope + "::";
    methodName += messageFieldModel.name();
    string methodReturn = "";
    string methodParameters = "size_t index";

    switch (messageFieldModel.fieldCategory())
    {
        case MessageFieldModel::FieldCategory::numericType:
        case MessageFieldModel::FieldCategory::enumType:
        {
            methodReturn += fieldType;
            sourceFileWriter.writeMethodImplementationOpening(methodName, methodReturn, methodParameters, true);

            sourceFileWriter.writeMethodImplementationClosing();
            break;
        }

        case MessageFieldModel::FieldCategory::stringType:
        case MessageFieldModel::FieldCategory::bytesType:
        case MessageFieldModel::FieldCategory::messageType:
        {
            methodReturn += "const ";
            methodReturn += fieldType + " &";
            sourceFileWriter.writeMethodImplementationOpening(methodName, methodReturn, methodParameters, true);

            sourceFileWriter.writeMethodImplementationClosing();
            break;
        }

        default:
            break;
    }
}

void Protocol::CodeGeneratorCPP::writeMessageFieldGetMutableRepeatedToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                                              const MessageFieldModel & messageFieldModel, const std::string & className,
                                                                              const std::string & fullScope) const
{
    string fieldType = fullTypeName(messageFieldModel);
    string methodName = fullScope + "::mutable";
    methodName += messageFieldModel.namePascal();
    string methodReturn = fieldType + " &";
    string methodParameters = "size_t index";

    switch (messageFieldModel.fieldCategory())
    {
        case MessageFieldModel::FieldCategory::numericType:
        case MessageFieldModel::FieldCategory::enumType:
        {
            break;
        }

        case MessageFieldModel::FieldCategory::stringType:
        case MessageFieldModel::FieldCategory::bytesType:
        case MessageFieldModel::FieldCategory::messageType:
        {
            sourceFileWriter.writeMethodImplementationOpening(methodName, methodReturn, methodParameters);

            sourceFileWriter.writeMethodImplementationClosing();
            break;
        }

        default:
            break;
    }
}

void Protocol::CodeGeneratorCPP::writeMessageFieldSetRepeatedToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                                       const MessageFieldModel & messageFieldModel, const std::string & className,
                                                                       const std::string & fullScope) const
{
    string fieldType = fullTypeName(messageFieldModel);
    string methodName = fullScope + "::set";
    methodName += messageFieldModel.namePascal();
    string methodReturn = "void";
    string methodParameters = "size_t index, ";

    switch (messageFieldModel.fieldCategory())
    {
        case MessageFieldModel::FieldCategory::numericType:
        case MessageFieldModel::FieldCategory::enumType:
        {
            methodParameters += fieldType + " value";
            sourceFileWriter.writeMethodImplementationOpening(methodName, methodReturn, methodParameters);

            sourceFileWriter.writeMethodImplementationClosing();
            break;
        }

        case MessageFieldModel::FieldCategory::stringType:
        case MessageFieldModel::FieldCategory::bytesType:
        case MessageFieldModel::FieldCategory::messageType:
        {
            methodParameters += "const ";
            methodParameters += fieldType + " & value";
            sourceFileWriter.writeMethodImplementationOpening(methodName, methodReturn, methodParameters);

            sourceFileWriter.writeMethodImplementationClosing();
            break;
        }

        default:
            break;
    }
}

void Protocol::CodeGeneratorCPP::writeMessageFieldAddRepeatedToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                                       const MessageFieldModel & messageFieldModel, const std::string & className,
                                                                       const std::string & fullScope) const
{
    string fieldType = fullTypeName(messageFieldModel);
    string methodName = fullScope + "::add";
    methodName += messageFieldModel.namePascal();
    string methodReturn = "void";
    string methodParameters = "";

    switch (messageFieldModel.fieldCategory())
    {
        case MessageFieldModel::FieldCategory::numericType:
        case MessageFieldModel::FieldCategory::enumType:
        {
            methodParameters += fieldType + " value";
            sourceFileWriter.writeMethodImplementationOpening(methodName, methodReturn, methodParameters);

            sourceFileWriter.writeMethodImplementationClosing();
            break;
        }

        case MessageFieldModel::FieldCategory::stringType:
        case MessageFieldModel::FieldCategory::bytesType:
        case MessageFieldModel::FieldCategory::messageType:
        {
            methodParameters += "const ";
            methodParameters += fieldType + " & value";
            sourceFileWriter.writeMethodImplementationOpening(methodName, methodReturn, methodParameters);

            sourceFileWriter.writeMethodImplementationClosing();
            break;
        }

        default:
            break;
    }
}

void Protocol::CodeGeneratorCPP::writeMessageFieldClearRepeatedToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                                         const MessageFieldModel & messageFieldModel, const std::string & className,
                                                                         const std::string & fullScope) const
{
    string methodName = fullScope + "::clear";
    methodName += messageFieldModel.namePascal();
    string methodReturn = "void";
    string methodParameters = "";
    sourceFileWriter.writeMethodImplementationOpening(methodName, methodReturn, methodParameters);

    switch (messageFieldModel.fieldCategory())
    {
        case MessageFieldModel::FieldCategory::numericType:
        case MessageFieldModel::FieldCategory::enumType:
        {
            break;
        }

        case MessageFieldModel::FieldCategory::stringType:
        case MessageFieldModel::FieldCategory::bytesType:
        case MessageFieldModel::FieldCategory::messageType:
        {
            break;
        }

        default:
            break;
    }

    sourceFileWriter.writeMethodImplementationClosing();
}

void Protocol::CodeGeneratorCPP::writeMessageFieldHasToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                               const MessageFieldModel & messageFieldModel, const std::string & className,
                                                               const std::string & fullScope) const
{
    string methodName = fullScope + "::has";
    methodName += messageFieldModel.namePascal();
    string methodReturn = "bool";
    string methodParameters = "";
    sourceFileWriter.writeMethodImplementationOpening(methodName, methodReturn, methodParameters, true);

    switch (messageFieldModel.fieldCategory())
    {
        case MessageFieldModel::FieldCategory::numericType:
        case MessageFieldModel::FieldCategory::enumType:
        {
            break;
        }

        case MessageFieldModel::FieldCategory::stringType:
        case MessageFieldModel::FieldCategory::bytesType:
        case MessageFieldModel::FieldCategory::messageType:
        {
            break;
        }

        default:
            break;
    }

    sourceFileWriter.writeMethodImplementationClosing();
}

void Protocol::CodeGeneratorCPP::writeMessageFieldGetToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                               const MessageFieldModel & messageFieldModel, const std::string & className,
                                                               const std::string & fullScope) const
{
    string fieldType = fullTypeName(messageFieldModel);
    string methodName = fullScope + "::";
    methodName += messageFieldModel.name();
    string methodReturn = "";
    string methodParameters = "";

    switch (messageFieldModel.fieldCategory())
    {
        case MessageFieldModel::FieldCategory::numericType:
        case MessageFieldModel::FieldCategory::enumType:
        {
            methodReturn += fieldType;
            sourceFileWriter.writeMethodImplementationOpening(methodName, methodReturn, methodParameters, true);

            sourceFileWriter.writeMethodImplementationClosing();
            break;
        }

        case MessageFieldModel::FieldCategory::stringType:
        case MessageFieldModel::FieldCategory::bytesType:
        case MessageFieldModel::FieldCategory::messageType:
        {
            methodReturn += "const ";
            methodReturn += fieldType + " &";
            sourceFileWriter.writeMethodImplementationOpening(methodName, methodReturn, methodParameters, true);

            sourceFileWriter.writeMethodImplementationClosing();
            break;
        }

        default:
            break;
    }
}

void Protocol::CodeGeneratorCPP::writeMessageFieldGetMutableToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                                      const MessageFieldModel & messageFieldModel, const std::string & className,
                                                                      const std::string & fullScope) const
{
    string fieldType = fullTypeName(messageFieldModel);
    string methodName = fullScope + "::mutable";
    methodName += messageFieldModel.namePascal();
    string methodReturn = fieldType + " &";
    string methodParameters = "";

    switch (messageFieldModel.fieldCategory())
    {
        case MessageFieldModel::FieldCategory::numericType:
        case MessageFieldModel::FieldCategory::enumType:
        {
            break;
        }

        case MessageFieldModel::FieldCategory::stringType:
        case MessageFieldModel::FieldCategory::bytesType:
        case MessageFieldModel::FieldCategory::messageType:
        {
            sourceFileWriter.writeMethodImplementationOpening(methodName, methodReturn, methodParameters);

            sourceFileWriter.writeMethodImplementationClosing();
            break;
        }

        default:
            break;
    }
}

void Protocol::CodeGeneratorCPP::writeMessageFieldSetToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                               const MessageFieldModel & messageFieldModel, const std::string & className,
                                                               const std::string & fullScope) const
{
    string fieldType = fullTypeName(messageFieldModel);
    string methodName = fullScope + "::set";
    methodName += messageFieldModel.namePascal();
    string methodReturn = "void";
    string methodParameters = "";

    switch (messageFieldModel.fieldCategory())
    {
        case MessageFieldModel::FieldCategory::numericType:
        case MessageFieldModel::FieldCategory::enumType:
        {
            methodParameters += fieldType + " value";
            sourceFileWriter.writeMethodImplementationOpening(methodName, methodReturn, methodParameters);

            sourceFileWriter.writeMethodImplementationClosing();
            break;
        }

        case MessageFieldModel::FieldCategory::stringType:
        case MessageFieldModel::FieldCategory::bytesType:
        case MessageFieldModel::FieldCategory::messageType:
        {
            methodParameters += "const ";
            methodParameters += fieldType + " & value";
            sourceFileWriter.writeMethodImplementationOpening(methodName, methodReturn, methodParameters);

            sourceFileWriter.writeMethodImplementationClosing();
            break;
        }

        default:
            break;
    }
}

void Protocol::CodeGeneratorCPP::writeMessageFieldClearToSource (CodeWriter & sourceFileWriter, const ProtoModel & protoModel,
                                                                 const MessageFieldModel & messageFieldModel, const std::string & className,
                                                                 const std::string & fullScope) const
{
    string methodName = fullScope + "::clear";
    methodName += messageFieldModel.namePascal();
    string methodReturn = "void";
    string methodParameters = "";
    sourceFileWriter.writeMethodImplementationOpening(methodName, methodReturn, methodParameters);

    switch (messageFieldModel.fieldCategory())
    {
        case MessageFieldModel::FieldCategory::numericType:
        case MessageFieldModel::FieldCategory::enumType:
        {
            break;
        }

        case MessageFieldModel::FieldCategory::stringType:
        case MessageFieldModel::FieldCategory::bytesType:
        case MessageFieldModel::FieldCategory::messageType:
        {
            break;
        }

        default:
            break;
    }

    sourceFileWriter.writeMethodImplementationClosing();
}

string Protocol::CodeGeneratorCPP::fullTypeName (const MessageFieldModel & messageFieldModel) const
{
    string fieldType = messageFieldModel.fieldType();
    if (fieldType == "bool")
    {
        return "bool";
    }
    if (fieldType == "string")
    {
        return "std::string";
    }
    if (fieldType == "double")
    {
        return "double";
    }
    if (fieldType == "float")
    {
        return "float";
    }
    if (fieldType == "int32")
    {
        return "int32_t";
    }
    if (fieldType == "int64")
    {
        return "int64_t";
    }
    if (fieldType == "uint32")
    {
        return "uint32_t";
    }
    if (fieldType == "uint64")
    {
        return "uint64_t";
    }
    if (fieldType == "sint32")
    {
        return "int32_t";
    }
    if (fieldType == "sint64")
    {
        return "int64_t";
    }
    if (fieldType == "fixed32")
    {
        return "int32_t";
    }
    if (fieldType == "fixed64")
    {
        return "int64_t";
    }
    if (fieldType == "sfixed32")
    {
        return "int32_t";
    }
    if (fieldType == "sfixed64")
    {
        return "int64_t";
    }
    if (fieldType == "bytes")
    {
        return "std::string";
    }

    boost::replace_all(fieldType, ".", "_");
    string fieldTypePackage = messageFieldModel.fieldTypePackage();
    boost::replace_all(fieldTypePackage, ".", "::");
    if (!fieldTypePackage.empty())
    {
        fieldTypePackage += "::";
    }
    fieldType = fieldTypePackage + fieldType;
    return fieldType;
}

string Protocol::CodeGeneratorCPP::fullTypeNameInternal (const MessageFieldModel & messageFieldModel) const
{
    string fieldType = messageFieldModel.fieldType();
    if (fieldType == "bool")
    {
        fieldType = mBaseClassesNamespace + "::ProtoBool";
        if (messageFieldModel.requiredness() == MessageFieldModel::Requiredness::repeated)
        {
            fieldType += "Collection";
        }
        return fieldType;
    }
    if (fieldType == "string")
    {
        fieldType = mBaseClassesNamespace + "::ProtoString";
        if (messageFieldModel.requiredness() == MessageFieldModel::Requiredness::repeated)
        {
            fieldType += "Collection";
        }
        return fieldType;
    }
    if (fieldType == "double")
    {
        fieldType = mBaseClassesNamespace + "::ProtoDouble";
        if (messageFieldModel.requiredness() == MessageFieldModel::Requiredness::repeated)
        {
            fieldType += "Collection";
        }
        return fieldType;
    }
    if (fieldType == "float")
    {
        fieldType = mBaseClassesNamespace + "::ProtoFloat";
        if (messageFieldModel.requiredness() == MessageFieldModel::Requiredness::repeated)
        {
            fieldType += "Collection";
        }
        return fieldType;
    }
    if (fieldType == "int32")
    {
        fieldType = mBaseClassesNamespace + "::ProtoInt32";
        if (messageFieldModel.requiredness() == MessageFieldModel::Requiredness::repeated)
        {
            fieldType += "Collection";
        }
        return fieldType;
    }
    if (fieldType == "int64")
    {
        fieldType = mBaseClassesNamespace + "::ProtoInt64";
        if (messageFieldModel.requiredness() == MessageFieldModel::Requiredness::repeated)
        {
            fieldType += "Collection";
        }
        return fieldType;
    }
    if (fieldType == "uint32")
    {
        fieldType = mBaseClassesNamespace + "::ProtoUnsignedInt32";
        if (messageFieldModel.requiredness() == MessageFieldModel::Requiredness::repeated)
        {
            fieldType += "Collection";
        }
        return fieldType;
    }
    if (fieldType == "uint64")
    {
        fieldType = mBaseClassesNamespace + "::ProtoUnsignedInt64";
        if (messageFieldModel.requiredness() == MessageFieldModel::Requiredness::repeated)
        {
            fieldType += "Collection";
        }
        return fieldType;
    }
    if (fieldType == "sint32")
    {
        fieldType = mBaseClassesNamespace + "::ProtoSignedInt32";
        if (messageFieldModel.requiredness() == MessageFieldModel::Requiredness::repeated)
        {
            fieldType += "Collection";
        }
        return fieldType;
    }
    if (fieldType == "sint64")
    {
        fieldType = mBaseClassesNamespace + "::ProtoSignedInt64";
        if (messageFieldModel.requiredness() == MessageFieldModel::Requiredness::repeated)
        {
            fieldType += "Collection";
        }
        return fieldType;
    }
    if (fieldType == "fixed32")
    {
        fieldType = mBaseClassesNamespace + "::ProtoFixedInt32";
        if (messageFieldModel.requiredness() == MessageFieldModel::Requiredness::repeated)
        {
            fieldType += "Collection";
        }
        return fieldType;
    }
    if (fieldType == "fixed64")
    {
        fieldType = mBaseClassesNamespace + "::ProtoFixedInt64";
        if (messageFieldModel.requiredness() == MessageFieldModel::Requiredness::repeated)
        {
            fieldType += "Collection";
        }
        return fieldType;
    }
    if (fieldType == "sfixed32")
    {
        fieldType = mBaseClassesNamespace + "::ProtoFixedSignedInt32";
        if (messageFieldModel.requiredness() == MessageFieldModel::Requiredness::repeated)
        {
            fieldType += "Collection";
        }
        return fieldType;
    }
    if (fieldType == "sfixed64")
    {
        fieldType = mBaseClassesNamespace + "::ProtoFixedSignedInt64";
        if (messageFieldModel.requiredness() == MessageFieldModel::Requiredness::repeated)
        {
            fieldType += "Collection";
        }
        return fieldType;
    }
    if (fieldType == "bytes")
    {
        fieldType = mBaseClassesNamespace + "::ProtoBytes";
        if (messageFieldModel.requiredness() == MessageFieldModel::Requiredness::repeated)
        {
            fieldType += "Collection";
        }
        return fieldType;
    }

    boost::replace_all(fieldType, ".", "_");
    string fieldTypePackage = messageFieldModel.fieldTypePackage();
    boost::replace_all(fieldTypePackage, ".", "::");
    if (!fieldTypePackage.empty())
    {
        fieldTypePackage += "::";
    }
    fieldType = fieldTypePackage + fieldType;

    if (messageFieldModel.fieldCategory() == MessageFieldModel::FieldCategory::enumType)
    {
        if (messageFieldModel.requiredness() == MessageFieldModel::Requiredness::repeated)
        {
            fieldType = mBaseClassesNamespace + "::ProtoEnumCollection<" + fieldType + ">";
        }
        else
        {
            fieldType = mBaseClassesNamespace + "::ProtoEnum<" + fieldType + ">";
        }
        return fieldType;
    }

    if (messageFieldModel.requiredness() == MessageFieldModel::Requiredness::repeated)
    {
        fieldType = mBaseClassesNamespace + "::ProtoMessageCollection<" + fieldType + ">";
    }

    return fieldType;
}
