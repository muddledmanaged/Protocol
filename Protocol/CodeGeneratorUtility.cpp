//
//  CodeGeneratorUtility.cpp
//  Protocol
//
//  Created by Wahid Tanner on 11/15/14.
//

#include "CodeGeneratorUtility.h"

using namespace MuddledManaged;

int Protocol::CodeGeneratorUtility::sizeIndex (unsigned long long index)
{
    return sizeVarInt(index << 3);
}

int Protocol::CodeGeneratorUtility::sizeVarInt (unsigned long long value)
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
