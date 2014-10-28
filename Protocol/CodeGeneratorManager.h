//
//  CodeGeneratorManager.h
//  Protocol
//
//  Created by Wahid Tanner on 10/17/14.
//

#ifndef Protocol_CodeGeneratorManager_h
#define Protocol_CodeGeneratorManager_h

#include <memory>
#include <string>
#include <unordered_map>

#include "CodeGeneratorInterface.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class CodeGeneratorManager
        {
        public:
            typedef std::shared_ptr<const CodeGeneratorInterface> SPCodeGeneratorInterface;
            typedef std::unordered_map<std::string, SPCodeGeneratorInterface> CodeGeneratorMap;

            ~CodeGeneratorManager ();

            static CodeGeneratorManager * instance ();

            const SPCodeGeneratorInterface generator (const std::string & language) const;

        private:
            CodeGeneratorManager ();
            CodeGeneratorManager (const CodeGeneratorManager & src) = delete;
            CodeGeneratorManager & operator = (const CodeGeneratorManager & rhs) = delete;

            CodeGeneratorMap mGeneratorMap;
        };

    } // namespace Protocol
    
} // namespace MuddledManaged

#endif // Protocol_CodeGeneratorManager_h
