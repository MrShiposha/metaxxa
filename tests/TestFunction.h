#ifndef METAXXA_TESTFUNCTION_H
#define METAXXA_TESTFUNCTION_H

#include "TestMetaxxa.h"

inline void void_return_function() {}

inline int int_return_function() { return 0; }

auto void_lambda = [] {};

auto int_lambda = []() -> int { return 0; };


inline void f1(int) {}

inline void f2(int, char) {}

inline void f3(const std::string &, int, int) {}

auto l1 = [](int) {};

auto l2 = [](std::string, std::vector<bool>) {};

auto l3 = [](char, char, char) {};


inline void feq_1(int, char) {}
inline void feq_1s(int, char) {}
inline void feq_2(int) {}

struct EqTest
{
	void feq_1c(int, char) const {}
	void feq_1cs(int, char) const {}

	void feq_1(int, char) {}
	void feq_1s(int, char) {}

	void feq_2c(int) const {}
	void feq_2cs(int) const {}

	void feq_2(int) {}
	void feq_2s(int) {}
};


struct TestFunction : TestMetaxxa
{
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

	struct F1Struct
	{
		void operator()(double)
		{}
	};

	struct F2Struct
	{
		void operator()(const std::pair<std::string, float> &, const char *)
		{}
	};

	struct F3Struct
	{
		void operator()(char, double, int)
		{}
	};

	struct F1ConstStruct
	{
		void operator()(void(*)(int)) const
		{}
	};

	struct F2ConstStruct
	{
		void operator()(int&&, char) const
		{}
	};

	struct F3ConstStruct
	{
		void operator()(float, float, double) const
		{}
	};

	using P1 = void(*)(double);
	using P2 = void(*)(int, char);
	using P3 = void(*)(float, const std::string &, int *);

	using F1 = std::function<void(std::vector<bool>)>;
	using F2 = std::function<void(std::initializer_list<float>, const std::string &)>;
	using F3 = std::function<void(double, double, float)>;

	TestFunction()
	: p_void_return_function(void_return_function), p_int_return_function(int_return_function),
	std_void_return_function(void_return_function), std_int_return_function(int_return_function),
	const_functor_1(),
	const_functor_2(),
	const_functor_3()
	{}
	 
	virtual bool test() override
	{
		bool result = true;
		result = result && test_result();
		result = result && test_argument_count();
		result = result && test_arguments_types();
		result = result && test_arguments_tuple();
		result = result && test_is_const();
		result = result && test_signature();
		result = result && test_equality();

		return result;
	}

	bool test_result()
	{
		using metaxxa::Function;

		static_assert(std::is_same_v<Function<decltype(void_return_function)>              ::Result, void>, "class Function: result test failed");
		static_assert(std::is_same_v<Function<decltype(p_void_return_function)>            ::Result, void>, "class Function: result test failed");
		static_assert(std::is_same_v<Function<decltype(std_void_return_function)>          ::Result, void>, "class Function: result test failed");
		static_assert(std::is_same_v<Function<decltype(void_lambda)>                       ::Result, void>, "class Function: result test failed");
		static_assert(std::is_same_v<Function<decltype(&VoidFunctorClass::operator())>     ::Result, void>, "class Function: result test failed");
		static_assert(std::is_same_v<Function<decltype(&VoidFunctorClassConst::operator())>::Result, void>, "class Function: result test failed");
		static_assert(std::is_same_v<Function<decltype(void_functor)>                      ::Result, void>, "class Function: result test failed");
		static_assert(std::is_same_v<Function<decltype(const_void_functor)>                ::Result, void>, "class Function: result test failed");

		
		static_assert(std::is_same_v<Function<decltype(int_return_function)>              ::Result, int>, "class Function: result test failed");
		static_assert(std::is_same_v<Function<decltype(p_int_return_function)>            ::Result, int>, "class Function: result test failed");
		static_assert(std::is_same_v<Function<decltype(std_int_return_function)>          ::Result, int>, "class Function: result test failed");
		static_assert(std::is_same_v<Function<decltype(int_lambda)>                       ::Result, int>, "class Function: result test failed");
		static_assert(std::is_same_v<Function<decltype(&IntFunctorClass::operator())>     ::Result, int>, "class Function: result test failed");
		static_assert(std::is_same_v<Function<decltype(&IntFunctorClassConst::operator())>::Result, int>, "class Function: result test failed");
		static_assert(std::is_same_v<Function<decltype(int_functor)>                      ::Result, int>, "class Function: result test failed");
		static_assert(std::is_same_v<Function<decltype(const_int_functor)>                ::Result, int>, "class Function: result test failed");
		return true;
	}

