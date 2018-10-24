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

TEST(TestHasMethod, NoArguments)
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

TEST(TestHasMethod, WithArguments)
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