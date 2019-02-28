#ifndef METAXXA_TYPE_H
#define METAXXA_TYPE_H

#include <typeinfo>
#include <typeindex>
#include <type_traits>

#include "detail/MoveTemplateTypes.h"
#include "detail/MoveTemplateTypesUnique.h"
#include "detail/WrapToTemplateIfNotWrapped.h"
#include "detail/TypeHasOperatorMethodMacros.h"

namespace metaxxa
{
	template <typename SomeType>
	class Type
	{
	public:
		template <template <typename...> typename TemplateType>
		using MoveTemplateTypes = detail::MoveTemplateTypes<TemplateType, SomeType>;

		template <template <typename...> typename TemplateType>
		using MoveTemplateTypesUnique = detail::MoveTemplateTypesUnique<TemplateType, SomeType>;

		template <template <typename...> typename TemplateType>
		using WrapToTemplateIfNotWrapped = typename detail::template WrapToTemplateIfNotWrapped<TemplateType, SomeType>::Result;

		static std::string get_name();

		static std::string name();

		static std::string get_short_name();

		static std::string short_name();

		static std::string get_name_without_templates();

		static std::string name_without_templates();

		static std::string get_short_name_without_templates();

		static std::string short_name_without_templates();

		static std::string get_name_with_modifiers();

		static std::string name_with_modifiers();

		static std::type_index get_index();

		static std::type_index index();

		static constexpr bool has_method_to_string();

		template <typename ToType>
		static constexpr bool is_convertible_to();

		template <typename DerivedType>
		static constexpr bool is_base_of();

		template <typename BaseType>
		static constexpr bool is_derived_from();

		template <typename FromType>
		static constexpr bool is_convertible_from();

		static constexpr bool is_fundamental();

		static constexpr bool is_class();

		static constexpr bool is_pod();

		static constexpr bool is_pointer();

		static constexpr bool is_reference();

		static constexpr bool is_lvalue_reference();

		static constexpr bool is_rvalue_reference();

		template <typename Argument>
		static constexpr bool is_implicitly_constructible_from();

		template <typename Argument>
		static constexpr bool is_explicitly_constructible_from();

		template <template <typename...> typename TemplateType>
		static constexpr bool is_instantiation_of();

		static constexpr bool is_template();

		static constexpr bool is_usual_callable();

		// ASSIGNMENT 
		// {
		___METAXXA___TYPE___DECLARE_BINARY_OPERATOR(assign);
		___METAXXA___TYPE___DECLARE_BINARY_OPERATOR(plus_assign);
		___METAXXA___TYPE___DECLARE_BINARY_OPERATOR(subtract_assign);
		___METAXXA___TYPE___DECLARE_BINARY_OPERATOR(multiply_assign);
		___METAXXA___TYPE___DECLARE_BINARY_OPERATOR(divide_assign);
		___METAXXA___TYPE___DECLARE_BINARY_OPERATOR(mod_assign);
		___METAXXA___TYPE___DECLARE_BINARY_OPERATOR(bit_and_assign);
		___METAXXA___TYPE___DECLARE_BINARY_OPERATOR(bit_or_assign);
		___METAXXA___TYPE___DECLARE_BINARY_OPERATOR(bit_xor_assign);
		___METAXXA___TYPE___DECLARE_BINARY_OPERATOR(left_shift_assign);
		___METAXXA___TYPE___DECLARE_BINARY_OPERATOR(right_shift_assign);
		// }

		// (IN|DE)CREMENT
		// {
		___METAXXA___TYPE___DECLARE_UNARY_OPERATOR(increment);
		___METAXXA___TYPE___DECLARE_UNARY_OPERATOR(decrement);
		// }

		// ARITHMETIC
		// {
		___METAXXA___TYPE___DECLARE_UNARY_AND_BINARY_OPERATOR(plus);
		___METAXXA___TYPE___DECLARE_UNARY_AND_BINARY_OPERATOR(minus);
		___METAXXA___TYPE___DECLARE_BINARY_OPERATOR(divide);
		___METAXXA___TYPE___DECLARE_BINARY_OPERATOR(mod);
		___METAXXA___TYPE___DECLARE_UNARY_OPERATOR (tilde);
		___METAXXA___TYPE___DECLARE_BINARY_OPERATOR(bit_or);
		___METAXXA___TYPE___DECLARE_BINARY_OPERATOR(bit_xor);
		___METAXXA___TYPE___DECLARE_BINARY_OPERATOR(left_shift);
		___METAXXA___TYPE___DECLARE_BINARY_OPERATOR(right_shift);
		// }


		// LOGICAL
		// {
		___METAXXA___TYPE___DECLARE_UNARY_OPERATOR (not);
		___METAXXA___TYPE___DECLARE_BINARY_OPERATOR(logical_and);
		___METAXXA___TYPE___DECLARE_BINARY_OPERATOR(logical_or);
		// }

		// COMPARISON
		// {
		___METAXXA___TYPE___DECLARE_BINARY_OPERATOR(equal);
		___METAXXA___TYPE___DECLARE_BINARY_OPERATOR(not_equal);
		___METAXXA___TYPE___DECLARE_BINARY_OPERATOR(less);
		___METAXXA___TYPE___DECLARE_BINARY_OPERATOR(greater);
		___METAXXA___TYPE___DECLARE_BINARY_OPERATOR(less_equal);
		___METAXXA___TYPE___DECLARE_BINARY_OPERATOR(greater_equal);
		// }

		// MEMBER ACCESS
		// {
		___METAXXA___TYPE___DECLARE_BINARY_OPERATOR(subscript);
		___METAXXA___TYPE___DECLARE_UNARY_OPERATOR (pointer_access);
		___METAXXA___TYPE___DECLARE_UNARY_OPERATOR (pointer_to_member_access);
		// }

		// OTHER
		// {

		___METAXXA___TYPE___DECLARE_NAMED_UNARY_AND_BINARY_OPERATOR(asterisk, dereference, multiply);
		___METAXXA___TYPE___DECLARE_NAMED_UNARY_AND_BINARY_OPERATOR(ampersand, address, bit_and);
		___METAXXA___TYPE___DECLARE_BINARY_OPERATOR(comma);
		___METAXXA___TYPE___DECLARE_UNARY_OPERATOR (call);

		template <typename ToType>
		static constexpr bool has_operator();
		// }
	};
}

template <typename FirstType, typename SecondType>
constexpr bool operator==(metaxxa::Type<FirstType>, metaxxa::Type<SecondType>);

template <typename FirstType, typename SecondType>
constexpr bool operator!=(metaxxa::Type<FirstType>, metaxxa::Type<SecondType>);

#endif // METAXXA_TYPE_H