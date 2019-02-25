#ifndef METAXXA_detail_METHODS_INC
#define METAXXA_detail_METHODS_INC

DEFINE_METHOD_IMPL_WITH_ARGUMENTS
(
    ResultType(SomeType::*)(FunctionArguments...), 
    IS_CONST(false), 
    IS_VOLATILE(false), 
    IS_LVALUE(true), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(false)
)

DEFINE_METHOD_IMPL_WITH_ARGUMENTS
(
    ResultType(SomeType::*)(FunctionArguments...) noexcept, 
    IS_CONST(false), 
    IS_VOLATILE(false), 
    IS_LVALUE(true), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(true)
)

DEFINE_METHOD_IMPL_WITH_ARGUMENTS
(
    ResultType(SomeType::*)(FunctionArguments...) &, 
    IS_CONST(false), 
    IS_VOLATILE(false), 
    IS_LVALUE(true), 
    IS_RVALUE(false), 
    IS_NOEXCEPT(false)
)

DEFINE_METHOD_IMPL_WITH_ARGUMENTS
(
    ResultType(SomeType::*)(FunctionArguments...) & noexcept, 
    IS_CONST(false), 
    IS_VOLATILE(false), 
    IS_LVALUE(true), 
    IS_RVALUE(false), 
    IS_NOEXCEPT(true)
)

DEFINE_METHOD_IMPL_WITH_ARGUMENTS
(
    ResultType(SomeType::*)(FunctionArguments...) &&, 
    IS_CONST(false), 
    IS_VOLATILE(false), 
    IS_LVALUE(false), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(false)
)

DEFINE_METHOD_IMPL_WITH_ARGUMENTS
(
    ResultType(SomeType::*)(FunctionArguments...) && noexcept, 
    IS_CONST(false), 
    IS_VOLATILE(false), 
    IS_LVALUE(false), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(true)
)

DEFINE_METHOD_IMPL_WITH_ARGUMENTS
(
    ResultType(SomeType::*)(FunctionArguments...) const, 
    IS_CONST(true), 
    IS_VOLATILE(false), 
    IS_LVALUE(true), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(false)
)

DEFINE_METHOD_IMPL_WITH_ARGUMENTS
(
    ResultType(SomeType::*)(FunctionArguments...) const noexcept, 
    IS_CONST(true), 
    IS_VOLATILE(false), 
    IS_LVALUE(true), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(true)
)

DEFINE_METHOD_IMPL_WITH_ARGUMENTS
(
    ResultType(SomeType::*)(FunctionArguments...) const &, 
    IS_CONST(true), 
    IS_VOLATILE(false), 
    IS_LVALUE(true), 
    IS_RVALUE(false), 
    IS_NOEXCEPT(false)
)

DEFINE_METHOD_IMPL_WITH_ARGUMENTS
(
    ResultType(SomeType::*)(FunctionArguments...) const & noexcept, 
    IS_CONST(true), 
    IS_VOLATILE(false), 
    IS_LVALUE(true), 
    IS_RVALUE(false), 
    IS_NOEXCEPT(true)
)

DEFINE_METHOD_IMPL_WITH_ARGUMENTS
(
    ResultType(SomeType::*)(FunctionArguments...) const &&, 
    IS_CONST(true), 
    IS_VOLATILE(false), 
    IS_LVALUE(false), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(false)
)

DEFINE_METHOD_IMPL_WITH_ARGUMENTS
(
    ResultType(SomeType::*)(FunctionArguments...) const && noexcept, 
    IS_CONST(true), 
    IS_VOLATILE(false), 
    IS_LVALUE(false), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(true)
)

DEFINE_METHOD_IMPL_WITH_ARGUMENTS
(
    ResultType(SomeType::*)(FunctionArguments...) volatile, 
    IS_CONST(false), 
    IS_VOLATILE(true), 
    IS_LVALUE(true), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(false)
)

DEFINE_METHOD_IMPL_WITH_ARGUMENTS
(
    ResultType(SomeType::*)(FunctionArguments...) volatile noexcept, 
    IS_CONST(false), 
    IS_VOLATILE(true), 
    IS_LVALUE(true), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(true)
)

DEFINE_METHOD_IMPL_WITH_ARGUMENTS
(
    ResultType(SomeType::*)(FunctionArguments...) volatile &, 
    IS_CONST(false), 
    IS_VOLATILE(true), 
    IS_LVALUE(true), 
    IS_RVALUE(false), 
    IS_NOEXCEPT(false)
)

