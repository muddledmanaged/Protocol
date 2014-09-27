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

namespace MuddledManaged
{
    namespace Protocol
    {
        class TokenReader
        {
        private:
            struct TokenReaderData
            {
                TokenReaderData (std::ifstream * protoStream);

                void reset ();
                
                // All begin iterators share this data;
                bool mEnd;
                bool mStringMode;
                char mDelimiter;
                std::string mCurrentToken;
                std::unique_ptr<std::ifstream> mProtoStream;
            };

        public:
            class TokenIterator
            {
            private:
                static const std::string Whitespace;
                static const std::string Delimiters;

            public:
                TokenIterator (); // Constructs an end iterator.
                TokenIterator (const TokenIterator & src);

                TokenIterator & operator = (const TokenIterator & rhs);

                bool operator == (const TokenIterator & rhs) const;
                bool operator != (const TokenIterator & rhs) const;

                TokenIterator & operator ++ ();

                std::string operator * () const;
                const std::string * operator -> () const;

            private:
                friend class TokenReader;
                
                TokenIterator (TokenReaderData * pData); // Constructs a begin iterator.

                void moveNext ();

                bool atEnd () const;

                TokenIterator operator ++ (int) = delete; // We don't support this.

                TokenReaderData * mpData;
            };

            typedef TokenIterator iterator;

            TokenReader (const std::string & protoFileName);
            ~TokenReader ();

            iterator begin ();
            iterator end ();

        private:
            std::unique_ptr<TokenReaderData> mData;
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_TokenReader_h
