#include "tests.h"

TEST_CASE("[metaxxa::type_if]")
{
    {
        using R = TypeIf<sizeof(uint16_t) != 2>
                    ::Then<char>
                    ::Else<void>
                    ::Type;

        static_assert(is_same_v<R, void>, "Invalid type result of (sizeof(int16_t) != 2)? char : void");
    }

    {
        using R = TypeIf<sizeof(uint16_t) == 2>
                    ::Then<char>
                    ::Else<void>
                    ::Type;

        static_assert(is_same_v<R, char>, "Invalid type result of (sizeof(int16_t) == 2)? char : void");
    }

    {
        using R = TypeIf<sizeof(uint16_t) == 2>
                    ::Then<char>
                    ::Type;

        static_assert(is_same_v<R, char>, "Invalid type result of (sizeof(int16_t) == 2)? char : <no type>");
    }
}