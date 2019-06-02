#include "../tests.h"

template <typename T>
struct IsSizeOfEq2
{
    static constexpr bool value = (sizeof(T) == 2);
};

template <typename T, std::size_t INDEX>
struct IntegralWithEvenIndex
{
    static constexpr bool value = (std::is_integral_v<T> && INDEX % 2 == 0);
};

template <typename T, std::size_t INDEX, typename SrcTuple>
struct IntegralAndSize4
{
    static constexpr bool value = (std::is_integral_v<T> && std::tuple_size_v<SrcTuple> == 4);
};

TEST_CASE("[metaxxa::Find]")
{
    SECTION("Find in empty list")
    {
        using R = Find<TypeList<>, IsSizeOfEq2>;

        static_assert(!R::FOUND, "TypeList is empty, no type with size == 2");
        static_assert(is_same_v<R::TypeOr<int>, int>, "TypeList is empty, OrType<int> == int expected");
    }

    SECTION("TypeList with size == 1, false condition")
    {
        using R = Find<TypeList<long long>, IsSizeOfEq2>;

        static_assert(!R::FOUND, "No type with size == 2 in TypeList<long long>");
        static_assert(is_same_v<R::TypeOr<double>, double>, "OrType<double> == double expected");
    }

    SECTION("TypeList with size == 1, true condition")
    {
        using R = Find<TypeList<short>, IsSizeOfEq2>;

        static_assert(R::FOUND, "TypeList<short> ==> sizeof(short) == 2 is true");
        static_assert(R::INDEX == 0, "TypeList<short>::INDEX == 0 expected");
        static_assert(is_same_v<R::Type, short>, "Type == short expected");
        static_assert(is_same_v<R::TypeOr<double>, short>, "OrType<double> == short expected");
    }

    SECTION("TypeList with size == 2, false condition")
    {
        using R = Find<TypeList<long long, double>, IsSizeOfEq2>;

        static_assert(!R::FOUND, "No type with size == 2 in TypeList<long long, double>");
        static_assert(is_same_v<R::TypeOr<float>, float>, "OrType<float> == float expected");
    }

    SECTION("TypeList with size == 2, true condition")
    {
        {
            using R = Find<TypeList<short, int>, IsSizeOfEq2>;

            static_assert(R::FOUND, "TypeList<short, int> ==> sizeof(short) == 2 is true");
            static_assert(R::INDEX == 0, "TypeList<short>::INDEX == 0 expected");
            static_assert(is_same_v<R::Type, short>, "Type == short expected");
            static_assert(is_same_v<R::TypeOr<double>, short>, "OrType<double> == short expected");
        }

        {
            using R = Find<TypeList<int, short>, IsSizeOfEq2>;

            static_assert(R::FOUND, "TypeList<int, short> ==> sizeof(short) == 2 is true");
            static_assert(R::INDEX == 1, "TypeList<short>::INDEX == 1 expected");
            static_assert(is_same_v<R::Type, short>, "Type == short expected");
            static_assert(is_same_v<R::TypeOr<double>, short>, "OrType<double> == short expected");
        }
    }

    SECTION("TypeList with size == 4, false condition")
    {
        using R = Find<TypeList<long long, double, char, char>, IsSizeOfEq2>;

        static_assert(!R::FOUND, "No type with size == 2 in TypeList<ong long, double, char, char>");
        static_assert(is_same_v<R::TypeOr<float>, float>, "OrType<float> == float expected");
    }

    SECTION("TypeList with size == 4, true condition")
    {
        using R = Find<TypeList<char, int, short, char>, IsSizeOfEq2>;

        static_assert(R::FOUND, "TypeList<char, int, short, char> ==> sizeof(short) == 2 is true");
        static_assert(R::INDEX == 2, "TypeList<char, int, short, char>::INDEX == 2 expected");
        static_assert(is_same_v<R::Type, short>, "Type == short expected");
        static_assert(is_same_v<R::TypeOr<double>, short>, "OrType<double> == short expected");   
    }

    SECTION("IndexFilter, true condition")
    {
        using T = TypeList<float, int, double, long, short, float>;
        using R = IndexFind<T, IntegralWithEvenIndex>;

        static_assert(R::FOUND, "T ==> at<4> == short && 4%2 == 0 is true");
        static_assert(R::INDEX == 4, "T::INDEX == 4 expected");
        static_assert(is_same_v<R::Type, short>, "Type == short expected");
        static_assert(is_same_v<R::TypeOr<double>, short>, "OrType<double> == short expected");   
    }

    SECTION("IndexFilter, false condition")
    {
        using T = TypeList<float, int, double, long, float>;
        using R = IndexFind<T, IntegralWithEvenIndex>;

        static_assert(!R::FOUND, "No integral with even index");
        static_assert(is_same_v<R::TypeOr<double>, double>, "OrType<double> == double expected");   
    }

    SECTION("OverallFilter, true condition")
    {
        using T = TypeList<float, int, double, long>;
        using R = OverallFind<T, IntegralAndSize4>;

        static_assert(R::FOUND, "T ==> at<1> == short T::size == 4 is true");
        static_assert(R::INDEX == 1, "T::INDEX == 1 expected");
        static_assert(is_same_v<R::Type, int>, "Type == int expected");
        static_assert(is_same_v<R::TypeOr<double>, int>, "OrType<double> == int expected");
    }

    SECTION("OverallFilter, false condition")
    {
        using T = TypeList<float, int, double>;
        using R = OverallFind<T, IntegralAndSize4>;

        static_assert(!R::FOUND, "T::size != 4 ==> false");
        static_assert(is_same_v<R::TypeOr<double>, double>, "OrType<double> == double expected");
    }
}