DEFINE_METHOD_IMPL_WITH_ARGUMENTS
(
    ResultType(SomeType::*)(FunctionArguments...) volatile & noexcept, 
    IS_CONST(false), 
    IS_VOLATILE(true), 
    IS_LVALUE(true), 
    IS_RVALUE(false), 
    IS_NOEXCEPT(true)
)

DEFINE_METHOD_IMPL_WITH_ARGUMENTS
(
    ResultType(SomeType::*)(FunctionArguments...) volatile &&, 
    IS_CONST(false), 
    IS_VOLATILE(true), 
    IS_LVALUE(false), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(false)
)

DEFINE_METHOD_IMPL_WITH_ARGUMENTS
(
    ResultType(SomeType::*)(FunctionArguments...) volatile && noexcept, 
    IS_CONST(false), 
    IS_VOLATILE(true), 
    IS_LVALUE(false), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(true)
)

DEFINE_METHOD_IMPL_WITH_ARGUMENTS
(
    ResultType(SomeType::*)(FunctionArguments...) const volatile, 
    IS_CONST(true), 
    IS_VOLATILE(true), 
    IS_LVALUE(true), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(false)
)

DEFINE_METHOD_IMPL_WITH_ARGUMENTS
(
    ResultType(SomeType::*)(FunctionArguments...) const volatile noexcept, 
    IS_CONST(true), 
    IS_VOLATILE(true), 
    IS_LVALUE(true), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(true)
)

DEFINE_METHOD_IMPL_WITH_ARGUMENTS
(
    ResultType(SomeType::*)(FunctionArguments...) const volatile &, 
    IS_CONST(true), 
    IS_VOLATILE(true), 
    IS_LVALUE(true), 
    IS_RVALUE(false), 
    IS_NOEXCEPT(false)
)

DEFINE_METHOD_IMPL_WITH_ARGUMENTS
(
    ResultType(SomeType::*)(FunctionArguments...) const volatile & noexcept, 
    IS_CONST(true), 
    IS_VOLATILE(true), 
    IS_LVALUE(true), 
    IS_RVALUE(false), 
    IS_NOEXCEPT(true)
)

DEFINE_METHOD_IMPL_WITH_ARGUMENTS
(
    ResultType(SomeType::*)(FunctionArguments...) const volatile &&, 
    IS_CONST(true), 
    IS_VOLATILE(true), 
    IS_LVALUE(false), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(false)
)

DEFINE_METHOD_IMPL_WITH_ARGUMENTS
(
    ResultType(SomeType::*)(FunctionArguments...) const volatile && noexcept, 
    IS_CONST(true), 
    IS_VOLATILE(true), 
    IS_LVALUE(false), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(true)
)

DEFINE_METHOD_IMPL_NO_ARGUMENTS
(
    ResultType(SomeType::*)(), 
    IS_CONST(false), 
    IS_VOLATILE(false), 
    IS_LVALUE(true), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(false)
)

DEFINE_METHOD_IMPL_NO_ARGUMENTS
(
    ResultType(SomeType::*)() noexcept, 
    IS_CONST(false), 
    IS_VOLATILE(false), 
    IS_LVALUE(true), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(true)
)

DEFINE_METHOD_IMPL_NO_ARGUMENTS
(
    ResultType(SomeType::*)() &, 
    IS_CONST(false), 
    IS_VOLATILE(false), 
    IS_LVALUE(true), 
    IS_RVALUE(false), 
    IS_NOEXCEPT(false)
)

DEFINE_METHOD_IMPL_NO_ARGUMENTS
(
    ResultType(SomeType::*)() & noexcept, 
    IS_CONST(false), 
    IS_VOLATILE(false), 
    IS_LVALUE(true), 
    IS_RVALUE(false), 
    IS_NOEXCEPT(true)
)

DEFINE_METHOD_IMPL_NO_ARGUMENTS
(
    ResultType(SomeType::*)() &&, 
    IS_CONST(false), 
    IS_VOLATILE(false), 
    IS_LVALUE(false), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(false)
)

DEFINE_METHOD_IMPL_NO_ARGUMENTS
(
    ResultType(SomeType::*)() && noexcept, 
    IS_CONST(false), 
    IS_VOLATILE(false), 
    IS_LVALUE(false), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(true)
)

DEFINE_METHOD_IMPL_NO_ARGUMENTS
(
    ResultType(SomeType::*)() const, 
    IS_CONST(true), 
    IS_VOLATILE(false), 
    IS_LVALUE(true), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(false)
)

DEFINE_METHOD_IMPL_NO_ARGUMENTS
(
    ResultType(SomeType::*)() const noexcept, 
    IS_CONST(true), 
    IS_VOLATILE(false), 
    IS_LVALUE(true), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(true)
)

