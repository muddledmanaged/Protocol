//
//  InvalidProtoException.h
//  Protocol
//
//  Created by Wahid Tanner on 9/27/14.
//

#ifndef Platform_InvalidProtoException_h
#define Platform_InvalidProtoException_h

#include <stdexcept>
#include <string>

namespace MuddledManaged
{
    namespace Protocol
    {
        class InvalidProtoException : public std::logic_error
        {
        public:
            InvalidProtoException (int line, int column, const std::string & message = std::string(""))
            : std::logic_error(""), mLine(line), mColumn(column)
            {
                if (message.size() != 0)
                {
                    mMessage = message;
                }
                else
                {
                    mMessage = "Error in proto file.";
                }
                mMessage = " (Line: ";
                mMessage += std::to_string(line);
                mMessage += ", Column: ";
                mMessage += std::to_string(column);
                mMessage += " )";
            }

            virtual ~InvalidProtoException ()
            { }

            virtual const char * what () const noexcept
            {
                return mMessage.c_str();
            }

            int line () const
            {
                return mLine;
            }

            int column () const
            {
                return mColumn;
            }

        protected:
            InvalidProtoException ()
            : std::logic_error("")
            { }

            std::string mMessage;
            int mLine;
            int mColumn;
        };

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Platform_InvalidProtoException_h
