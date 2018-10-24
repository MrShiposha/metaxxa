#ifndef METAXXA_TESTISIMPLICITLYCONSTRUCTIBLE_H
#define METAXXA_TESTISIMPLICITLYCONSTRUCTIBLE_H

#include <IsImplicitlyConstructible.h>

struct TestImpl
{
	TestImpl(int) {}

	TestImpl(void *) {}

	explicit TestImpl(const char *) {}
};

TEST(TestIsImplicitlyCinstructible, TestTrue)
{
	using namespace std;
	using metaxxa::IS_IMPLICITLY_CONSTRUCTIBLE;
	
	bool result;
	
	result = IS_IMPLICITLY_CONSTRUCTIBLE<std::string, const char *>;
	EXPECT_TRUE(result);

	result = IS_IMPLICITLY_CONSTRUCTIBLE<int, char>;
	EXPECT_TRUE(result);

	result = IS_IMPLICITLY_CONSTRUCTIBLE<TestImpl, int>;
	EXPECT_TRUE(result);

	result = IS_IMPLICITLY_CONSTRUCTIBLE<TestImpl, void*>;
	EXPECT_TRUE(result);
}

TEST(TestIsImplicitlyCinstructible, TestFalse)
{
	using namespace std;
	using metaxxa::IS_IMPLICITLY_CONSTRUCTIBLE;

	bool result;

	result = IS_IMPLICITLY_CONSTRUCTIBLE<int *, char *>;
	EXPECT_FALSE(result);

	result = IS_IMPLICITLY_CONSTRUCTIBLE<TestImpl, const char*>;
	EXPECT_FALSE(result);
}

#endif // METAXXA_TESTISIMPLICITLYCONSTRUCTIBLE_H