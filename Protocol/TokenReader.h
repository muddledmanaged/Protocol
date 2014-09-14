//
//  TokenReader.h
//  Protocol
//
//  Created by Wahid Tanner on 9/11/14.
//

#ifndef Protocol_TokenReader_h
#define Protocol_TokenReader_h

#include <fstream>
#include <memory>
#include <string>

#include "Token.h"

namespace MuddledManaged
{
    namespace Protocol
    {
        class TokenReader
        {
        public:
            class TokenIterator
            {
            private:
                static const std::string Whitespace;
                static const std::string Delimiters;

            public:
                bool operator != (const TokenIterator & rhs) const;

                TokenIterator & operator ++ ();

                Token & operator * ();
                const Token & operator * () const;
                
                Token * operator -> ();
                const Token * operator -> () const;

                friend class TokenReader;

            private:
                TokenIterator (); // Constructs an end iterator.
                TokenIterator (std::ifstream * protoStream); // Constructs a begin iterator.
                TokenIterator (const TokenIterator & src);

                TokenIterator & operator = (const TokenIterator & rhs);

                void moveNext ();

                TokenIterator operator ++ (int) = delete; // We don't support this.

                bool mEnd;
                bool mStringTokenStarted;
                std::ifstream * mpProtoStream;
                std::shared_ptr<Token> mCurrent;
            };

            typedef TokenIterator iterator;

            TokenReader (const std::string & protoFileName);
            ~TokenReader ();

            iterator begin ();
            iterator end ();

        private:
            std::unique_ptr<std::ifstream> mProtoStream;
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_TokenReader_h