DEFINE_METHOD_IMPL_NO_ARGUMENTS
(
    ResultType(SomeType::*)() const &, 
    IS_CONST(true), 
    IS_VOLATILE(false), 
    IS_LVALUE(true), 
    IS_RVALUE(false), 
    IS_NOEXCEPT(false)
)

DEFINE_METHOD_IMPL_NO_ARGUMENTS
(
    ResultType(SomeType::*)() const & noexcept, 
    IS_CONST(true), 
    IS_VOLATILE(false), 
    IS_LVALUE(true), 
    IS_RVALUE(false), 
    IS_NOEXCEPT(true)
)

DEFINE_METHOD_IMPL_NO_ARGUMENTS
(
    ResultType(SomeType::*)() const &&, 
    IS_CONST(true), 
    IS_VOLATILE(false), 
    IS_LVALUE(false), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(false)
)

DEFINE_METHOD_IMPL_NO_ARGUMENTS
(
    ResultType(SomeType::*)() const && noexcept, 
    IS_CONST(true), 
    IS_VOLATILE(false), 
    IS_LVALUE(false), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(true)
)

DEFINE_METHOD_IMPL_NO_ARGUMENTS
(
    ResultType(SomeType::*)() volatile, 
    IS_CONST(false), 
    IS_VOLATILE(true), 
    IS_LVALUE(true), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(false)
)

DEFINE_METHOD_IMPL_NO_ARGUMENTS
(
    ResultType(SomeType::*)() volatile noexcept, 
    IS_CONST(false), 
    IS_VOLATILE(true), 
    IS_LVALUE(true), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(true)
)

DEFINE_METHOD_IMPL_NO_ARGUMENTS
(
    ResultType(SomeType::*)() volatile &, 
    IS_CONST(false), 
    IS_VOLATILE(true), 
    IS_LVALUE(true), 
    IS_RVALUE(false), 
    IS_NOEXCEPT(false)
)

DEFINE_METHOD_IMPL_NO_ARGUMENTS
(
    ResultType(SomeType::*)() volatile & noexcept, 
    IS_CONST(false), 
    IS_VOLATILE(true), 
    IS_LVALUE(true), 
    IS_RVALUE(false), 
    IS_NOEXCEPT(true)
)

DEFINE_METHOD_IMPL_NO_ARGUMENTS
(
    ResultType(SomeType::*)() volatile &&, 
    IS_CONST(false), 
    IS_VOLATILE(true), 
    IS_LVALUE(false), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(false)
)

DEFINE_METHOD_IMPL_NO_ARGUMENTS
(
    ResultType(SomeType::*)() volatile && noexcept, 
    IS_CONST(false), 
    IS_VOLATILE(true), 
    IS_LVALUE(false), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(true)
)

DEFINE_METHOD_IMPL_NO_ARGUMENTS
(
    ResultType(SomeType::*)() const volatile, 
    IS_CONST(true), 
    IS_VOLATILE(true), 
    IS_LVALUE(true), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(false)
)

DEFINE_METHOD_IMPL_NO_ARGUMENTS
(
    ResultType(SomeType::*)() const volatile noexcept, 
    IS_CONST(true), 
    IS_VOLATILE(true), 
    IS_LVALUE(true), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(true)
)

DEFINE_METHOD_IMPL_NO_ARGUMENTS
(
    ResultType(SomeType::*)() const volatile &, 
    IS_CONST(true), 
    IS_VOLATILE(true), 
    IS_LVALUE(true), 
    IS_RVALUE(false), 
    IS_NOEXCEPT(false)
)

DEFINE_METHOD_IMPL_NO_ARGUMENTS
(
    ResultType(SomeType::*)() const volatile & noexcept, 
    IS_CONST(true), 
    IS_VOLATILE(true), 
    IS_LVALUE(true), 
    IS_RVALUE(false), 
    IS_NOEXCEPT(true)
)

DEFINE_METHOD_IMPL_NO_ARGUMENTS
(
    ResultType(SomeType::*)() const volatile &&, 
    IS_CONST(true), 
    IS_VOLATILE(true), 
    IS_LVALUE(false), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(false)
)

DEFINE_METHOD_IMPL_NO_ARGUMENTS
(
    ResultType(SomeType::*)() const volatile && noexcept, 
    IS_CONST(true), 
    IS_VOLATILE(true), 
    IS_LVALUE(false), 
    IS_RVALUE(true), 
    IS_NOEXCEPT(true)
)

#endif // METAXXA_detail_METHODS_INC
