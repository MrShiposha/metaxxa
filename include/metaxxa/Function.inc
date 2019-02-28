#ifndef METAXXA_FUNCTION_INC
#define METAXXA_FUNCTION_INC

#include "Function.h"
#include "detail/ArgumentsSignatureBuilder.inc"

#define DEFINE_FUNCTION_IMPL_WITH_ARGUMENTS(Signature) \
    template<typename ResultType, typename... FunctionArguments>                                   \
    constexpr size_t Function<Signature>::argument_count()  { return Arguments::size(); }          \
                                                                                                   \
    template<typename ResultType, typename... FunctionArguments>                                   \
    constexpr bool Function<Signature>::is_method() { return false; }                              \
                                                                                                   \
    template<typename ResultType, typename... FunctionArguments>                                   \
    std::string Function<Signature>::get_signature()                                               \
    {                                                                                              \
        std::string arguments;                                                                     \
        Arguments::template for_each_types<metaxxa::detail::ArgumentsSignatureBuilder>(arguments); \
        return Type<Result>::name_with_modifiers() + " (" + arguments + ")";                       \
    }                                                                                              \
                                                                                                   \
    template<typename ResultType, typename... FunctionArguments>                                   \
    std::string Function<Signature>::signature() { return get_signature(); }

#define DEFINE_FUNCTION_IMPL_NO_ARGUMENTS(Signature) \
    template<typename ResultType>                                                         \
    constexpr size_t Function<Signature>::argument_count() { return 0; }                  \
                                                                                          \
    template<typename ResultType>                                                         \
    constexpr bool Function<Signature>::is_method() { return false; }                     \
                                                                                          \
    template<typename ResultType>                                                         \
    std::string Function<Signature>::get_signature()                                      \
    {                                                                                     \
        return Type<Result>::name_with_modifiers() + " ()";                               \
    }                                                                                     \
                                                                                          \
    template<typename ResultType>                                                         \
    std::string Function<Signature>::signature() { return get_signature(); }

#define IS_CONST(a) a
#define IS_VOLATILE(a) a
#define IS_LVALUE(a) a
#define IS_RVALUE(a) a
#define IS_NOEXCEPT(a) a

#define DEFINE_METHOD_IMPL_WITH_ARGUMENTS(Signature, _IS_CONST, _IS_VOLATILE, _IS_LVALUE, _IS_RVALUE, _IS_NOEXCEPT) \
    template<typename SomeType, typename ResultType, typename... FunctionArguments>                                   \
    constexpr size_t Function<Signature>::argument_count() { return Arguments::size(); }                              \
                                                                                                                      \
    template<typename SomeType, typename ResultType, typename... FunctionArguments>                                   \
    constexpr bool Function<Signature>::is_method() { return true; }                                                  \
                                                                                                                      \
    template<typename SomeType, typename ResultType, typename... FunctionArguments>                                   \
    constexpr bool Function<Signature>::is_const() { return _IS_CONST; }                                              \
                                                                                                                      \
    template<typename SomeType, typename ResultType, typename... FunctionArguments>                                   \
    constexpr bool Function<Signature>::is_volatile() { return _IS_VOLATILE; }                                        \
                                                                                                                      \
    template<typename SomeType, typename ResultType, typename... FunctionArguments>                                   \
    constexpr bool Function<Signature>::is_lvalue() { return _IS_LVALUE; }                                            \
                                                                                                                      \
    template<typename SomeType, typename ResultType, typename... FunctionArguments>                                   \
    constexpr bool Function<Signature>::is_rvalue() { return _IS_RVALUE; }                                            \
                                                                                                                      \
    template<typename SomeType, typename ResultType, typename... FunctionArguments>                                   \
    constexpr bool Function<Signature>::is_noexcept() { return _IS_NOEXCEPT; }                                        \
                                                                                                                      \
    template<typename SomeType, typename ResultType, typename... FunctionArguments>                                   \
    std::string Function<Signature>::get_signature()                                                                  \
    {                                                                                                                 \
        std::string arguments;                                                                                        \
        Arguments::template for_each_types<metaxxa::detail::ArgumentsSignatureBuilder>(arguments);                    \
        std::string signature = Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)";         \
                                                                                                                      \
        signature += " (" + arguments + ")";                                                                          \
        if constexpr(is_const()) signature += " const";                                                               \
        if constexpr(is_volatile()) signature += " volatile";                                                         \
        if constexpr(is_lvalue() && !is_rvalue()) signature += " &";                                                  \
        if constexpr(!is_lvalue() && is_rvalue()) signature += " &&";                                                 \
        if constexpr(is_noexcept()) signature += " noexcept";                                                         \
        return signature;                                                                                             \
    }                                                                                                                 \
                                                                                                                      \
    template<typename SomeType, typename ResultType, typename... FunctionArguments>                                   \
    std::string Function<Signature>::signature() { return get_signature(); }                                          \

