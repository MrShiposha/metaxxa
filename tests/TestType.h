#include <type_traits>
#include <variant>

#include <metaxxa/Type.h>
#include <metaxxa/Function.h>
#include <metaxxa/CallableToMethod.h>

#include "TestMetaxxa.h"

struct TestType : TestMetaxxa
{
	struct StructUnary
	{
		void operator+() {}

		int operator*() { return 0; }

		int operator&() { return 0; }
	};

	struct StructBinary
	{
		void operator+(int) {}

		int operator*(int) { return 0; }

		int operator&(int) { return 0; }
	};

	struct StructUnaryBinary
	{
		void operator+() {}

		int operator*() { return 0; }

		int operator&() { return 0; }

		void operator+(int) {}

		int operator*(int) { return 0; }

		int operator&(int) { return 0; }
	};

	struct Ambiguous
	{
		void operator+() {}

		void operator+(int) {}
	};

	struct TestImpl
	{
		TestImpl(int) {}

		TestImpl(void *) {}

		explicit TestImpl(const char *) {}
	};

	struct TestExpl
	{
		TestExpl(int) {}

		TestExpl(void *) {}

		explicit TestExpl(const char *) {}
	};

	template <typename T>
	class TemplateClass
	{};

	virtual bool test() override
	{
		bool result = true;
		result = result && test_has_method_with_arguments();
		result = result && test_has_method_without_arguments();
		result = result && test_is_implicitly_constructible();
		result = result && test_is_explicitly_constructible();
		result = result && test_is_instantiation_of();
		result = result && test_wrap_if_not_wrapped();
		result = result && test_move_template_types();
		result = result && test_move_template_types_unique();
		
		return result;
	}

	bool test_has_method_without_arguments()
	{
		using metaxxa::Type;

		static_assert(Type<StructUnary>::has_single_operator_unary_plus(),           "class Type: has method without arguments test failed");
		static_assert(!Type<StructUnary>::has_single_operator_binary_plus(),         "class Type: has method without arguments test failed");
		static_assert(Type<StructUnary>::has_single_operator_asterisk_dereference(), "class Type: has method without arguments test failed");
		static_assert(!Type<StructUnary>::has_single_operator_asterisk_multiply(),   "class Type: has method without arguments test failed");
		static_assert(Type<StructUnary>::has_single_operator_ampersand_address(),    "class Type: has method without arguments test failed");
		static_assert(!Type<StructUnary>::has_single_operator_ampersand_bit_and(),   "class Type: has method without arguments test failed");

		static_assert(Type<StructBinary>::has_single_operator_binary_plus(),           "class Type: has method without arguments test failed");
		static_assert(!Type<StructBinary>::has_single_operator_unary_plus(),           "class Type: has method without arguments test failed");
		static_assert(Type<StructBinary>::has_single_operator_asterisk_multiply(),     "class Type: has method without arguments test failed");
		static_assert(!Type<StructBinary>::has_single_operator_asterisk_dereference(), "class Type: has method without arguments test failed");
		static_assert(Type<StructBinary>::has_single_operator_ampersand_bit_and(),     "class Type: has method without arguments test failed");
		static_assert(!Type<StructBinary>::has_single_operator_ampersand_address(),    "class Type: has method without arguments test failed");

		static_assert(!Type<StructUnaryBinary>::has_single_operator_unary_plus(),           "class Type: has method without arguments test failed");
		static_assert(!Type<StructUnaryBinary>::has_single_operator_binary_plus(),          "class Type: has method without arguments test failed");
		static_assert(!Type<StructUnaryBinary>::has_single_operator_asterisk_dereference(), "class Type: has method without arguments test failed");
		static_assert(!Type<StructUnaryBinary>::has_single_operator_asterisk_multiply(),    "class Type: has method without arguments test failed");
		static_assert(!Type<StructUnaryBinary>::has_single_operator_ampersand_address(),    "class Type: has method without arguments test failed");
		static_assert(!Type<StructUnaryBinary>::has_single_operator_ampersand_bit_and(),    "class Type: has method without arguments test failed");

		return true;
	}

