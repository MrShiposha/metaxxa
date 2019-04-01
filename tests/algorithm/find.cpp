#include "../tests.h"

template <typename T>
struct IsSizeOfEq2
{
    static constexpr bool VALUE = (sizeof(T) == 2);
};

TEST_CASE("[metaxxa::Find]")
{
    SECTION("Find in empty list")
    {
        using R = Find<List<>, IsSizeOfEq2>;

        static_assert(!R::FOUND, "List is empty, no type with size == 2");
        static_assert(is_same_v<R::TypeOr<int>, int>, "List is empty, OrType<int> == int expected");
    }

    SECTION("List with size == 1, false condition")
    {
        using R = Find<List<long long>, IsSizeOfEq2>;

        static_assert(!R::FOUND, "No type with size == 2 in List<long long>");
        static_assert(is_same_v<R::TypeOr<double>, double>, "OrType<double> == double expected");
    }

    SECTION("List with size == 1, true condition")
    {
        using R = Find<List<short>, IsSizeOfEq2>;

        static_assert(R::FOUND, "List<short> ==> sizeof(short) == 2 is true");
        static_assert(R::INDEX == 0, "List<short>::INDEX == 0 expected");
        static_assert(is_same_v<R::Type, short>, "Type == short expected");
        static_assert(is_same_v<R::TypeOr<double>, short>, "OrType<double> == short expected");
    }

    SECTION("List with size == 2, false condition")
    {
        using R = Find<List<long long, double>, IsSizeOfEq2>;

        static_assert(!R::FOUND, "No type with size == 2 in List<long long, double>");
        static_assert(is_same_v<R::TypeOr<float>, float>, "OrType<float> == float expected");
    }

    SECTION("List with size == 2, true condition")
    {
        {
            using R = Find<List<short, int>, IsSizeOfEq2>;

            static_assert(R::FOUND, "List<short, int> ==> sizeof(short) == 2 is true");
            static_assert(R::INDEX == 0, "List<short>::INDEX == 0 expected");
            static_assert(is_same_v<R::Type, short>, "Type == short expected");
            static_assert(is_same_v<R::TypeOr<double>, short>, "OrType<double> == short expected");
        }

        {
            using R = Find<List<int, short>, IsSizeOfEq2>;

            static_assert(R::FOUND, "List<int, short> ==> sizeof(short) == 2 is true");
            static_assert(R::INDEX == 1, "List<short>::INDEX == 1 expected");
            static_assert(is_same_v<R::Type, short>, "Type == short expected");
            static_assert(is_same_v<R::TypeOr<double>, short>, "OrType<double> == short expected");
        }
    }

    SECTION("List with size == 4, false condition")
    {
        using R = Find<List<long long, double, char, char>, IsSizeOfEq2>;

        static_assert(!R::FOUND, "No type with size == 2 in List<ong long, double, char, char>");
        static_assert(is_same_v<R::TypeOr<float>, float>, "OrType<float> == float expected");
    }

    SECTION("List with size == 4, true condition")
    {
        using R = Find<List<char, int, short, char>, IsSizeOfEq2>;

        static_assert(R::FOUND, "List<char, int, short, char> ==> sizeof(short) == 2 is true");
        static_assert(R::INDEX == 2, "List<char, int, short, char>::INDEX == 2 expected");
        static_assert(is_same_v<R::Type, short>, "Type == short expected");
        static_assert(is_same_v<R::TypeOr<double>, short>, "OrType<double> == short expected");   
    }
}