#ifndef METAXXA_TESTFUNCTION_H
#define METAXXA_TESTFUNCTION_H

#include <Function.h>

inline void void_return_function() {}

inline int int_return_function() { return 0; }

struct VoidFunctorClass
{
	VoidFunctorClass() {}

	void operator()()
	{}
};

struct IntFunctorClass
{
	IntFunctorClass() {}

	int operator()()
	{
		return 0;
	}
};

struct VoidFunctorClassConst
{
	VoidFunctorClassConst() {}

	void operator()() const
	{}
};

struct IntFunctorClassConst
{
	IntFunctorClassConst() {}

	int operator()() const
	{
		return 0;
	}
};

struct F1
{
	void operator()(double)
	{}
};

struct F2
{
	void operator()(const std::pair<std::string, float> &, const char *)
	{}
};

struct F3
{
	void operator()(char, double, int)
	{}
};

struct F1Const
{
	F1Const() 
	{}

	void operator()(void(*)(int)) const
	{}
};

struct F2Const
{
	F2Const() 
	{}

	void operator()(int&&, char) const
	{}
};

struct F3Const
{
	F3Const() 
	{}

	void operator()(float, float, double) const
	{}
};


struct TestFunction : testing::Test
{
	using P1 = void(*)(double);
	using P2 = void(*)(int, char);
	using P3 = void(*)(float, const std::string &, int *);

	using F1 = std::function<void(std::vector<bool>)>;
	using F2 = std::function<void(std::initializer_list<float>, const std::string &)>;
	using F3 = std::function<void(double, double, float)>;


	void SetUp()
	{
		p_void_return_function = void_return_function;
		p_int_return_function = int_return_function;
		
		std_void_return_function = void_return_function;
		std_int_return_function = int_return_function;
	}
	 
	void                      (*p_void_return_function)();
	int                       (*p_int_return_function)();
	std::function<void()>       std_void_return_function;
	std::function<int()>        std_int_return_function;

	VoidFunctorClass            void_functor;
	const VoidFunctorClassConst const_void_functor;

	IntFunctorClass			    int_functor;
	const IntFunctorClassConst  const_int_functor;

	::F1 functor_1;
	::F2 functor_2;
	::F3 functor_3;

	const ::F1Const const_functor_1;
	const ::F2Const const_functor_2;
	const ::F3Const const_functor_3;
};

auto void_lambda = [] {};

auto int_lambda = []() -> int { return 0; };


inline void f1(int) {}

inline void f2(int, char) {}

inline void f3(const std::string &, int, int) {}

auto l1 = [](int) {};

auto l2 = [](std::string, std::vector<bool>) {};

auto l3 = [](char, char, char) {};


TEST_F(TestFunction, TestResult)
{
	using metaxxa::Function;
	using testing::StaticAssertTypeEq;

	StaticAssertTypeEq<Function<decltype(void_return_function)>              ::Result, void>();
	StaticAssertTypeEq<Function<decltype(p_void_return_function)>            ::Result, void>();
	StaticAssertTypeEq<Function<decltype(std_void_return_function)>          ::Result, void>();
	StaticAssertTypeEq<Function<decltype(void_lambda)>                       ::Result, void>();
	StaticAssertTypeEq<Function<decltype(&VoidFunctorClass::operator())>     ::Result, void>();
	StaticAssertTypeEq<Function<decltype(&VoidFunctorClassConst::operator())>::Result, void>();
	StaticAssertTypeEq<Function<decltype(void_functor)>                      ::Result, void>();
	StaticAssertTypeEq<Function<decltype(const_void_functor)>                ::Result, void>();

	
	StaticAssertTypeEq<Function<decltype(int_return_function)>              ::Result, int>();
	StaticAssertTypeEq<Function<decltype(p_int_return_function)>            ::Result, int>();
	StaticAssertTypeEq<Function<decltype(std_int_return_function)>          ::Result, int>();
	StaticAssertTypeEq<Function<decltype(int_lambda)>                       ::Result, int>();
	StaticAssertTypeEq<Function<decltype(&IntFunctorClass::operator())>     ::Result, int>();
	StaticAssertTypeEq<Function<decltype(&IntFunctorClassConst::operator())>::Result, int>();
	StaticAssertTypeEq<Function<decltype(int_functor)>                      ::Result, int>();
	StaticAssertTypeEq<Function<decltype(const_int_functor)>                ::Result, int>();
}

