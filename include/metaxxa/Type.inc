#ifndef METAXXA_TYPE_INC
#define METAXXA_TYPE_INC

#include "Type.h"

#include "detail/OperatorTesters.h"
#include "detail/HasMethodToString.h"
#include "detail/IsExplicitlyConstructible.h"
#include "detail/IsImplicitlyConstructible.h"
#include "detail/IsInstantiationOf.h"
#include "detail/Demangle.h"
#include "detail/IsTemplate.h"
#include "FunctionTag.h"


namespace metaxxa
{
    template <typename SomeType>
    std::string Type<SomeType>::get_name()
    {
        return detail::demangle_no_cvr<SomeType>();
    }

    template <typename SomeType>
    std::string Type<SomeType>::name()
    {
        return get_name();
    }

    template <typename SomeType>
    std::string Type<SomeType>::get_short_name()
    {
        auto type_name = name();
        
        auto template_params_begin = type_name.find_first_of("<");

        std::string::size_type namespace_end_index;
        if (template_params_begin != std::string::npos)
            namespace_end_index = type_name.substr(0, template_params_begin).find_last_of("::");
        else 
            namespace_end_index = type_name.find_last_of("::");

        if (namespace_end_index != std::string::npos)
            type_name = type_name.substr(namespace_end_index + 1);

        if constexpr (std::is_class_v<SomeType>)
            return "class " + type_name;
        else
            return type_name;
    }

    template <typename SomeType>
    std::string Type<SomeType>::short_name()
    {
        return get_short_name();
    }

    template <typename SomeType>
    std::string Type<SomeType>::get_name_without_templates()
    {
        auto type_name = name();

        auto template_params_begin = type_name.find_first_of("<");
        if (template_params_begin != std::string::npos)
            type_name = type_name.substr(0, template_params_begin);

        return type_name;
    }

    template <typename SomeType>
    std::string Type<SomeType>::name_without_templates()
    {
        return get_name_without_templates();
    }

    template <typename SomeType>
    std::string Type<SomeType>::get_short_name_without_templates()
    {
        auto type_name = name();

        auto template_params_begin = type_name.find_first_of("<");
        if (template_params_begin != std::string::npos)
            type_name = type_name.substr(0, template_params_begin);

        auto namespace_end_index = type_name.find_last_of("::");
        if (namespace_end_index != std::string::npos)
            type_name = type_name.substr(namespace_end_index + 1);

        if constexpr (std::is_class_v<SomeType>)
            return "class " + type_name;
        else
            return type_name;
    }

    template <typename SomeType>
    std::string Type<SomeType>::short_name_without_templates()
    {
        return get_short_name_without_templates();
    }

    template <typename SomeType>
    std::string Type<SomeType>::get_name_with_modifiers()
    {
        return detail::demangle<SomeType>();
    }

    template <typename SomeType>
    std::string Type<SomeType>::name_with_modifiers()
    {
        return get_name_with_modifiers();
    }

    template <typename SomeType>
    std::type_index Type<SomeType>::get_index() 
    {
        return std::type_index(typeid(SomeType));
    }

    template <typename SomeType>
    std::type_index Type<SomeType>::index() 
    {
        return get_index();
    }

    template <typename SomeType>
    constexpr bool Type<SomeType>::has_method_to_string()
    {
        return detail::has_method_to_string<SomeType>();
    }

    template <typename SomeType>
    template <typename ToType>
    constexpr bool Type<SomeType>::is_convertible_to()
    {
        return std::is_convertible_v<SomeType, ToType>;
    }

    template <typename SomeType>
    template <typename DerivedType>
    constexpr bool Type<SomeType>::is_base_of()
    {
        return std::is_base_of_v<SomeType, DerivedType>;
    }

    template <typename SomeType>
    template <typename BaseType>
    constexpr bool Type<SomeType>::is_derived_from()
    {
        return std::is_base_of_v<BaseType, SomeType>;
    }

    template <typename SomeType>
    template <typename FromType>
    constexpr bool Type<SomeType>::is_convertible_from()
    {
        return std::is_convertible_v<FromType, SomeType>;
    }

    template <typename SomeType>
    constexpr bool Type<SomeType>::is_fundamental()
    {
        return std::is_fundamental_v<SomeType>;
    }

    template <typename SomeType>
    constexpr bool Type<SomeType>::is_class()
    {
        return std::is_class_v<SomeType>;
    }

    template <typename SomeType>
    constexpr bool Type<SomeType>::is_pod()
    {
        return std::is_pod_v<SomeType>;
    }

    template <typename SomeType>
    constexpr bool Type<SomeType>::is_pointer()
    {
        return std::is_pointer_v<SomeType>;
    }

    template <typename SomeType>
    constexpr bool Type<SomeType>::is_reference()
    {
        return std::is_reference_v<SomeType>;
    }

    template <typename SomeType>
    constexpr bool Type<SomeType>::is_lvalue_reference()
    {
        return std::is_lvalue_reference_v<SomeType>;
    }

    template <typename SomeType>
    constexpr bool Type<SomeType>::is_rvalue_reference()
    {
        return std::is_rvalue_reference_v<SomeType>;
    }

    template <typename SomeType>
    template <typename Argument>
    constexpr bool Type<SomeType>::is_implicitly_constructible_from()
    {
        return detail::IS_IMPLICITLY_CONSTRUCTIBLE<SomeType, Argument>;
    }

