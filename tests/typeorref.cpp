#include "tests.h"

#define ___METAXXA_MINIMAL_TYPE_TEST___(Type) \
        static_assert(!(sizeof(Type) <= sizeof(Type *))|| is_same_v<TypeOrRef<Type>, Type>, "Invalid minimal type for "#Type); \
        static_assert(!(sizeof(Type) > sizeof(Type *)) || is_same_v<TypeOrRef<Type>, Type &>, "Invalid minimal type for "#Type)

struct Bytes256
{
    char bytes[256];
};

TEST_CASE("actual type of TypeOrRef", "[metaxxa::TypeOrRef]")
{
    ___METAXXA_MINIMAL_TYPE_TEST___(char);
    ___METAXXA_MINIMAL_TYPE_TEST___(short);
    ___METAXXA_MINIMAL_TYPE_TEST___(int);
    ___METAXXA_MINIMAL_TYPE_TEST___(long long);
    ___METAXXA_MINIMAL_TYPE_TEST___(double);
    ___METAXXA_MINIMAL_TYPE_TEST___(Bytes256);

    ___METAXXA_MINIMAL_TYPE_TEST___(const char);
    ___METAXXA_MINIMAL_TYPE_TEST___(const short);
    ___METAXXA_MINIMAL_TYPE_TEST___(const int);
    ___METAXXA_MINIMAL_TYPE_TEST___(const long long);
    ___METAXXA_MINIMAL_TYPE_TEST___(const double);
    ___METAXXA_MINIMAL_TYPE_TEST___(const Bytes256);
}

TEST_CASE("wrappers of TypeOfRef", "[metaxxa::TypeOrRef]")
{
    SECTION("ref")
    {
        {
            char a = 'a';
            auto obj = obj_or_ref(a);

            static_assert(is_same_v<decltype(obj), decltype(a)>, "Expected object type");
            REQUIRE(a == obj);
        }

        {
            Bytes256 obj;
            auto ref = obj_or_ref(obj);

            static_assert(is_same_v<decltype(ref), std::reference_wrapper<Bytes256>>, "Expected ref type");
            REQUIRE(&ref.get() == &obj);
        }
    }

    SECTION("cref")
    {
        {
            const char a = 'a';
            auto obj = obj_or_cref(a);

            static_assert(is_same_v<decltype(obj), char>, "Expected object type");
            REQUIRE(a == obj);
        }

        {
            const Bytes256 obj {};
            auto ref = obj_or_cref(obj);

            static_assert(is_same_v<decltype(ref), std::reference_wrapper<const Bytes256>>, "Expected ref type");
            REQUIRE(&ref.get() == &obj);
        }
    }
}

#undef ___METAXXA_MINIMAL_TYPE_TEST___