TEST_F(TestFunction, TestArgumentCount)
{
	using namespace metaxxa;
	using testing::StaticAssertTypeEq;
	using std::tuple_size;

	EXPECT_EQ(Function<decltype(void_return_function)>              ::argument_count(), 0);
	EXPECT_EQ(Function<decltype(p_void_return_function)>            ::argument_count(), 0);
	EXPECT_EQ(Function<decltype(std_void_return_function)>          ::argument_count(), 0);
	EXPECT_EQ(Function<decltype(void_lambda)>                       ::argument_count(), 0);
	EXPECT_EQ(Function<decltype(&VoidFunctorClass::operator())>     ::argument_count(), 0);
	EXPECT_EQ(Function<decltype(&VoidFunctorClassConst::operator())>::argument_count(), 0);
	EXPECT_EQ(Function<decltype(void_functor)>						::argument_count(), 0);
	EXPECT_EQ(Function<decltype(const_void_functor)>			    ::argument_count(), 0);

	EXPECT_EQ(Function<decltype(f1)>                  ::argument_count(), 1);
	EXPECT_EQ(Function<TestFunction::P1>              ::argument_count(), 1);
	EXPECT_EQ(Function<TestFunction::F1>              ::argument_count(), 1);
	EXPECT_EQ(Function<decltype(l1)>                  ::argument_count(), 1);
	EXPECT_EQ(Function<decltype(&F1::operator())>     ::argument_count(), 1);
	EXPECT_EQ(Function<decltype(&F1Const::operator())>::argument_count(), 1);
	EXPECT_EQ(Function<decltype(functor_1)>           ::argument_count(), 1);
	EXPECT_EQ(Function<decltype(const_functor_1)>     ::argument_count(), 1);

	EXPECT_EQ(Function<decltype(f2)>                  ::argument_count(), 2);
	EXPECT_EQ(Function<TestFunction::P2>              ::argument_count(), 2);
	EXPECT_EQ(Function<TestFunction::F2>              ::argument_count(), 2);
	EXPECT_EQ(Function<decltype(l2)>                  ::argument_count(), 2);
	EXPECT_EQ(Function<decltype(&F2::operator())>     ::argument_count(), 2);
	EXPECT_EQ(Function<decltype(&F2Const::operator())>::argument_count(), 2);
	EXPECT_EQ(Function<decltype(functor_2)>           ::argument_count(), 2);
	EXPECT_EQ(Function<decltype(const_functor_2)>     ::argument_count(), 2);

	EXPECT_EQ(Function<decltype(f3)>                  ::argument_count(), 3);
	EXPECT_EQ(Function<TestFunction::P3>              ::argument_count(), 3);
	EXPECT_EQ(Function<TestFunction::F3>              ::argument_count(), 3);
	EXPECT_EQ(Function<decltype(l3)>                  ::argument_count(), 3);
	EXPECT_EQ(Function<decltype(&F3::operator())>     ::argument_count(), 3);
	EXPECT_EQ(Function<decltype(&F3Const::operator())>::argument_count(), 3);
	EXPECT_EQ(Function<decltype(functor_3)>           ::argument_count(), 3);
	EXPECT_EQ(Function<decltype(const_functor_3)>     ::argument_count(), 3);
}

