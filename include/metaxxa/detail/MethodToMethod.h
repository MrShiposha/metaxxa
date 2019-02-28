#ifndef METAXXA_detail_METHODTOMETHOD_H
#define METAXXA_detail_METHODTOMETHOD_H

namespace metaxxa::detail
{
    template 
    <
        typename SomeType, 
        typename Callable,
        bool IS_CONST,
        bool IS_VOLATILE,
        bool IS_LVALUE,
        bool IS_RVALUE,
        bool IS_NOEXCEPT, 
        typename... Arguments
    >
    struct MethodToMethod
    {};

    template 
    <
        typename SomeType, 
        typename Callable, 
        typename... Arguments
    >
    struct MethodToMethod<SomeType, Callable, false, false, true, true, false, Arguments...>
    {
        using MethodResult = typename Function<Callable>::Result;

        using Method = MethodResult(SomeType::*)(Arguments...);
    };

    template 
    <
        typename SomeType, 
        typename Callable, 
        typename... Arguments
    >
    struct MethodToMethod<SomeType, Callable, false, false, true, true, true, Arguments...>
    {
        using MethodResult = typename Function<Callable>::Result;

        using Method = MethodResult(SomeType::*)(Arguments...) noexcept;
    };

    template 
    <
        typename SomeType, 
        typename Callable, 
        typename... Arguments
    >
    struct MethodToMethod<SomeType, Callable, false, false, true, false, false, Arguments...>
    {
        using MethodResult = typename Function<Callable>::Result;

        using Method = MethodResult(SomeType::*)(Arguments...) &;
    };

    template 
    <
        typename SomeType, 
        typename Callable, 
        typename... Arguments
    >
    struct MethodToMethod<SomeType, Callable, false, false, true, false, true, Arguments...>
    {
        using MethodResult = typename Function<Callable>::Result;

        using Method = MethodResult(SomeType::*)(Arguments...) & noexcept;
    };

    template 
    <
        typename SomeType, 
        typename Callable, 
        typename... Arguments
    >
    struct MethodToMethod<SomeType, Callable, false, false, false, true, false, Arguments...>
    {
        using MethodResult = typename Function<Callable>::Result;

        using Method = MethodResult(SomeType::*)(Arguments...) &&;
    };

    template 
    <
        typename SomeType, 
        typename Callable, 
        typename... Arguments
    >
    struct MethodToMethod<SomeType, Callable, false, false, false, true, true, Arguments...>
    {
        using MethodResult = typename Function<Callable>::Result;

        using Method = MethodResult(SomeType::*)(Arguments...) && noexcept;
    };

    template 
    <
        typename SomeType, 
        typename Callable, 
        typename... Arguments
    >
    struct MethodToMethod<SomeType, Callable, true, false, true, true, false, Arguments...>
    {
        using MethodResult = typename Function<Callable>::Result;

        using Method = MethodResult(SomeType::*)(Arguments...) const;
    };

    template 
    <
        typename SomeType, 
        typename Callable, 
        typename... Arguments
    >
    struct MethodToMethod<SomeType, Callable, true, false, true, true, true, Arguments...>
    {
        using MethodResult = typename Function<Callable>::Result;

        using Method = MethodResult(SomeType::*)(Arguments...) const noexcept;
    };

    template 
    <
        typename SomeType, 
        typename Callable, 
        typename... Arguments
    >
    struct MethodToMethod<SomeType, Callable, true, false, true, false, false, Arguments...>
    {
        using MethodResult = typename Function<Callable>::Result;

        using Method = MethodResult(SomeType::*)(Arguments...) const &;
    };

    template 
    <
        typename SomeType, 
        typename Callable, 
        typename... Arguments
    >
    struct MethodToMethod<SomeType, Callable, true, false, true, false, true, Arguments...>
    {
        using MethodResult = typename Function<Callable>::Result;

        using Method = MethodResult(SomeType::*)(Arguments...) const & noexcept;
    };

    template 
    <
        typename SomeType, 
        typename Callable, 
        typename... Arguments
    >
    struct MethodToMethod<SomeType, Callable, true, false, false, true, false, Arguments...>
    {
        using MethodResult = typename Function<Callable>::Result;

        using Method = MethodResult(SomeType::*)(Arguments...) const &&;
    };

    template 
    <
        typename SomeType, 
        typename Callable, 
        typename... Arguments
    >
    struct MethodToMethod<SomeType, Callable, true, false, false, true, true, Arguments...>
    {
        using MethodResult = typename Function<Callable>::Result;

