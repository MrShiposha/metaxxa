#ifndef METAXXA_TESTMOVEFUNCTIONARGUMENTTYPES_H
#define METAXXA_TESTMOVEFUNCTIONARGUMENTTYPES_H

#include <string>
#include <map>
#include <vector>
#include <functional>

#include "TestMetaxxa.h"

void my_fn(int a, double b, const char *m)
{}

struct TestMoveFunctionArgumentTypes : TestMetaxxa
{
	using Vector = std::vector<int>;
	using Pair = std::pair<const std::string &, void *>;
	using Tuple = std::tuple<const Pair &, std::map<char, int>>;
	using F1 = std::function<void(int)>;
	using F2 = std::function<void(const std::string &, void *)>;
	using F3 = std::function<void(const Pair &, std::map<char, int>)>;

	virtual bool test() override
	{	
		static_assert(std::is_same_v<metaxxa::MoveFunctionArgumentTypes<std::vector, F1>, Vector>, "class TestMoveFunctionArgumentTypes: test failed");
		static_assert(std::is_same_v<metaxxa::MoveFunctionArgumentTypes<std::pair, F2>,   Pair>,   "class TestMoveFunctionArgumentTypes: test failed");
		static_assert(std::is_same_v<metaxxa::MoveFunctionArgumentTypes<std::tuple, F3>,  Tuple>,  "class TestMoveFunctionArgumentTypes: test failed");


		using namespace metaxxa;

		using T = MoveFunctionArgumentTypes<std::tuple, decltype(my_fn)>;

		return true;
	}
};
 
#endif // METAXXA_TESTMOVEFUNCTIONARGUMENTTYPES_H
