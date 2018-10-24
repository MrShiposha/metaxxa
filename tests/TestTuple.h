#ifndef METAXXA_TESTTUPLE_H
#define METAXXA_TESTTUPLE_H

#include <optional>
#include <Tuple.h>

TEST(TestTuple, TestSize)
{
	EXPECT_EQ(metaxxa::tuple().size(), 0);
	EXPECT_EQ(metaxxa::tuple(1).size(), 1);
	EXPECT_EQ(metaxxa::tuple(1, 2).size(), 2);
	EXPECT_EQ(metaxxa::tuple(1, 2, 3).size(), 3);
	EXPECT_EQ(metaxxa::tuple(1, 2, 3, 4).size(), 4);
}

TEST(TestTuple, SkipFirst)
{
	int     _1  = 1;
	char    _2  = 'A';
	char   _3[] = "My message";
	double _4   = 3.14;

	auto source = metaxxa::tuple(_1, _2, _3, _4);
	auto result_1 = metaxxa::tuple(_2, _3, _4);
	auto result_2 = metaxxa::tuple(_3, _4);
	auto result_3 = metaxxa::tuple(_4);
	auto result_4 = metaxxa::tuple();

	EXPECT_EQ(source.skip_first<0>(), source);
	EXPECT_EQ(source.skip_first<1>(), result_1);
	EXPECT_EQ(source.skip_first<2>(), result_2);
	EXPECT_EQ(source.skip_first<3>(), result_3);
	EXPECT_EQ(source.skip_first<4>(), result_4);
}

TEST(TestTuple, TestMap)
{
	auto source = metaxxa::tuple(1, 2, int16_t(-1), size_t(3));
	auto map_result = source.map([](auto const &value) { return value * 10; });

	auto result = metaxxa::tuple(10, 20, int16_t(-10), size_t(30));

	EXPECT_EQ(map_result, result);
}

template <typename Type>
struct MapArithmeticToInt
{
	constexpr auto operator()()
	{
		if constexpr (std::is_arithmetic_v<Type>)
			return int();
		else
			return Type();
	}
};

TEST(TestTuple, TestMapTypes)
{
	using Source = metaxxa::Tuple<int, double, char, std::string, bool>;

	using MappedTuple = decltype(Source::map_types<MapArithmeticToInt>());
	testing::StaticAssertTypeEq<MappedTuple, metaxxa::Tuple<int, int, int, std::string, int>>();
}

TEST(TestTuple, TestSum)
{
	auto tuple = metaxxa::tuple(1, 5, 3.14, 5.1f, 'A', 0);

	EXPECT_NEAR(tuple.sum(), 79.24, 0.001);
}

TEST(TestTuple, JustObjects)
{
    std::tuple<const int, const char, const double> t;
    
    testing::StaticAssertTypeEq<decltype(metaxxa::just_objects_types<decltype(t)>()), std::tuple<int, char, double>>();
}

TEST(TestTuple, TestMakeTuple)
{
    int var = 42;
    const int &cr = var;
    int &r = var;
    auto tref = metaxxa::tuple(var, cr, r);
    
    testing::StaticAssertTypeEq<metaxxa::Tuple<int &, const int &, int &>, decltype(tref)>();
}


template <typename Type>
struct IsSingleSize
{
	constexpr bool operator()()
	{
		return sizeof(Type) == 1;
	}
};

struct MyOrType {};

struct MySingleSize {};

TEST(TestTuple, TestFindTypes)
{
	metaxxa::Tuple<int, MySingleSize, short, double, std::string> expected_found;
	metaxxa::Tuple<int, double, std::string> expected_not_found;

	{
		using SingleSizeOptional = decltype(expected_found.find_types<IsSingleSize>());

		EXPECT_TRUE(SingleSizeOptional::FOUND);
		EXPECT_EQ(SingleSizeOptional::INDEX, 1);
		testing::StaticAssertTypeEq<SingleSizeOptional::Type, MySingleSize>();
		testing::StaticAssertTypeEq<SingleSizeOptional::TypeOr<MyOrType>, MySingleSize>();
	} 

	{
		using SingleSizeOptional = decltype(expected_not_found.find_types<IsSingleSize>());

		EXPECT_FALSE(SingleSizeOptional::FOUND);
		testing::StaticAssertTypeEq<SingleSizeOptional::TypeOr<MyOrType>, MyOrType>();
	}
}


TEST(TestTuple, TestOptionals)
{
	using Test = typename metaxxa::Tuple<int, double, std::string>::Optionals;
	testing::StaticAssertTypeEq<Test, metaxxa::Tuple<std::optional<int>, std::optional<double>, std::optional<std::string>>>();
}

TEST(TestTuple, TestFilter)
{
	metaxxa::Tuple<int, int, short, double, std::string, char, const char *, const char *> t(1, 12, 42, 3.14, "44", char(4), "0", "15");
 
	auto filtered = t.filter([](auto value) 
	{ 
		if constexpr(std::is_same_v<decltype(value), std::string> || std::is_same_v<decltype(value), const char *>)
			return std::stoi(value) > 10;
		else
		{
			return value > 10;
		}
	});

	EXPECT_FALSE(filtered.get<0>());
	EXPECT_TRUE (filtered.get<1>());
	EXPECT_TRUE (filtered.get<2>());
	EXPECT_FALSE(filtered.get<3>());
	EXPECT_TRUE (filtered.get<4>());
	EXPECT_FALSE(filtered.get<5>());
	EXPECT_FALSE(filtered.get<6>());
	EXPECT_TRUE (filtered.get<7>());

	EXPECT_EQ(filtered.get<1>().value(), 12);
	EXPECT_EQ(filtered.get<2>().value(), 42);
	EXPECT_EQ(filtered.get<4>().value(), "44");
	EXPECT_STREQ(filtered.get<7>().value(), "15");
}


template <typename Type>
struct IsCharOrString
{
	constexpr bool operator()()
	{
		return std::is_same_v<Type, char> || std::is_same_v<Type, std::string>; 
	}
};

TEST(TestTuple, TestFilterTypes)
{
	using Test = metaxxa::Tuple<int, double, char, std::string, bool>;

	using FilteredTuple = decltype(Test::filter_types<IsCharOrString>());
	testing::StaticAssertTypeEq<FilteredTuple, metaxxa::Tuple<char, std::string>>();
}

#endif // METAXXA_TESTTUPLE_H
