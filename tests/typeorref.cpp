#include "tests.h"

#define ___METAXXA_MINIMAL_TYPE_TEST___(Type) \
        static_assert(!(sizeof(Type) <= sizeof(Type *))|| is_same_v<TypeOrRef<Type>, Type>, "Invalid minimal type for "#Type); \
        static_assert(!(sizeof(Type) > sizeof(Type *)) || is_same_v<TypeOrRef<Type>, Type &>, "Invalid minimal type for "#Type)

struct Bytes256
{
    char bytes[256];
};

TEST_CASE("[metaxxa::TypeOrRef]")
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

#undef ___METAXXA_MINIMAL_TYPE_TEST___