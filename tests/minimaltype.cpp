#include "tests.h"

#define ___METAXXA_MINIMAL_TYPE_TEST___(Type) \
        static_assert(!(sizeof(Type) <= sizeof(Type *))|| is_same_v<MinimalType<Type>, Type>, "Invalid minimal type for "#Type); \
        static_assert(!(sizeof(Type) > sizeof(Type *)) || is_same_v<MinimalType<Type>, const Type &>, "Invalid minimal type for "#Type)

struct My
{
    int a[548];
};

TEST_CASE("[metaxxa::MinimalType]")
{
    ___METAXXA_MINIMAL_TYPE_TEST___(char);
    ___METAXXA_MINIMAL_TYPE_TEST___(short);
    ___METAXXA_MINIMAL_TYPE_TEST___(int);
    ___METAXXA_MINIMAL_TYPE_TEST___(long long);
    ___METAXXA_MINIMAL_TYPE_TEST___(long double);
}

#undef ___METAXXA_MINIMAL_TYPE_TEST___