#ifndef METAXXA_TESTISEXPLICITLYCONSTRUCTIBLE_H
#define METAXXA_TESTISEXPLICITLYCONSTRUCTIBLE_H

#include <IsExplicitlyConstructible.h>

struct TestExp
{
	TestExp(int) {}

	TestExp(void *) {}

	explicit TestExp(const char *) {}
};


TEST(TestIsExplicitlyCinstructible, TestTrue)
{
	using namespace std;
	using metaxxa::IS_EXPLICITLY_CONSTRUCTIBLE;

	bool result;

	result = IS_EXPLICITLY_CONSTRUCTIBLE<TestExp, const char*>;
	EXPECT_TRUE(result);
}


TEST(TestIsExplicitlyCinstructible, TestFalse)
{
	using namespace std;
	using metaxxa::IS_EXPLICITLY_CONSTRUCTIBLE;

	bool result;

	result = IS_EXPLICITLY_CONSTRUCTIBLE<std::string, const char *>;
	EXPECT_FALSE(result);

	result = IS_EXPLICITLY_CONSTRUCTIBLE<int, char>;
	EXPECT_FALSE(result);

	result = IS_EXPLICITLY_CONSTRUCTIBLE<TestExp, int>;
	EXPECT_FALSE(result);

	result = IS_EXPLICITLY_CONSTRUCTIBLE<TestExp, void*>;
	EXPECT_FALSE(result);
}

#endif // METAXXA_TESTISEXPLICITLYCONSTRUCTIBLE_H