	bool test_argument_count()
	{
		using namespace metaxxa;
		using std::tuple_size;

		static_assert(Function<decltype(void_return_function)>              ::argument_count() == 0, "class Function: argument count test failed");
		static_assert(Function<decltype(p_void_return_function)>            ::argument_count() == 0, "class Function: argument count test failed");
		static_assert(Function<decltype(std_void_return_function)>          ::argument_count() == 0, "class Function: argument count test failed");
		static_assert(Function<decltype(void_lambda)>                       ::argument_count() == 0, "class Function: argument count test failed");
		static_assert(Function<decltype(&VoidFunctorClass::operator())>     ::argument_count() == 0, "class Function: argument count test failed");
		static_assert(Function<decltype(&VoidFunctorClassConst::operator())>::argument_count() == 0, "class Function: argument count test failed");
		static_assert(Function<decltype(void_functor)>						::argument_count() == 0, "class Function: argument count test failed");
		static_assert(Function<decltype(const_void_functor)>			    ::argument_count() == 0, "class Function: argument count test failed");

		static_assert(Function<decltype(f1)>                        ::argument_count() == 1, "class Function: argument count test failed");
		static_assert(Function<TestFunction::P1>                    ::argument_count() == 1, "class Function: argument count test failed");
		static_assert(Function<TestFunction::F1>                    ::argument_count() == 1, "class Function: argument count test failed");
		static_assert(Function<decltype(l1)>                        ::argument_count() == 1, "class Function: argument count test failed");
		static_assert(Function<decltype(&F1Struct::operator())>     ::argument_count() == 1, "class Function: argument count test failed");
		static_assert(Function<decltype(&F1ConstStruct::operator())>::argument_count() == 1, "class Function: argument count test failed");
		static_assert(Function<decltype(functor_1)>                 ::argument_count() == 1, "class Function: argument count test failed");
		static_assert(Function<decltype(const_functor_1)>           ::argument_count() == 1, "class Function: argument count test failed");

		static_assert(Function<decltype(f2)>                        ::argument_count() == 2, "class Function: argument count test failed");
		static_assert(Function<TestFunction::P2>                    ::argument_count() == 2, "class Function: argument count test failed");
		static_assert(Function<TestFunction::F2>                    ::argument_count() == 2, "class Function: argument count test failed");
		static_assert(Function<decltype(l2)>                        ::argument_count() == 2, "class Function: argument count test failed");
		static_assert(Function<decltype(&F2Struct::operator())>     ::argument_count() == 2, "class Function: argument count test failed");
		static_assert(Function<decltype(&F2ConstStruct::operator())>::argument_count() == 2, "class Function: argument count test failed");
		static_assert(Function<decltype(functor_2)>                 ::argument_count() == 2, "class Function: argument count test failed");
		static_assert(Function<decltype(const_functor_2)>           ::argument_count() == 2, "class Function: argument count test failed");

		static_assert(Function<decltype(f3)>                        ::argument_count() == 3, "class Function: argument count test failed");
		static_assert(Function<TestFunction::P3>                    ::argument_count() == 3, "class Function: argument count test failed");
		static_assert(Function<TestFunction::F3>                    ::argument_count() == 3, "class Function: argument count test failed");
		static_assert(Function<decltype(l3)>                        ::argument_count() == 3, "class Function: argument count test failed");
		static_assert(Function<decltype(&F3Struct::operator())>     ::argument_count() == 3, "class Function: argument count test failed");
		static_assert(Function<decltype(&F3ConstStruct::operator())>::argument_count() == 3, "class Function: argument count test failed");
		static_assert(Function<decltype(functor_3)>                 ::argument_count() == 3, "class Function: argument count test failed");
		static_assert(Function<decltype(const_functor_3)>           ::argument_count() == 3, "class Function: argument count test failed");
		return true;
	}