	bool test_has_method_with_arguments()
	{
		using metaxxa::Type;
		using metaxxa::Function;
		using metaxxa::CallableToMethod;

		static_assert(Type<StructUnary>::has_operator_plus<void()>());
		static_assert(!Type<StructUnary>::has_operator_plus<void(int)>());
		static_assert(Type<StructUnary>::has_operator_dereference<int()>());
		static_assert(!Type<StructUnary>::has_operator_multiply<int(int)>());
		static_assert(Type<StructUnary>::has_operator_address<int()>());
		static_assert(!Type<StructUnary>::has_operator_bit_and<int(int)>());

		static_assert(Type<StructBinary>::has_operator_plus<void(int)>());
		static_assert(!Type<StructBinary>::has_operator_plus<void()>());
		static_assert(Type<StructBinary>::has_operator_multiply<int(int)>());
		static_assert(!Type<StructBinary>::has_operator_dereference<int()>());
		static_assert(Type<StructBinary>::has_operator_bit_and<int(int)>());
		static_assert(!Type<StructBinary>::has_operator_address<int()>());

		static_assert(Type<StructUnaryBinary>::has_operator_plus<void(int)>());
		static_assert(Type<StructUnaryBinary>::has_operator_plus<void()>());
		static_assert(Type<StructUnaryBinary>::has_operator_multiply<int(int)>());
		static_assert(Type<StructUnaryBinary>::has_operator_dereference<int()>());
		static_assert(Type<StructUnaryBinary>::has_operator_bit_and<int(int)>());
		static_assert(Type<StructUnaryBinary>::has_operator_address<int()>());

		static_assert(Type<Ambiguous>::has_operator_plus<void(int)>());
		static_assert(Type<Ambiguous>::has_operator_plus<void()>());

		return true;
	}

	bool test_is_implicitly_constructible()
	{
		using namespace std;
		using namespace metaxxa;
		
		static_assert(Type<std::string>::is_implicitly_constructible_from<const char *>(), "class Type: implicitly constructible test failed");
		static_assert(Type<int>::is_implicitly_constructible_from<char>(),                 "class Type: implicitly constructible test failed");
		static_assert(Type<TestImpl>::is_implicitly_constructible_from<int>(),             "class Type: implicitly constructible test failed");
		static_assert(Type<TestImpl>::is_implicitly_constructible_from<void*>(),           "class Type: implicitly constructible test failed");
		static_assert(!Type<int *>::is_implicitly_constructible_from<char *>(),            "class Type: implicitly constructible test failed");
		static_assert(!Type<TestImpl>::is_implicitly_constructible_from<const char*>(),    "class Type: implicitly constructible test failed");

		return true;
	}

	bool test_is_explicitly_constructible()
	{
		using namespace std;
		using namespace metaxxa;

		static_assert(Type<TestExpl>::is_explicitly_constructible_from<const char*>(),      "class Type: explicitly constructible test failed");
		static_assert(!Type<std::string>::is_explicitly_constructible_from<const char *>(), "class Type: explicitly constructible test failed");
		static_assert(!Type<int>::is_explicitly_constructible_from<char>(),                 "class Type: explicitly constructible test failed");
		static_assert(!Type<TestExpl>::is_explicitly_constructible_from<int>(),             "class Type: explicitly constructible test failed");
		static_assert(!Type<TestExpl>::is_explicitly_constructible_from<void*>(),           "class Type: explicitly constructible test failed");

		return true;
	}

	bool test_is_instantiation_of()
	{
		using namespace metaxxa;

		static_assert(Type<TemplateClass<int>>::is_instantiation_of<TemplateClass>(),  "class Type: is_instantiation_of failed");
		static_assert(!Type<TemplateClass<int>>::is_instantiation_of<std::optional>(), "class Type: is_instantiation_of failed");

		static_assert(Type<Tuple<int, char>>::is_instantiation_of<Tuple>(),         "class Type: is_instantiation_of failed");
		static_assert(!Type<std::variant<int, char>>::is_instantiation_of<Tuple>(), "class Type: is_instantiation_of failed");

		return true;
	}

	bool test_is_template()
	{
		using namespace metaxxa;

		static_assert(Type<std::tuple<int, char>>::is_template(), "class Type: is_template test failed");
		static_assert(!Type<int>::is_template(),                  "class Type: is_template test failed");


		return true;
	}

	bool test_wrap_if_not_wrapped()
	{
		using namespace metaxxa;

		static_assert(std::is_same_v<Type<Tuple<int, char>>::template WrapToTemplateIfNotWrapped<Tuple>, Tuple<int, char>>, "class Type: WrapToTemplateIfNotWrapped failed");
		static_assert(std::is_same_v<Type<int>::template WrapToTemplateIfNotWrapped<Tuple>, Tuple<int>>,                    "class Type: WrapToTemplateIfNotWrapped failed");

		return true;
	}

	bool test_move_template_types()
	{
		using namespace metaxxa;

		static_assert(std::is_same_v<typename Type<Tuple<char, double, int>>::template MoveTemplateTypes<std::variant>, std::variant<char, double, int>>, "class Type: MoveTemplateType test failed");

		return true;
	}

	bool test_move_template_types_unique()
	{
		using namespace metaxxa;

		static_assert(std::is_same_v<typename Type<Tuple<char, double, int, double, char>>::template MoveTemplateTypesUnique<std::variant>, std::variant<char, double, int>>, "class Type: MoveTemplateTypeUnique test failed");
		static_assert(std::is_same_v<typename Type<Tuple<char, double>>::template MoveTemplateTypesUnique<std::variant>, std::variant<char, double>>, 			  			  "class Type: MoveTemplateTypeUnique test failed");

		return true;
	}
};