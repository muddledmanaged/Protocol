//
//  CodeGeneratorUtilityCPP.h
//  Protocol
//
//  Created by Wahid Tanner on 11/18/14.
//

#ifndef Protocol_CodeGeneratorUtilityCPP_h
#define Protocol_CodeGeneratorUtilityCPP_h

namespace MuddledManaged
{
    namespace Protocol
    {
        int sizeVarInt (unsigned long long value)
        {
            if (value < (1ull << 7))
            {
                return 1;
            }
            else if (value < (1ull << 14))
            {
                return 2;
            }
            else if (value < (1ull << 21))
            {
                return 3;
            }
            else if (value < (1ull << 28))
            {
                return 4;
            }
            else if (value < (1ull << 35))
            {
                return 5;
            }
            else if (value < (1ull << 42))
            {
                return 6;
            }
            else if (value < (1ull << 49))
            {
                return 7;
            }
            else if (value < (1ull << 56))
            {
                return 8;
            }
            else if (value < (1ull << 63))
            {
                return 9;
            }
            return 10;
        }

        int sizeIndex (unsigned long long index)
        {
            return sizeVarInt(index << 3);
        }

    } // namespace Protocol

} // namespace MuddledManaged

#endif // Protocol_CodeGeneratorUtilityCPP_h