TEST_F(TestFunction, TestArgumentTypes)
{
	using namespace metaxxa;
	using testing::StaticAssertTypeEq;

	StaticAssertTypeEq<typename Function<decltype(f1)>                  ::template Argument<0>, int>              ();
	StaticAssertTypeEq<typename Function<TestFunction::P1>              ::template Argument<0>, double>           ();
	StaticAssertTypeEq<typename Function<TestFunction::F1>              ::template Argument<0>, std::vector<bool>>();
	StaticAssertTypeEq<typename Function<decltype(l1)>                  ::template Argument<0>, int>              ();
	StaticAssertTypeEq<typename Function<decltype(&::F1::operator())>   ::template Argument<0>, double>           ();
	StaticAssertTypeEq<typename Function<decltype(&F1Const::operator())>::template Argument<0>, void(*)(int)>     ();
	StaticAssertTypeEq<typename Function<decltype(functor_1)>           ::template Argument<0>, double>           ();
	StaticAssertTypeEq<typename Function<decltype(const_functor_1)>     ::template Argument<0>, void(*)(int)>     ();

	StaticAssertTypeEq<typename Function<decltype(f2)>					::template Argument<0>, int>                                  ();
	StaticAssertTypeEq<typename Function<TestFunction::P2>				::template Argument<0>, int>                                  ();
	StaticAssertTypeEq<typename Function<TestFunction::F2>				::template Argument<0>, std::initializer_list<float>>         ();
	StaticAssertTypeEq<typename Function<decltype(l2)>                  ::template Argument<0>, std::string>                          ();
	StaticAssertTypeEq<typename Function<decltype(&::F2::operator())>   ::template Argument<0>, const std::pair<std::string, float> &>();
	StaticAssertTypeEq<typename Function<decltype(&F2Const::operator())>::template Argument<0>, int&&>                                ();
	StaticAssertTypeEq<typename Function<decltype(functor_2)>			::template Argument<0>, const std::pair<std::string, float> &>();
	StaticAssertTypeEq<typename Function<decltype(const_functor_2)>		::template Argument<0>, int&&>                                ();
	
	
	StaticAssertTypeEq<typename Function<decltype(f2)>					::template Argument<1>, char>               ();
	StaticAssertTypeEq<typename Function<TestFunction::P2>				::template Argument<1>, char>               ();
	StaticAssertTypeEq<typename Function<TestFunction::F2>				::template Argument<1>, const std::string &>();
	StaticAssertTypeEq<typename Function<decltype(l2)>                  ::template Argument<1>, std::vector<bool>>  ();
	StaticAssertTypeEq<typename Function<decltype(&::F2::operator())>   ::template Argument<1>, const char *>       ();
	StaticAssertTypeEq<typename Function<decltype(&F2Const::operator())>::template Argument<1>, char>               ();
	StaticAssertTypeEq<typename Function<decltype(functor_2)>			::template Argument<1>, const char *>       ();
	StaticAssertTypeEq<typename Function<decltype(const_functor_2)>		::template Argument<1>, char>               ();

	StaticAssertTypeEq<typename Function<decltype(f3)>					::template Argument<0>, const std::string &> ();
	StaticAssertTypeEq<typename Function<TestFunction::P3>				::template Argument<0>, float>				 ();
	StaticAssertTypeEq<typename Function<TestFunction::F3>				::template Argument<0>, double>				 ();
	StaticAssertTypeEq<typename Function<decltype(l3)>					::template Argument<0>, char>				 ();
	StaticAssertTypeEq<typename Function<decltype(&::F3::operator())>   ::template Argument<0>, char>				 ();
	StaticAssertTypeEq<typename Function<decltype(&F3Const::operator())>::template Argument<0>, float>				 ();
	StaticAssertTypeEq<typename Function<decltype(functor_3)>			::template Argument<0>, char>				 ();
	StaticAssertTypeEq<typename Function<decltype(const_functor_3)>		::template Argument<0>, float>				 ();
	
	StaticAssertTypeEq<typename Function<decltype(f3)>					::template Argument<1>, int>                ();
	StaticAssertTypeEq<typename Function<TestFunction::P3>				::template Argument<1>, const std::string &>();
	StaticAssertTypeEq<typename Function<TestFunction::F3>				::template Argument<1>, double>             ();
	StaticAssertTypeEq<typename Function<decltype(l3)>					::template Argument<1>, char>               ();
	StaticAssertTypeEq<typename Function<decltype(&::F3::operator())>   ::template Argument<1>, double>             ();
	StaticAssertTypeEq<typename Function<decltype(&F3Const::operator())>::template Argument<1>, float>              ();
	StaticAssertTypeEq<typename Function<decltype(functor_3)>			::template Argument<1>, double>             ();
	StaticAssertTypeEq<typename Function<decltype(const_functor_3)>		::template Argument<1>, float>              ();
	
	StaticAssertTypeEq<typename Function<decltype(f3)>					::template Argument<2>, int>   ();
	StaticAssertTypeEq<typename Function<TestFunction::P3>				::template Argument<2>, int*>  ();
	StaticAssertTypeEq<typename Function<TestFunction::F3>				::template Argument<2>, float> ();
	StaticAssertTypeEq<typename Function<decltype(l3)>					::template Argument<2>, char>  ();
	StaticAssertTypeEq<typename Function<decltype(&::F3::operator())>   ::template Argument<2>, int>   ();
	StaticAssertTypeEq<typename Function<decltype(&F3Const::operator())>::template Argument<2>, double>();
	StaticAssertTypeEq<typename Function<decltype(functor_3)>			::template Argument<2>, int>   ();
	StaticAssertTypeEq<typename Function<decltype(const_functor_3)>		::template Argument<2>, double>();
}