    template <typename SomeType>
    template <typename Argument>
    constexpr bool Type<SomeType>::is_explicitly_constructible_from()
    {
        return detail::IS_EXPLICITLY_CONSTRUCTIBLE<SomeType, Argument>;
    }

    template <typename SomeType>
    template <template <typename...> typename TemplateType>
    constexpr bool Type<SomeType>::is_instantiation_of()
    {
        return detail::IS_INSTANTIATION_OF<TemplateType, SomeType>;
    }

    template <typename SomeType>
    constexpr bool Type<SomeType>::is_template()
    {
        return detail::IS_TEMPLATE<SomeType>;
    }

    template <typename SomeType>
    constexpr bool Type<SomeType>::is_usual_callable()
    {
        return is_derived_from<FunctionTag>();
    }

    // ASSIGNMENT 
    // {
    ___METAXXA___TYPE___DEFINE_BINARY_OPERATOR(assign);
    ___METAXXA___TYPE___DEFINE_BINARY_OPERATOR(plus_assign);
    ___METAXXA___TYPE___DEFINE_BINARY_OPERATOR(subtract_assign);
    ___METAXXA___TYPE___DEFINE_BINARY_OPERATOR(multiply_assign);
    ___METAXXA___TYPE___DEFINE_BINARY_OPERATOR(divide_assign);
    ___METAXXA___TYPE___DEFINE_BINARY_OPERATOR(mod_assign);
    ___METAXXA___TYPE___DEFINE_BINARY_OPERATOR(bit_and_assign);
    ___METAXXA___TYPE___DEFINE_BINARY_OPERATOR(bit_or_assign);
    ___METAXXA___TYPE___DEFINE_BINARY_OPERATOR(bit_xor_assign);
    ___METAXXA___TYPE___DEFINE_BINARY_OPERATOR(left_shift_assign);
    ___METAXXA___TYPE___DEFINE_BINARY_OPERATOR(right_shift_assign);
    // }

    // (IN|DE)CREMENT
    // {
    ___METAXXA___TYPE___DEFINE_UNARY_OPERATOR(increment);
    ___METAXXA___TYPE___DEFINE_UNARY_OPERATOR(decrement);
    // }

    // ARITHMETIC
    // {
    ___METAXXA___TYPE___DEFINE_UNARY_AND_BINARY_OPERATOR(plus);
    ___METAXXA___TYPE___DEFINE_UNARY_AND_BINARY_OPERATOR(minus);
    ___METAXXA___TYPE___DEFINE_BINARY_OPERATOR(divide);
    ___METAXXA___TYPE___DEFINE_BINARY_OPERATOR(mod);
    ___METAXXA___TYPE___DEFINE_UNARY_OPERATOR (tilde);
    ___METAXXA___TYPE___DEFINE_BINARY_OPERATOR(bit_or);
    ___METAXXA___TYPE___DEFINE_BINARY_OPERATOR(bit_xor);
    ___METAXXA___TYPE___DEFINE_BINARY_OPERATOR(left_shift);
    ___METAXXA___TYPE___DEFINE_BINARY_OPERATOR(right_shift);
    // }


    // LOGICAL
    // {
    ___METAXXA___TYPE___DEFINE_UNARY_OPERATOR (not);
    ___METAXXA___TYPE___DEFINE_BINARY_OPERATOR(logical_and);
    ___METAXXA___TYPE___DEFINE_BINARY_OPERATOR(logical_or);
    // }

    // COMPARISON
    // {
    ___METAXXA___TYPE___DEFINE_BINARY_OPERATOR(equal);
    ___METAXXA___TYPE___DEFINE_BINARY_OPERATOR(not_equal);
    ___METAXXA___TYPE___DEFINE_BINARY_OPERATOR(less);
    ___METAXXA___TYPE___DEFINE_BINARY_OPERATOR(greater);
    ___METAXXA___TYPE___DEFINE_BINARY_OPERATOR(less_equal);
    ___METAXXA___TYPE___DEFINE_BINARY_OPERATOR(greater_equal);
    // }

    // MEMBER ACCESS
    // {
    ___METAXXA___TYPE___DEFINE_BINARY_OPERATOR(subscript);
    ___METAXXA___TYPE___DEFINE_UNARY_OPERATOR (pointer_access);
    ___METAXXA___TYPE___DEFINE_UNARY_OPERATOR (pointer_to_member_access);
    // }

    // OTHER
    // {

    ___METAXXA___TYPE___DEFINE_NAMED_UNARY_AND_BINARY_OPERATOR(asterisk, dereference, multiply);
    ___METAXXA___TYPE___DEFINE_NAMED_UNARY_AND_BINARY_OPERATOR(ampersand, address, bit_and);
    ___METAXXA___TYPE___DEFINE_BINARY_OPERATOR(comma);
    ___METAXXA___TYPE___DEFINE_UNARY_OPERATOR (call);

    template <typename SomeType>
    template <typename ToType>
    constexpr bool Type<SomeType>::has_operator()
    {
    	return detail::___METAXXA___OPERATOR_TESTER(cast_operator)<SomeType, ToType, void>::has();
    }
}

template <typename FirstType, typename SecondType>
constexpr bool operator==(metaxxa::Type<FirstType>, metaxxa::Type<SecondType>)
{
	return std::is_same_v<FirstType, SecondType>;
}

template <typename FirstType, typename SecondType>
constexpr bool operator!=(metaxxa::Type<FirstType>, metaxxa::Type<SecondType>)
{
	return !std::is_same_v<FirstType, SecondType>;
}

#endif // METAXXA_TYPE_INC