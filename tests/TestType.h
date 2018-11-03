#include <Type.h>
#include <CallableToMethod.h>

#include <type_traits>

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

TEST(TestType, TestHasMethodNoArguments)
{
	using metaxxa::Type;

	EXPECT_TRUE(Type<StructUnary>::has_single_operator_unary_plus());
	EXPECT_FALSE(Type<StructUnary>::has_single_operator_binary_plus());
	EXPECT_TRUE(Type<StructUnary>::has_single_operator_asterisk_dereference());
	EXPECT_FALSE(Type<StructUnary>::has_single_operator_asterisk_multiply());
	EXPECT_TRUE(Type<StructUnary>::has_single_operator_ampersand_address());
	EXPECT_FALSE(Type<StructUnary>::has_single_operator_ampersand_bit_and());

	EXPECT_TRUE(Type<StructBinary>::has_single_operator_binary_plus());
	EXPECT_FALSE(Type<StructBinary>::has_single_operator_unary_plus());
	EXPECT_TRUE(Type<StructBinary>::has_single_operator_asterisk_multiply());
	EXPECT_FALSE(Type<StructBinary>::has_single_operator_asterisk_dereference());
	EXPECT_TRUE(Type<StructBinary>::has_single_operator_ampersand_bit_and());
	EXPECT_FALSE(Type<StructBinary>::has_single_operator_ampersand_address());

	EXPECT_FALSE(Type<StructUnaryBinary>::has_single_operator_unary_plus());
	EXPECT_FALSE(Type<StructUnaryBinary>::has_single_operator_binary_plus());
	EXPECT_FALSE(Type<StructUnaryBinary>::has_single_operator_asterisk_dereference());
	EXPECT_FALSE(Type<StructUnaryBinary>::has_single_operator_asterisk_multiply());
	EXPECT_FALSE(Type<StructUnaryBinary>::has_single_operator_ampersand_address());
	EXPECT_FALSE(Type<StructUnaryBinary>::has_single_operator_ampersand_bit_and());
}

TEST(TestType, TestHasMethodWithArguments)
{
	using metaxxa::Type;
	using metaxxa::Function;
	using metaxxa::CallableToMethod;

	EXPECT_TRUE(Type<StructUnary>::has_operator_plus<void()>());
	EXPECT_FALSE(Type<StructUnary>::has_operator_plus<void(int)>());
	EXPECT_TRUE(Type<StructUnary>::has_operator_dereference<int()>());
	EXPECT_FALSE(Type<StructUnary>::has_operator_multiply<int(int)>());
	EXPECT_TRUE(Type<StructUnary>::has_operator_address<int()>());
	EXPECT_FALSE(Type<StructUnary>::has_operator_bit_and<int(int)>());

	EXPECT_TRUE(Type<StructBinary>::has_operator_plus<void(int)>());
	EXPECT_FALSE(Type<StructBinary>::has_operator_plus<void()>());
	EXPECT_TRUE(Type<StructBinary>::has_operator_multiply<int(int)>());
	EXPECT_FALSE(Type<StructBinary>::has_operator_dereference<int()>());
	EXPECT_TRUE(Type<StructBinary>::has_operator_bit_and<int(int)>());
	EXPECT_FALSE(Type<StructBinary>::has_operator_address<int()>());

	EXPECT_TRUE(Type<StructUnaryBinary>::has_operator_plus<void(int)>());
	EXPECT_TRUE(Type<StructUnaryBinary>::has_operator_plus<void()>());
	EXPECT_TRUE(Type<StructUnaryBinary>::has_operator_multiply<int(int)>());
	EXPECT_TRUE(Type<StructUnaryBinary>::has_operator_dereference<int()>());
	EXPECT_TRUE(Type<StructUnaryBinary>::has_operator_bit_and<int(int)>());
	EXPECT_TRUE(Type<StructUnaryBinary>::has_operator_address<int()>());

	EXPECT_TRUE(Type<Ambiguous>::has_operator_plus<void(int)>());
	EXPECT_TRUE(Type<Ambiguous>::has_operator_plus<void()>());

}

struct TestImpl
{
	TestImpl(int) {}

	TestImpl(void *) {}

	explicit TestImpl(const char *) {}
};

TEST(TestType, TestIsImplicitlyConstructible)
{
	using namespace std;
	using namespace metaxxa;
	bool result;
	
	result = Type<std::string>::is_implicitly_constructible_from<const char *>();
	EXPECT_TRUE(result);

	result = Type<int>::is_implicitly_constructible_from<char>();
	EXPECT_TRUE(result);

	result = Type<TestImpl>::is_implicitly_constructible_from<int>();
	EXPECT_TRUE(result);

	result = Type<TestImpl>::is_implicitly_constructible_from<void*>();
	EXPECT_TRUE(result);

	result = Type<int *>::is_implicitly_constructible_from<char *>();
	EXPECT_FALSE(result);

	result = Type<TestImpl>::is_implicitly_constructible_from<const char*>();
	EXPECT_FALSE(result);
}

struct TestExpl
{
	TestExpl(int) {}

	TestExpl(void *) {}

	explicit TestExpl(const char *) {}
};


TEST(TestType, TestIsExplicitlyConstructible)
{
	using namespace std;
	using namespace metaxxa;
	bool result;

	result = Type<TestExpl>::is_explicitly_constructible_from<const char*>();
	EXPECT_TRUE(result);

	result = Type<std::string>::is_explicitly_constructible_from<const char *>();
	EXPECT_FALSE(result);

	result = Type<int>::is_explicitly_constructible_from<char>();
	EXPECT_FALSE(result);

	result = Type<TestExpl>::is_explicitly_constructible_from<int>();
	EXPECT_FALSE(result);

	result = Type<TestExpl>::is_explicitly_constructible_from<void*>();
	EXPECT_FALSE(result);
}


template <typename T>
class TemplateClass
{};

TEST(TestType, TestIsInstantiationOf)
{
	using namespace metaxxa;

	static_assert(Type<TemplateClass<int>>::is_instantiation_of<TemplateClass>(), "class Type<T>: is_instantiation_of failed");
	static_assert(!Type<TemplateClass<int>>::is_instantiation_of<std::optional>(), "class Type<T>: is_instantiation_of failed");

	static_assert(Type<Tuple<int, char>>::is_instantiation_of<Tuple>(), "class Type<T>: is_instantiation_of failed");
	static_assert(!Type<std::variant<int, char>>::is_instantiation_of<Tuple>(), "class Type<T>: is_instantiation_of failed");
}

TEST(TestType, TestWrapIfNotWrapped)
{
	using namespace metaxxa;

	static_assert(std::is_same_v<Type<Tuple<int, char>>::template WrapToTemplateIfNotWrapped<Tuple>, Tuple<int, char>>, "class Type<T>: WrapToTemplateIfNotWrapped failed");
	static_assert(std::is_same_v<Type<int>::template WrapToTemplateIfNotWrapped<Tuple>, Tuple<int>>, "class Type<T>: WrapToTemplateIfNotWrapped failed");
}