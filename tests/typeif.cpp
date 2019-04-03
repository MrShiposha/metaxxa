#include "tests.h"

TEST_CASE("[metaxxa::TypeIf]")
{
    {
        using R = TypeIf<false_type>
                    ::Then<char>
                    ::Else<void>
                    ::Type;

        static_assert(is_same_v<R, void>, "Invalid type result of TypeIf<false_type>? char : void");
    }

    {
        using R = TypeIf<int> // int != std::false_type ==> true
                    ::Then<char>
                    ::Else<void>
                    ::Type;

        static_assert(is_same_v<R, char>, "Invalid type result of TypeIf<int>? char : void");
    }

    {
        using R = TypeIf<true_type>
                    ::Then<char>
                    ::Type;

        static_assert(is_same_v<R, char>, "Invalid type result of TypeIf<true_type>? char : <no type>");
    }
}