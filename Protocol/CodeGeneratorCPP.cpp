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

void Protocol::CodeGeneratorCPP::generateCode (const string & outputFolder, const ProtoModel & model, const std::string & projectName) const
{
    filesystem::path outputPath(outputFolder);
    filesystem::path modelPath(model.fileName());
    filesystem::path headerPath(outputPath / filesystem::change_extension(modelPath, mHeaderFileExtension));
    filesystem::path sourcePath(outputPath / filesystem::change_extension(modelPath, mSourceFileExtension));

    filesystem::create_directory(outputFolder);
    filesystem::ofstream headerFile(headerPath, ios::out | ios::trunc);
    CodeWriter headerFileWriter(headerFile);
    filesystem::ofstream sourceFile(sourcePath, ios::out | ios::trunc);
    CodeWriter sourceFileWriter(sourceFile);

    headerFileWriter.writeLine(mHeaderFileProlog);
    headerFileWriter.writeHeaderIncludeBlockOpening(headerIncludeBlockText(model, projectName));

    writeProtoEnumsToHeader(headerFileWriter, model);

    headerFileWriter.writeHeaderIncludeBlockClosing();

    sourceFileWriter.writeLine(mSourceFileProlog);
}

string Protocol::CodeGeneratorCPP::headerIncludeBlockText (const ProtoModel & model, const std::string & projectName) const
{
    string text = projectName;
    if (!text.empty())
    {
        text += "_";
    }

    filesystem::path modelPath(model.fileName());
    text += filesystem::basename(modelPath.filename());
    text += "_h";

    return text;
}

void Protocol::CodeGeneratorCPP::writeProtoEnumsToHeader (CodeWriter & headerFileWriter, const ProtoModel & model) const
{
    auto protoEnumBegin = model.enums()->cbegin();
    auto protoEnumEnd = model.enums()->cend();
    while (protoEnumBegin != protoEnumEnd)
    {
        auto enumModel = *protoEnumBegin;
        headerFileWriter.writeEnumOpening(enumModel->name());

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