#define DEFINE_METHOD_IMPL_NO_ARGUMENTS(Signature, _IS_CONST, _IS_VOLATILE, _IS_LVALUE, _IS_RVALUE, _IS_NOEXCEPT) \
    template<typename SomeType, typename ResultType>                                                                  \
    constexpr size_t Function<Signature>::argument_count() { return 0; }                                              \
                                                                                                                      \
    template<typename SomeType, typename ResultType>                                                                  \
    constexpr bool Function<Signature>::is_method() { return true; }                                                  \
                                                                                                                      \
    template<typename SomeType, typename ResultType>                                                                  \
    constexpr bool Function<Signature>::is_const() { return _IS_CONST; }                                              \
                                                                                                                      \
    template<typename SomeType, typename ResultType>                                                                  \
    constexpr bool Function<Signature>::is_volatile() { return _IS_VOLATILE; }                                        \
                                                                                                                      \
    template<typename SomeType, typename ResultType>                                                                  \
    constexpr bool Function<Signature>::is_lvalue() { return _IS_LVALUE; }                                            \
                                                                                                                      \
    template<typename SomeType, typename ResultType>                                                                  \
    constexpr bool Function<Signature>::is_rvalue() { return _IS_RVALUE; }                                            \
                                                                                                                      \
    template<typename SomeType, typename ResultType>                                                                  \
    constexpr bool Function<Signature>::is_noexcept() { return _IS_NOEXCEPT; }                                        \
                                                                                                                      \
    template<typename SomeType, typename ResultType>                                                                  \
    std::string Function<Signature>::get_signature()                                                                  \
    {                                                                                                                 \
        std::string signature = Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*) ()";      \
                                                                                                                      \
        if constexpr(is_const()) signature += " const";                                                               \
        if constexpr(is_volatile()) signature += " volatile";                                                         \
        if constexpr(is_lvalue() && !is_rvalue()) signature += " &";                                                  \
        if constexpr(!is_lvalue() && is_rvalue()) signature += " &&";                                                 \
        if constexpr(is_noexcept()) signature += " noexcept";                                                         \
        return signature;                                                                                             \
    }                                                                                                                 \
                                                                                                                      \
    template<typename SomeType, typename ResultType>                                                                  \
    std::string Function<Signature>::signature() { return get_signature(); }  

DEFINE_FUNCTION_IMPL_WITH_ARGUMENTS(ResultType(FunctionArguments...))
DEFINE_FUNCTION_IMPL_WITH_ARGUMENTS(ResultType(*)(FunctionArguments...))
DEFINE_FUNCTION_IMPL_WITH_ARGUMENTS(std::function<ResultType(FunctionArguments...)>)

DEFINE_FUNCTION_IMPL_NO_ARGUMENTS(ResultType())
DEFINE_FUNCTION_IMPL_NO_ARGUMENTS(ResultType(*)())
DEFINE_FUNCTION_IMPL_NO_ARGUMENTS(std::function<ResultType()>)


#include "detail/Methods.inc"

template <typename FirstCallable, typename SecondCallable>
constexpr bool is_same_signature()
{
    return Type<typename Function<FirstCallable>::Arguments>() == Type<typename Function<SecondCallable>::Arguments>()
        && Type<typename Function<FirstCallable>::Result>() == Type<typename Function<SecondCallable>::Result>();
}

template <typename FirstCallable, typename SecondCallable>
constexpr bool is_same_modifiers()
{
    using F1 = Function<FirstCallable>;
    using F2 = Function<SecondCallable>;

    if constexpr(F1::is_method() && F2::is_method())
        return 
            (F1::is_const() == F2::is_const())
            && (F1::is_volatile() == F2::is_volatile())
            && (F1::is_lvalue() == F2::is_lvalue())
            && (F1::is_rvalue() == F2::is_rvalue())
            && (F1::is_noexcept() == F2::is_noexcept());
    else 
        return true;
}

template <typename FirstCallable, typename SecondCallable>
constexpr bool is_same_signature(Function<FirstCallable>, Function<SecondCallable>)
{
    return is_same_signature<FirstCallable, SecondCallable>();
}

template <typename FirstCallable, typename SecondCallable>
constexpr bool is_same_modifiers(Function<FirstCallable>, Function<SecondCallable>)
{
    return is_same_modifiers<FirstCallable, SecondCallable>();
}

template <typename FirstCallable, typename SecondCallable>
constexpr auto operator==(Function<FirstCallable>, Function<SecondCallable>)
{
return is_same_signature<FirstCallable, SecondCallable>() && is_same_modifiers<FirstCallable, SecondCallable>();
}

template <typename FirstCallable, typename SecondCallable>
constexpr auto operator!=(Function<FirstCallable> first, Function<SecondCallable> second)
{
return !(first == second);
}

#undef DEFINE_FUNCTION_IMPL_WITH_ARGUMENTS
#undef DEFINE_FUNCTION_IMPL_NO_ARGUMENTS
#undef DEFINE_METHOD_IMPL_WITH_ARGUMENTS
#undef DEFINE_METHOD_IMPL_NO_ARGUMENTS

#undef IS_CONST
#undef IS_VOLATILE
#undef IS_LVALUE
#undef IS_RVALUE
#undef IS_NOEXCEPT

#endif // METAXXA_FUNCTION_INC