	bool test_arguments_types()
	{
		using namespace metaxxa;

		static_assert(std::is_same_v<typename Function<decltype(f1)>                        ::template Argument<0>, int>,               "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<TestFunction::P1>                    ::template Argument<0>, double>,            "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<TestFunction::F1>                    ::template Argument<0>, std::vector<bool>>, "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<decltype(l1)>                        ::template Argument<0>, int>,               "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<decltype(&F1Struct::operator())>     ::template Argument<0>, double>,            "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<decltype(&F1ConstStruct::operator())>::template Argument<0>, void(*)(int)>,      "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<decltype(functor_1)>                 ::template Argument<0>, double>,            "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<decltype(const_functor_1)>           ::template Argument<0>, void(*)(int)>,      "class Function: arguments types test failed");

		static_assert(std::is_same_v<typename Function<decltype(f2)>					    ::template Argument<0>, int>,                                   "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<TestFunction::P2>				    ::template Argument<0>, int>,                                   "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<TestFunction::F2>				    ::template Argument<0>, std::initializer_list<float>>,          "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<decltype(l2)>                        ::template Argument<0>, std::string>,                           "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<decltype(&F2Struct::operator())>     ::template Argument<0>, const std::pair<std::string, float> &>, "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<decltype(&F2ConstStruct::operator())>::template Argument<0>, int&&>,                                 "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<decltype(functor_2)>			        ::template Argument<0>, const std::pair<std::string, float> &>, "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<decltype(const_functor_2)>		    ::template Argument<0>, int&&>,                                 "class Function: arguments types test failed");
		
		
		static_assert(std::is_same_v<typename Function<decltype(f2)>					    ::template Argument<1>, char>,                "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<TestFunction::P2>				    ::template Argument<1>, char>,                "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<TestFunction::F2>				    ::template Argument<1>, const std::string &>, "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<decltype(l2)>                        ::template Argument<1>, std::vector<bool>>,   "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<decltype(&F2Struct::operator())>     ::template Argument<1>, const char *>,        "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<decltype(&F2ConstStruct::operator())>::template Argument<1>, char>,                "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<decltype(functor_2)>			        ::template Argument<1>, const char *>,        "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<decltype(const_functor_2)>		    ::template Argument<1>, char>,                "class Function: arguments types test failed");

		static_assert(std::is_same_v<typename Function<decltype(f3)>					    ::template Argument<0>, const std::string &>, "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<TestFunction::P3>				    ::template Argument<0>, float>,               "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<TestFunction::F3>				    ::template Argument<0>, double>,              "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<decltype(l3)>					    ::template Argument<0>, char>,                "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<decltype(&F3Struct::operator())>     ::template Argument<0>, char>,                "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<decltype(&F3ConstStruct::operator())>::template Argument<0>, float>,               "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<decltype(functor_3)>			        ::template Argument<0>, char>,                "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<decltype(const_functor_3)>		    ::template Argument<0>, float>,               "class Function: arguments types test failed");
		
		static_assert(std::is_same_v<typename Function<decltype(f3)>					    ::template Argument<1>, int>,                 "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<TestFunction::P3>				    ::template Argument<1>, const std::string &>, "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<TestFunction::F3>				    ::template Argument<1>, double>,              "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<decltype(l3)>					    ::template Argument<1>, char>,                "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<decltype(&F3Struct::operator())>     ::template Argument<1>, double>,              "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<decltype(&F3ConstStruct::operator())>::template Argument<1>, float>,               "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<decltype(functor_3)>			        ::template Argument<1>, double>,              "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<decltype(const_functor_3)>		    ::template Argument<1>, float>,               "class Function: arguments types test failed");
		
		static_assert(std::is_same_v<typename Function<decltype(f3)>					    ::template Argument<2>, int>,    "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<TestFunction::P3>				    ::template Argument<2>, int*>,   "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<TestFunction::F3>				    ::template Argument<2>, float>,  "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<decltype(l3)>					    ::template Argument<2>, char>,   "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<decltype(&F3Struct::operator())>     ::template Argument<2>, int>,    "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<decltype(&F3ConstStruct::operator())>::template Argument<2>, double>, "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<decltype(functor_3)>			        ::template Argument<2>, int>,    "class Function: arguments types test failed");
		static_assert(std::is_same_v<typename Function<decltype(const_functor_3)>		    ::template Argument<2>, double>, "class Function: arguments types test failed");
		return true;
	}

	bool test_arguments_tuple()
	{
		using namespace metaxxa;
		
		static_assert(std::is_same_v<Function<decltype(f1)>				           ::Arguments, Tuple<int>>,               "class Function: arguments tuple test failed");
		static_assert(std::is_same_v<Function<TestFunction::P1>                    ::Arguments, Tuple<double>>,            "class Function: arguments tuple test failed");
		static_assert(std::is_same_v<Function<TestFunction::F1>                    ::Arguments, Tuple<std::vector<bool>>>, "class Function: arguments tuple test failed");
		static_assert(std::is_same_v<Function<decltype(l1)>                        ::Arguments, Tuple<int>>,               "class Function: arguments tuple test failed");
		static_assert(std::is_same_v<Function<decltype(&F1Struct::operator())>     ::Arguments, Tuple<double>>,            "class Function: arguments tuple test failed");
		static_assert(std::is_same_v<Function<decltype(&F1ConstStruct::operator())>::Arguments, Tuple<void(*)(int)>>,      "class Function: arguments tuple test failed");
		static_assert(std::is_same_v<Function<decltype(functor_1)>                 ::Arguments, Tuple<double>>,            "class Function: arguments tuple test failed");
		static_assert(std::is_same_v<Function<decltype(const_functor_1)>           ::Arguments, Tuple<void(*)(int)>>,      "class Function: arguments tuple test failed");

		static_assert(std::is_same_v<Function<decltype(f2)>					       ::Arguments, Tuple<int, char>>,                                           "class Function: arguments tuple test failed");
		static_assert(std::is_same_v<Function<TestFunction::P2>				       ::Arguments, Tuple<int, char>>,                                           "class Function: arguments tuple test failed");
		static_assert(std::is_same_v<Function<TestFunction::F2>				       ::Arguments, Tuple<std::initializer_list<float>, const std::string &>>,   "class Function: arguments tuple test failed");
		static_assert(std::is_same_v<Function<decltype(l2)>                        ::Arguments, Tuple<std::string, std::vector<bool>>>,                      "class Function: arguments tuple test failed");
		static_assert(std::is_same_v<Function<decltype(&F2Struct::operator())>     ::Arguments, Tuple<const std::pair<std::string, float> &, const char *>>, "class Function: arguments tuple test failed");
		static_assert(std::is_same_v<Function<decltype(&F2ConstStruct::operator())>::Arguments, Tuple<int&&, char>>,                                         "class Function: arguments tuple test failed");
		static_assert(std::is_same_v<Function<decltype(functor_2)>			       ::Arguments, Tuple<const std::pair<std::string, float> &, const char *>>, "class Function: arguments tuple test failed");
		static_assert(std::is_same_v<Function<decltype(const_functor_2)>	       ::Arguments, Tuple<int&&, char>>,                                         "class Function: arguments tuple test failed");

		return true;
	}

	bool test_is_const()
	{
		using namespace metaxxa;

		static_assert(!Function<decltype(functor_3)>::is_const(), "class Function: \"is const\" test failed");
		static_assert(Function<decltype(const_functor_3)>::is_const(), "class Function: \"is const\" test failed");

		return true;
	}

	bool test_signature()
	{
		using namespace metaxxa;
		using namespace std::string_literals;

		TEST(Function<decltype(f1)>::signature() == "void (int)"s,                        "class Function: signature test failed");
		TEST(Function<TestFunction::P1>::signature() == "void (double)"s,                    "class Function: signature test failed");
		
		TEST
		(
			Function<TestFunction::F1>::signature().find("void ") == 0, 
			"class Function: signature test failed"
		);

		TEST
		(
			Function<TestFunction::F1>::signature().find("std::") != std::string::npos, 
			"class Function: signature test failed"
		);

		TEST
		(
			Function<TestFunction::F1>::signature().find("vector") != std::string::npos, 
			"class Function: signature test failed"
		);
		
		
		TEST(Function<decltype(l1)>::signature().find("void ") != std::string::npos,        "class Function: signature test failed");
		TEST(Function<decltype(l1)>::signature().find(" (int) const") != std::string::npos, "class Function: signature test failed");

		TEST(Function<decltype(&F1Struct::operator())>::signature().find("void (") != std::string::npos, "class Function: signature test failed");
		TEST(Function<decltype(&F1Struct::operator())>::signature().find("TestFunction::F1Struct::*) (double)") != std::string::npos, "class Function: signature test failed");
		
		TEST(Function<decltype(&F1ConstStruct::operator())>::signature().find("void (") != std::string::npos, "class Function: signature test failed");
		TEST(Function<decltype(&F1ConstStruct::operator())>::signature().find("TestFunction::F1ConstStruct::*) (void (") != std::string::npos, "class Function: signature test failed");
		TEST(Function<decltype(&F1ConstStruct::operator())>::signature().find("*)(int)) const") != std::string::npos, "class Function: signature test failed");
		
		TEST(Function<decltype(functor_1)>::signature().find("void (") != std::string::npos, "class Function: signature test failed");
		TEST(Function<decltype(functor_1)>::signature().find("TestFunction::F1Struct::*) (double)") != std::string::npos, "class Function: signature test failed");
		
		TEST(Function<decltype(const_functor_1)>::signature().find("void (") != std::string::npos, "class Function: signature test failed");
		TEST(Function<decltype(const_functor_1)>::signature().find("TestFunction::F1ConstStruct::*) (void (") != std::string::npos, "class Function: signature test failed");

		TEST(Function<decltype(const_functor_1)>::signature().find("*)(int)) const") != std::string::npos, "class Function: signature test failed");
		
		TEST(Function<decltype(const_functor_2)>::signature().find("void (") != std::string::npos, "class Function: signature test failed");
		TEST(Function<decltype(const_functor_2)>::signature().find("TestFunction::F2ConstStruct::*) (int") != std::string::npos, "class Function: signature test failed");
		TEST(Function<decltype(const_functor_2)>::signature().find("&&") != std::string::npos, "class Function: signature test failed");
		TEST(Function<decltype(const_functor_2)>::signature().find(", char) const") != std::string::npos, "class Function: signature test failed");		
		
		return true;
	}

	bool test_equality()
	{
		using namespace metaxxa;

		bool same_sig = is_same_signature<decltype(feq_1), decltype(feq_1s)>();
		TEST(same_sig, "class Function: equality test failed");
		TEST(Function<decltype(feq_1)>() == Function<decltype(feq_1s)>(), "class Function: equality test failed");

		same_sig = is_same_signature<decltype(feq_1), decltype(feq_2)>();
		TEST(!same_sig, "class Function: equality test failed");
		TEST(Function<decltype(feq_1)>() != Function<decltype(feq_2)>(), "class Function: equality test failed");
		

		same_sig = is_same_signature<decltype(&EqTest::feq_1c), decltype(feq_1)>();
		TEST(same_sig, "class Function: equality test failed");
		TEST(Function<decltype(&EqTest::feq_1c)>() == Function<decltype(feq_1)>(), "class Function: equality test failed");

		same_sig = is_same_signature<decltype(&EqTest::feq_1), decltype(feq_1)>();
		TEST(same_sig, "class Function: equality test failed");
		TEST(Function<decltype(&EqTest::feq_1)>() == Function<decltype(feq_1)>(), "class Function: equality test failed");

		same_sig = is_same_signature<decltype(&EqTest::feq_2c), decltype(feq_1)>();
		TEST(!same_sig, "class Function: equality test failed");
		TEST(Function<decltype(&EqTest::feq_2c)>() != Function<decltype(feq_1)>(), "class Function: equality test failed");

		same_sig = is_same_signature<decltype(&EqTest::feq_2), decltype(feq_1)>();
		TEST(!same_sig, "class Function: equality test failed");
		TEST(Function<decltype(&EqTest::feq_2)>() != Function<decltype(feq_1)>(), "class Function: equality test failed");


		same_sig = is_same_signature<decltype(feq_1), decltype(&EqTest::feq_1c)>();
		TEST(same_sig, "class Function: equality test failed");
		TEST(Function<decltype(feq_1)>() == Function<decltype(&EqTest::feq_1c)>(), "class Function: equality test failed");

		same_sig = is_same_signature<decltype(feq_1), decltype(&EqTest::feq_1)>();
		TEST(same_sig, "class Function: equality test failed");
		TEST(Function<decltype(feq_1)>() == Function<decltype(&EqTest::feq_1)>(), "class Function: equality test failed");

		same_sig = is_same_signature<decltype(feq_1), decltype(&EqTest::feq_2c)>();
		TEST(!same_sig, "class Function: equality test failed");
		TEST(Function<decltype(feq_1)>() != Function<decltype(&EqTest::feq_2c)>(), "class Function: equality test failed");

		same_sig = is_same_signature<decltype(feq_1), decltype(&EqTest::feq_2)>();
		TEST(!same_sig, "class Function: equality test failed");
		TEST(Function<decltype(feq_1)>() != Function<decltype(&EqTest::feq_2)>(), "class Function: equality test failed");


		same_sig = is_same_signature<decltype(&EqTest::feq_1c), decltype(&EqTest::feq_1cs)>();
		TEST(same_sig, "class Function: equality test failed");
		TEST(Function<decltype(&EqTest::feq_1c)>() == Function<decltype(&EqTest::feq_1cs)>(), "class Function: equality test failed");

		same_sig = is_same_signature<decltype(&EqTest::feq_1), decltype(&EqTest::feq_1s)>();
		TEST(same_sig, "class Function: equality test failed");
		TEST(Function<decltype(&EqTest::feq_1)>() == Function<decltype(&EqTest::feq_1s)>(), "class Function: equality test failed");


		same_sig = is_same_signature<decltype(&EqTest::feq_1c), decltype(&EqTest::feq_1)>();
		TEST(same_sig, "class Function: equality test failed");
		TEST(Function<decltype(&EqTest::feq_1c)>() != Function<decltype(&EqTest::feq_1)>(), "class Function: equality test failed");

		same_sig = is_same_signature<decltype(&EqTest::feq_1), decltype(&EqTest::feq_1c)>();
		TEST(same_sig, "class Function: equality test failed");
		TEST(Function<decltype(&EqTest::feq_1)>() != Function<decltype(&EqTest::feq_1c)>(), "class Function: equality test failed");

		
		same_sig = is_same_signature<decltype(&EqTest::feq_1c), decltype(&EqTest::feq_2c)>();
		TEST(!same_sig, "class Function: equality test failed");
		TEST(Function<decltype(&EqTest::feq_1c)>() != Function<decltype(&EqTest::feq_2c)>(), "class Function: equality test failed");

		same_sig = is_same_signature<decltype(&EqTest::feq_1), decltype(&EqTest::feq_2)>();
		TEST(!same_sig, "class Function: equality test failed");
		TEST(Function<decltype(&EqTest::feq_1)>() != Function<decltype(&EqTest::feq_2)>(), "class Function: equality test failed");


		same_sig = is_same_signature<decltype(&EqTest::feq_1c), decltype(&EqTest::feq_2)>();
		TEST(!same_sig, "class Function: equality test failed");
		TEST(Function<decltype(&EqTest::feq_1c)>() != Function<decltype(&EqTest::feq_2)>(), "class Function: equality test failed");

		same_sig = is_same_signature<decltype(&EqTest::feq_1), decltype(&EqTest::feq_2c)>();
		TEST(!same_sig, "class Function: equality test failed");
		TEST(Function<decltype(&EqTest::feq_1)>() != Function<decltype(&EqTest::feq_2c)>(), "class Function: equality test failed");

		return true;
	}

	void                      (*p_void_return_function)();
	int                       (*p_int_return_function)();
	std::function<void()>       std_void_return_function;
	std::function<int()>        std_int_return_function;

	VoidFunctorClass            void_functor;
	const VoidFunctorClassConst const_void_functor;

	IntFunctorClass			    int_functor;
	const IntFunctorClassConst  const_int_functor;

	F1Struct functor_1;
	F2Struct functor_2;
	F3Struct functor_3;

	const F1ConstStruct const_functor_1;
	const F2ConstStruct const_functor_2;
	const F3ConstStruct const_functor_3;
};

#endif // METAXXA_TESTFUNCTION_H