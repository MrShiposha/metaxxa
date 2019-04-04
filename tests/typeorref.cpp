#include "tests.h"

#define ___METAXXA_MINIMAL_TYPE_TEST___(Type) \
        static_assert(!(sizeof(Type) <= sizeof(Type *))|| is_same_v<TypeOrRef<Type>, Type>, "Invalid minimal type for "#Type); \
        static_assert(!(sizeof(Type) > sizeof(Type *)) || is_same_v<TypeOrRef<Type>, const Type &>, "Invalid minimal type for "#Type)

TEST_CASE("[metaxxa::TypeOrRef]")
{
    ___METAXXA_MINIMAL_TYPE_TEST___(char);
    ___METAXXA_MINIMAL_TYPE_TEST___(short);
    ___METAXXA_MINIMAL_TYPE_TEST___(int);
    ___METAXXA_MINIMAL_TYPE_TEST___(long long);
    ___METAXXA_MINIMAL_TYPE_TEST___(double);
}

#undef ___METAXXA_MINIMAL_TYPE_TEST___