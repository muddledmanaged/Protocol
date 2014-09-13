//
//  TokenReader.cpp
//  Protocol
//
//  Created by Wahid Tanner on 9/11/14.
//

#include "TokenReader.h"

using namespace std;

const string TokenReader::TokenIterator::Whitespace = " \t\r\n";
const string TokenReader::TokenIterator::Delimiters = "{}[]=;\"";

TokenReader::TokenIterator::TokenIterator ()
: mEnd(true), mpProtoStream(nullptr), mCurrent(new Token()), mStringTokenStarted(false)
{
}

TokenReader::TokenIterator::TokenIterator (ifstream * protoStream)
: mEnd(false), mpProtoStream(protoStream), mCurrent(new Token()), mStringTokenStarted(false)
{
    // Advance to the first token right away. There will always be a first
    // token even if it is empty.
    moveNext();
}

bool TokenReader::TokenIterator::operator != (const TokenIterator & rhs) const
{
    if (!mEnd || !rhs.mEnd)
    {
        return true;
    }
    return false;
}

void TokenReader::moveNext ()
{
    if (mpProtoStream != nullptr)
    {
        string text;
        char delimiter = '\0';

        bool delimiterFound = false;
        bool needSpace = false;
        bool textFound = false;
        bool previousForwardSlash = false;
        bool previousStar = false;
        bool previousEscape = false;
        bool ignoreToEndOfLine = false;
        bool ignoreToEndOfComment = false;
        char c;
        while (mpProtoStream->get(c))
        {
            if (mStringTokenStarted)
            {
                // An opening quote was found at the end of the last token. That
                // begins string processing for this token until the end quote is
                // found or the end of the line. Strings are not allowed to span
                // lines, so if we find a newline before the end quote, then return
                // what we have and stop further token reading.
                if (c == '\n')
                {
                    break;
                }

                if (c == '\\')
                {
                    if (previousEscape)
                    {
                        text += "\\\\";
                        previousEscape = false;
                    }
                    else
                    {
                        previousEscape = true;
                    }
                    continue;
                }

                if (c != '\"' || previousEscape)
                {
                    text += '\\';
                    text += c;
                    previousEscape = false;
                    continue;
                }

                delimiter = c;
                delimiterFound = true;
                mStringTokenStarted = false;
                break;
            }

            if (ignoreToEndOfComment)
            {
                if (c == '/' && previousStar)
                {
                    ignoreToEndOfComment = false;
                }
                else if (c == '*')
                {
                    previousStar = true;
                }
                previousStar = false;
                continue;
            }

            if (ignoreToEndOfLine)
            {
                if (c == '\n')
                {
                    ignoreToEndOfLine = false;
                }
                continue;
            }

            string::size_type index = Delimiters.find(c);
            if (index == str::npos)
            {
                index = Whitespace.find(c);
                if (index == str::npos)
                {
                    if (c == '/')
                    {
                        if (previousForwardSlash)
                        {
                            // This is a single-line comment. There could still
                            // be text on the same line before the comment.
                            previousForwardSlash = false;
                            ignoreToEndOfLine = true;
                            continue;
                        }
                        previousForwardSlash = true;
                        continue;
                    }
                    else
                    {
                        if (c == '*' && previousForwardSlash)
                        {
                            // This is a potential multi-line comment. There could still
                            // be text on the same line before or after the comment.
                            previousForwardSlash = false;
                            ignoreToEndOfComment = true;
                            continue;
                        }

                        textFound = true;
                        if (needSpace)
                        {
                            text += ' ';
                            needSpace = false;
                        }
                        if (previousForwardSlash)
                        {
                            text += '/';
                        }
                        text += c;
                    }
                }
                else if (previousForwardSlash)
                {
                    // This is a single forward slash followed by whitespace. There
                    // may or may not have been whitespace before the forward slash.
                    textFound = true;
                    if (needSpace)
                    {
                        text += ' ';
                    }
                    text += '/';
                    needSpace = true;
                    previousForwardSlash = false;
                }
                else if (textFound)
                {
                    // This is any other whitespace. We don't add any whitespace yet
                    // to the text until more text is found. Multiple whitespace
                    // characters will eventually be collapsed to a single space
                    // if needed.
                    needSpace = true;
                }
            }
            else
            {
                if (c == '\"')
                {
                    // This will cause the next token to be processed as a string.
                    mStringTokenStarted = true;
                }

                if (previousForwardSlash)
                {
                    text += '/';
                }

                delimiter = c;
                delimiterFound = true;
                break;
            }
        }
        if (!delimiterFound)
        {
            mpProtoStream = nullptr;
        }

        unique_ptr<Token> nextToken(new Token(text, delimiter));
        mCurrent = nextToken;
    }
}

TokenReader::TokenIterator & TokenReader::TokenIterator::operator ++ ()
{
    moveNext();

    if (mpProtoStream == nullptr)
    {
        mEnd = true;
    }

    return *this;
}

Token & TokenReader::TokenIterator::operator * ()
{
    return *mCurrent;
}

const Token & TokenReader::TokenIterator::operator * () const
{
    return *mCurrent;
}

Token * TokenReader::TokenIterator::operator -> ()
{
    return mCurrent->get();
}

const Token * TokenReader::TokenIterator::operator -> () const
{
    return mCurrent->get();
}

TokenReader (const std::string & protoFileName)
: mProtoStream(new ifstream(protoFileName))
{
    if (!*mProtoStream)
    {
        mProtoStream = nullptr;
    }
}

~TokenReader ()
{
}

TokenReader::iterator TokenReader::begin ()
{
    mProtoStream->clear();
    mProtoStream->seekg(0);

    return iterator(mProtoStream.get());
}

TokenReader::iterator TokenReader::end ()
{
    return iterator();
}