TEST_F(TestFunction, TestArgumentsTuple)
{
	using namespace metaxxa;
	using testing::StaticAssertTypeEq;

	StaticAssertTypeEq<Function<decltype(f1)>				   ::Arguments, Tuple<int>>();
	StaticAssertTypeEq<Function<TestFunction::P1>              ::Arguments, Tuple<double>>();
	StaticAssertTypeEq<Function<TestFunction::F1>              ::Arguments, Tuple<std::vector<bool>>>();
	StaticAssertTypeEq<Function<decltype(l1)>                  ::Arguments, Tuple<int>>();
	StaticAssertTypeEq<Function<decltype(&::F1::operator())>   ::Arguments, Tuple<double>>();
	StaticAssertTypeEq<Function<decltype(&F1Const::operator())>::Arguments, Tuple<void(*)(int)>>();
	StaticAssertTypeEq<Function<decltype(functor_1)>           ::Arguments, Tuple<double>>();
	StaticAssertTypeEq<Function<decltype(const_functor_1)>     ::Arguments, Tuple<void(*)(int)>>();

	StaticAssertTypeEq<Function<decltype(f2)>					::Arguments, Tuple<int, char>>();
	StaticAssertTypeEq<Function<TestFunction::P2>				::Arguments, Tuple<int, char>>();
	StaticAssertTypeEq<Function<TestFunction::F2>				::Arguments, Tuple<std::initializer_list<float>, const std::string &>>();
	StaticAssertTypeEq<Function<decltype(l2)>                   ::Arguments, Tuple<std::string, std::vector<bool>>>();
	StaticAssertTypeEq<Function<decltype(&::F2::operator())>    ::Arguments, Tuple<const std::pair<std::string, float> &, const char *>>();
	StaticAssertTypeEq<Function<decltype(&F2Const::operator())> ::Arguments, Tuple<int&&, char>>();
	StaticAssertTypeEq<Function<decltype(functor_2)>			::Arguments, Tuple<const std::pair<std::string, float> &, const char *>>();
	StaticAssertTypeEq<Function<decltype(const_functor_2)>		::Arguments, Tuple<int&&, char>>();
}

TEST_F(TestFunction, TestIsConst)
{
	using namespace metaxxa;
	using testing::StaticAssertTypeEq;

	EXPECT_FALSE(Function<decltype(functor_3)>::is_const());
	EXPECT_TRUE(Function<decltype(const_functor_3)>::is_const());
}

#endif // METAXXA_TESTFUNCTION_H