        using Method = MethodResult(SomeType::*)(Arguments...) const && noexcept;
    };

    template 
    <
        typename SomeType, 
        typename Callable, 
        typename... Arguments
    >
    struct MethodToMethod<SomeType, Callable, false, true, true, true, false, Arguments...>
    {
        using MethodResult = typename Function<Callable>::Result;

        using Method = MethodResult(SomeType::*)(Arguments...) volatile;
    };

    template 
    <
        typename SomeType, 
        typename Callable, 
        typename... Arguments
    >
    struct MethodToMethod<SomeType, Callable, false, true, true, true, true, Arguments...>
    {
        using MethodResult = typename Function<Callable>::Result;

        using Method = MethodResult(SomeType::*)(Arguments...) volatile noexcept;
    };

    template 
    <
        typename SomeType, 
        typename Callable, 
        typename... Arguments
    >
    struct MethodToMethod<SomeType, Callable, false, true, true, false, false, Arguments...>
    {
        using MethodResult = typename Function<Callable>::Result;

        using Method = MethodResult(SomeType::*)(Arguments...) volatile &;
    };

    template 
    <
        typename SomeType, 
        typename Callable, 
        typename... Arguments
    >
    struct MethodToMethod<SomeType, Callable, false, true, true, false, true, Arguments...>
    {
        using MethodResult = typename Function<Callable>::Result;

        using Method = MethodResult(SomeType::*)(Arguments...) volatile & noexcept;
    };

    template 
    <
        typename SomeType, 
        typename Callable, 
        typename... Arguments
    >
    struct MethodToMethod<SomeType, Callable, false, true, false, true, false, Arguments...>
    {
        using MethodResult = typename Function<Callable>::Result;

        using Method = MethodResult(SomeType::*)(Arguments...) volatile &&;
    };

    template 
    <
        typename SomeType, 
        typename Callable, 
        typename... Arguments
    >
    struct MethodToMethod<SomeType, Callable, false, true, false, true, true, Arguments...>
    {
        using MethodResult = typename Function<Callable>::Result;

        using Method = MethodResult(SomeType::*)(Arguments...) volatile && noexcept;
    };

    template 
    <
        typename SomeType, 
        typename Callable, 
        typename... Arguments
    >
    struct MethodToMethod<SomeType, Callable, true, true, true, true, false, Arguments...>
    {
        using MethodResult = typename Function<Callable>::Result;

        using Method = MethodResult(SomeType::*)(Arguments...) const volatile;
    };

    template 
    <
        typename SomeType, 
        typename Callable, 
        typename... Arguments
    >
    struct MethodToMethod<SomeType, Callable, true, true, true, true, true, Arguments...>
    {
        using MethodResult = typename Function<Callable>::Result;

        using Method = MethodResult(SomeType::*)(Arguments...) const volatile noexcept;
    };

    template 
    <
        typename SomeType, 
        typename Callable, 
        typename... Arguments
    >
    struct MethodToMethod<SomeType, Callable, true, true, true, false, false, Arguments...>
    {
        using MethodResult = typename Function<Callable>::Result;

        using Method = MethodResult(SomeType::*)(Arguments...) const volatile &;
    };

    template 
    <
        typename SomeType, 
        typename Callable, 
        typename... Arguments
    >
    struct MethodToMethod<SomeType, Callable, true, true, true, false, true, Arguments...>
    {
        using MethodResult = typename Function<Callable>::Result;

        using Method = MethodResult(SomeType::*)(Arguments...) const volatile & noexcept;
    };

    template 
    <
        typename SomeType, 
        typename Callable, 
        typename... Arguments
    >
    struct MethodToMethod<SomeType, Callable, true, true, false, true, false, Arguments...>
    {
        using MethodResult = typename Function<Callable>::Result;

        using Method = MethodResult(SomeType::*)(Arguments...) const volatile &&;
    };

    template 
    <
        typename SomeType, 
        typename Callable, 
        typename... Arguments
    >
    struct MethodToMethod<SomeType, Callable, true, true, false, true, true, Arguments...>
    {
        using MethodResult = typename Function<Callable>::Result;

        using Method = MethodResult(SomeType::*)(Arguments...) const volatile && noexcept;
    };
}

#endif // METAXXA_detail_METHODTOMETHOD_H