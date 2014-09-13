//
//  Token.h
//  Protocol
//
//  Created by Wahid Tanner on 9/11/14.
//

#ifndef Protocol_Token_h
#define Protocol_Token_h

#include <iostream>
#include <string>

namespace MuddledManaged
{
    namespace Protocol
    {
        class Token
        {
        public:
            Token (const std::string & text = "", char endingDelimiter = '\0')
            : mText(text), mEndingDelimiter(endingDelimiter)
            { }

            Token (const Token & src)
            : mText(src.text()), mEndingDelimiter(src.endingDelimiter())
            { }

            const std::string & text () const
            {
                return mText;
            }

            const char endingDelimiter () const
            {
                return mEndingDelimiter;
            }

        private:
            const std::string mText;
            const char mEndingDelimiter;
        };

        std::ostream & operator << (std::ostream & stream, const Token & token);

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_Token_h
