#include "tests.h"

#include <iostream>

class MyClass
{
public:
    void member_fn() {}

    struct Nested {};

    using NestedAlias = int;
};

TEST_CASE("Valid class members", "metaxxa::is_valid")
{
    static_assert(is_valid<MyClass>([](auto t) -> decltype(t.member_fn()) {}), "member_fn must be member of MyClass");
    static_assert(is_valid<MyClass>([](auto t) -> TypeSaver<typename decltype(t)::Nested> {}), "Nested must be nested type of MyClass");
    static_assert(is_valid<MyClass>([](auto t) -> TypeSaver<typename decltype(t)::NestedAlias> {}), "NestedAlias must be nested alias of MyClass");
}

TEST_CASE("Invalid class members", "metaxxa::is_valid")
{
    static_assert(!is_valid<MyClass>([](auto t) -> decltype(t.not_member_fn()) {}), "not_member_fn is not member of MyClass");
    static_assert(!is_valid<MyClass>([](auto t) -> TypeSaver<typename decltype(t)::NotNested> {}), "NotNested is not nested type of MyClass");
}