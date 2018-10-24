#ifndef METAXXA_TESTMOVEFUNCTIONARGUMENTTYPES_H
#define METAXXA_TESTMOVEFUNCTIONARGUMENTTYPES_H

#include <MoveFunctionArgumentTypes.h>

struct TestMoveFunctionArgumentTypes : testing::Test
{
	using Vector = std::vector<int>;

	using Pair = std::pair<const std::string &, void *>;

	using Tuple = std::tuple<const Pair &, std::map<char, int>>;

	using F1 = std::function<void(int)>;

	using F2 = std::function<void(const std::string &, void *)>;

	using F3 = std::function<void(const Pair &, std::map<char, int>)>;
};

TEST_F(TestMoveFunctionArgumentTypes, TestTypes)
{
	using namespace std;
	using metaxxa::MoveFunctionArgumentTypes;
	using testing::StaticAssertTypeEq;

	StaticAssertTypeEq<MoveFunctionArgumentTypes<vector, F1>, Vector>();
	StaticAssertTypeEq<MoveFunctionArgumentTypes<pair, F2>,   Pair>  ();
	StaticAssertTypeEq<MoveFunctionArgumentTypes<tuple, F3>,  Tuple> ();

}
 
#endif // METAXXA_TESTMOVEFUNCTIONARGUMENTTYPES_H
