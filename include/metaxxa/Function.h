#ifndef METAXXA_FUNCTION_H
#define METAXXA_FUNCTION_H

#include <functional>

#include "Tuple.h"
#include "Type.h"
#include "detail/FunctionTag.h"

namespace metaxxa
{
	namespace detail
	{
		template <typename ArgumentType>
		struct ArgumentsSignatureBuilder
		{
			ArgumentsSignatureBuilder(std::string &result)
				: result(result)
			{}

			void operator()()
			{
				if (!result.empty())
					result += ", ";
				result += Type<ArgumentType>::name_with_modifiers();
			}

		private:
			std::string &result;
		};

		struct NonFunction
		{};

		template <typename T, template <typename> typename Function, bool HAS_CALL_OPERATOR = Type<T>::has_single_operator_call()>
		struct ResolveFunctionBase
		{};

		template <typename T, template <typename> typename Function>
		struct ResolveFunctionBase<T, Function, true>
		{
			using Base = Function<decltype(&T::operator())>;
		};

		template <typename T, template <typename> typename Function>
		struct ResolveFunctionBase<T, Function, false>
		{
			using Base = NonFunction;
		};
	}

	template<typename T>
	struct Function : detail::ResolveFunctionBase<T, Function>::Base
	{
	};


	template<typename ResultType, typename... FunctionArguments>
	struct Function<ResultType(FunctionArguments...)> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<FunctionArguments...>;

		template <size_t INDEX>
		using Argument = std::tuple_element_t<INDEX, typename Arguments::StdTuple>;

		static constexpr size_t argument_count() { return Arguments::size(); }

		static constexpr bool is_method() { return false; }

		static std::string get_signature()
		{
			std::string arguments;
			Arguments::template for_each_types<detail::ArgumentsSignatureBuilder>(arguments);

			return Type<Result>::name_with_modifiers() + " (" + arguments + ")";
		}

		static std::string signature()
		{
			return get_signature();
		}
	};


	template<typename ResultType, typename... FunctionArguments>
	struct Function<ResultType(*)(FunctionArguments...)> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<FunctionArguments...>;
		
		template <size_t INDEX>
		using Argument = std::tuple_element_t<INDEX, typename Arguments::StdTuple>;

		static constexpr size_t argument_count() { return Arguments::size(); }

		static constexpr bool is_method() { return false; }

		static std::string get_signature()
		{
			std::string arguments;
			Arguments::template for_each_types<detail::ArgumentsSignatureBuilder>(arguments);

			return Type<Result>::name_with_modifiers() + " (" + arguments + ")";
		}

		static std::string signature()
		{
			return get_signature();
		}

	};


	template<typename ResultType, typename... FunctionArguments>
	struct Function<std::function<ResultType(FunctionArguments...)>> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<FunctionArguments...>;
		
		template <size_t INDEX>
		using Argument = std::tuple_element_t<INDEX, typename Arguments::StdTuple>;

		static constexpr size_t argument_count() { return Arguments::size(); }

		static constexpr bool is_method() { return false; }

		static std::string get_signature()
		{
			std::string arguments;
			Arguments::template for_each_types<detail::ArgumentsSignatureBuilder>(arguments);

			return Type<Result>::name_with_modifiers() + " (" + arguments + ")";
		}

		static std::string signature()
		{
			return get_signature();
		}
	};


	template<typename SomeType, typename ResultType, typename... FunctionArguments>
	struct Function<ResultType(SomeType::*)(FunctionArguments...)> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<FunctionArguments...>;
		
		template <size_t INDEX>
		using Argument = std::tuple_element_t<INDEX, typename Arguments::StdTuple>;

		static constexpr size_t argument_count() { return Arguments::size(); }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return false; }

		static constexpr bool is_volatile() { return false; }

		static constexpr bool is_lvalue() { return true; }

		static constexpr bool is_rvalue() { return true; }

		static constexpr bool is_noexcept() { return false; }

		static std::string get_signature()
		{
			std::string arguments;
			Arguments::template for_each_types<detail::ArgumentsSignatureBuilder>(arguments);

			return Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " (" + arguments + ")";
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType, typename... FunctionArguments>
	struct Function<ResultType(SomeType::*)(FunctionArguments...) noexcept> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<FunctionArguments...>;
		
		template <size_t INDEX>
		using Argument = std::tuple_element_t<INDEX, typename Arguments::StdTuple>;

		static constexpr size_t argument_count() { return Arguments::size(); }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return false; }

		static constexpr bool is_volatile() { return false; }

		static constexpr bool is_lvalue() { return true; }

		static constexpr bool is_rvalue() { return true; }

		static constexpr bool is_noexcept() { return true; }

		static std::string get_signature()
		{
			std::string arguments;
			Arguments::template for_each_types<detail::ArgumentsSignatureBuilder>(arguments);

			return Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " (" + arguments + ") noexcept";
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType, typename... FunctionArguments>
	struct Function<ResultType(SomeType::*)(FunctionArguments...) &> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<FunctionArguments...>;
		
		template <size_t INDEX>
		using Argument = std::tuple_element_t<INDEX, typename Arguments::StdTuple>;

		static constexpr size_t argument_count() { return Arguments::size(); }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return false; }

		static constexpr bool is_volatile() { return false; }

		static constexpr bool is_lvalue() { return true; }

		static constexpr bool is_rvalue() { return false; }

		static constexpr bool is_noexcept() { return false; }

		static std::string get_signature()
		{
			std::string arguments;
			Arguments::template for_each_types<detail::ArgumentsSignatureBuilder>(arguments);

			return Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " (" + arguments + ") &";
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType, typename... FunctionArguments>
	struct Function<ResultType(SomeType::*)(FunctionArguments...) & noexcept> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<FunctionArguments...>;
		
		template <size_t INDEX>
		using Argument = std::tuple_element_t<INDEX, typename Arguments::StdTuple>;

		static constexpr size_t argument_count() { return Arguments::size(); }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return false; }

		static constexpr bool is_volatile() { return false; }

		static constexpr bool is_lvalue() { return true; }

		static constexpr bool is_rvalue() { return false; }

		static constexpr bool is_noexcept() { return true; }

		static std::string get_signature()
		{
			std::string arguments;
			Arguments::template for_each_types<detail::ArgumentsSignatureBuilder>(arguments);

			return Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " (" + arguments + ") & noexcept";
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType, typename... FunctionArguments>
	struct Function<ResultType(SomeType::*)(FunctionArguments...) &&> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<FunctionArguments...>;
		
		template <size_t INDEX>
		using Argument = std::tuple_element_t<INDEX, typename Arguments::StdTuple>;

		static constexpr size_t argument_count() { return Arguments::size(); }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return false; }

		static constexpr bool is_volatile() { return false; }

		static constexpr bool is_lvalue() { return false; }

		static constexpr bool is_rvalue() { return true; }

		static constexpr bool is_noexcept() { return false; }

		static std::string get_signature()
		{
			std::string arguments;
			Arguments::template for_each_types<detail::ArgumentsSignatureBuilder>(arguments);

			return Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " (" + arguments + ") &&";
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType, typename... FunctionArguments>
	struct Function<ResultType(SomeType::*)(FunctionArguments...) && noexcept> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<FunctionArguments...>;
		
		template <size_t INDEX>
		using Argument = std::tuple_element_t<INDEX, typename Arguments::StdTuple>;

		static constexpr size_t argument_count() { return Arguments::size(); }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return false; }

		static constexpr bool is_volatile() { return false; }

		static constexpr bool is_lvalue() { return false; }

		static constexpr bool is_rvalue() { return true; }

		static constexpr bool is_noexcept() { return true; }

		static std::string get_signature()
		{
			std::string arguments;
			Arguments::template for_each_types<detail::ArgumentsSignatureBuilder>(arguments);

			return Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " (" + arguments + ") && noexcept";
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType, typename... FunctionArguments>
	struct Function<ResultType(SomeType::*)(FunctionArguments...) const> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<FunctionArguments...>;
		
		template <size_t INDEX>
		using Argument = std::tuple_element_t<INDEX, typename Arguments::StdTuple>;

		static constexpr size_t argument_count() { return Arguments::size(); }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return true; }

		static constexpr bool is_volatile() { return false; }

		static constexpr bool is_lvalue() { return true; }

		static constexpr bool is_rvalue() { return true; }

		static constexpr bool is_noexcept() { return false; }

		static std::string get_signature()
		{
			std::string arguments;
			Arguments::template for_each_types<detail::ArgumentsSignatureBuilder>(arguments);

			return Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " (" + arguments + ") const";
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType, typename... FunctionArguments>
	struct Function<ResultType(SomeType::*)(FunctionArguments...) const noexcept> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<FunctionArguments...>;
		
		template <size_t INDEX>
		using Argument = std::tuple_element_t<INDEX, typename Arguments::StdTuple>;

		static constexpr size_t argument_count() { return Arguments::size(); }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return true; }

		static constexpr bool is_volatile() { return false; }

		static constexpr bool is_lvalue() { return true; }

		static constexpr bool is_rvalue() { return true; }

		static constexpr bool is_noexcept() { return true; }

		static std::string get_signature()
		{
			std::string arguments;
			Arguments::template for_each_types<detail::ArgumentsSignatureBuilder>(arguments);

			return Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " (" + arguments + ") const noexcept";
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType, typename... FunctionArguments>
	struct Function<ResultType(SomeType::*)(FunctionArguments...) const &> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<FunctionArguments...>;
		
		template <size_t INDEX>
		using Argument = std::tuple_element_t<INDEX, typename Arguments::StdTuple>;

		static constexpr size_t argument_count() { return Arguments::size(); }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return true; }

		static constexpr bool is_volatile() { return false; }

		static constexpr bool is_lvalue() { return true; }

		static constexpr bool is_rvalue() { return false; }

		static constexpr bool is_noexcept() { return false; }

		static std::string get_signature()
		{
			std::string arguments;
			Arguments::template for_each_types<detail::ArgumentsSignatureBuilder>(arguments);

			return Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " (" + arguments + ") const &";
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType, typename... FunctionArguments>
	struct Function<ResultType(SomeType::*)(FunctionArguments...) const & noexcept> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<FunctionArguments...>;
		
		template <size_t INDEX>
		using Argument = std::tuple_element_t<INDEX, typename Arguments::StdTuple>;

		static constexpr size_t argument_count() { return Arguments::size(); }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return true; }

		static constexpr bool is_volatile() { return false; }

		static constexpr bool is_lvalue() { return true; }

		static constexpr bool is_rvalue() { return false; }

		static constexpr bool is_noexcept() { return true; }

		static std::string get_signature()
		{
			std::string arguments;
			Arguments::template for_each_types<detail::ArgumentsSignatureBuilder>(arguments);

			return Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " (" + arguments + ") const & noexcept";
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType, typename... FunctionArguments>
	struct Function<ResultType(SomeType::*)(FunctionArguments...) const &&> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<FunctionArguments...>;
		
		template <size_t INDEX>
		using Argument = std::tuple_element_t<INDEX, typename Arguments::StdTuple>;

		static constexpr size_t argument_count() { return Arguments::size(); }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return true; }

		static constexpr bool is_volatile() { return false; }

		static constexpr bool is_lvalue() { return false; }

		static constexpr bool is_rvalue() { return true; }

		static constexpr bool is_noexcept() { return false; }

		static std::string get_signature()
		{
			std::string arguments;
			Arguments::template for_each_types<detail::ArgumentsSignatureBuilder>(arguments);

			return Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " (" + arguments + ") const &&";
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType, typename... FunctionArguments>
	struct Function<ResultType(SomeType::*)(FunctionArguments...) const && noexcept> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<FunctionArguments...>;
		
		template <size_t INDEX>
		using Argument = std::tuple_element_t<INDEX, typename Arguments::StdTuple>;

		static constexpr size_t argument_count() { return Arguments::size(); }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return true; }

		static constexpr bool is_volatile() { return false; }

		static constexpr bool is_lvalue() { return false; }

		static constexpr bool is_rvalue() { return true; }

		static constexpr bool is_noexcept() { return true; }

		static std::string get_signature()
		{
			std::string arguments;
			Arguments::template for_each_types<detail::ArgumentsSignatureBuilder>(arguments);

			return Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " (" + arguments + ") const && noexcept";
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType, typename... FunctionArguments>
	struct Function<ResultType(SomeType::*)(FunctionArguments...) volatile> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<FunctionArguments...>;
		
		template <size_t INDEX>
		using Argument = std::tuple_element_t<INDEX, typename Arguments::StdTuple>;

		static constexpr size_t argument_count() { return Arguments::size(); }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return false; }

		static constexpr bool is_volatile() { return true; }

		static constexpr bool is_lvalue() { return true; }

		static constexpr bool is_rvalue() { return true; }

		static constexpr bool is_noexcept() { return false; }

		static std::string get_signature()
		{
			std::string arguments;
			Arguments::template for_each_types<detail::ArgumentsSignatureBuilder>(arguments);

			return Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " (" + arguments + ") volatile";
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType, typename... FunctionArguments>
	struct Function<ResultType(SomeType::*)(FunctionArguments...) volatile noexcept> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<FunctionArguments...>;
		
		template <size_t INDEX>
		using Argument = std::tuple_element_t<INDEX, typename Arguments::StdTuple>;

		static constexpr size_t argument_count() { return Arguments::size(); }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return false; }

		static constexpr bool is_volatile() { return true; }

		static constexpr bool is_lvalue() { return true; }

		static constexpr bool is_rvalue() { return true; }

		static constexpr bool is_noexcept() { return true; }

		static std::string get_signature()
		{
			std::string arguments;
			Arguments::template for_each_types<detail::ArgumentsSignatureBuilder>(arguments);

			return Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " (" + arguments + ") volatile noexcept";
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType, typename... FunctionArguments>
	struct Function<ResultType(SomeType::*)(FunctionArguments...) volatile &> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<FunctionArguments...>;
		
		template <size_t INDEX>
		using Argument = std::tuple_element_t<INDEX, typename Arguments::StdTuple>;

		static constexpr size_t argument_count() { return Arguments::size(); }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return false; }

		static constexpr bool is_volatile() { return true; }

		static constexpr bool is_lvalue() { return true; }

		static constexpr bool is_rvalue() { return false; }

		static constexpr bool is_noexcept() { return false; }

		static std::string get_signature()
		{
			std::string arguments;
			Arguments::template for_each_types<detail::ArgumentsSignatureBuilder>(arguments);

			return Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " (" + arguments + ") volatile &";
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType, typename... FunctionArguments>
	struct Function<ResultType(SomeType::*)(FunctionArguments...) volatile & noexcept> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<FunctionArguments...>;
		
		template <size_t INDEX>
		using Argument = std::tuple_element_t<INDEX, typename Arguments::StdTuple>;

		static constexpr size_t argument_count() { return Arguments::size(); }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return false; }

		static constexpr bool is_volatile() { return true; }

		static constexpr bool is_lvalue() { return true; }

		static constexpr bool is_rvalue() { return false; }

		static constexpr bool is_noexcept() { return true; }

		static std::string get_signature()
		{
			std::string arguments;
			Arguments::template for_each_types<detail::ArgumentsSignatureBuilder>(arguments);

			return Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " (" + arguments + ") volatile & noexcept";
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType, typename... FunctionArguments>
	struct Function<ResultType(SomeType::*)(FunctionArguments...) volatile &&> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<FunctionArguments...>;
		
		template <size_t INDEX>
		using Argument = std::tuple_element_t<INDEX, typename Arguments::StdTuple>;

		static constexpr size_t argument_count() { return Arguments::size(); }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return false; }

		static constexpr bool is_volatile() { return true; }

		static constexpr bool is_lvalue() { return false; }

		static constexpr bool is_rvalue() { return true; }

		static constexpr bool is_noexcept() { return false; }

		static std::string get_signature()
		{
			std::string arguments;
			Arguments::template for_each_types<detail::ArgumentsSignatureBuilder>(arguments);

			return Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " (" + arguments + ") volatile &&";
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType, typename... FunctionArguments>
	struct Function<ResultType(SomeType::*)(FunctionArguments...) volatile && noexcept> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<FunctionArguments...>;
		
		template <size_t INDEX>
		using Argument = std::tuple_element_t<INDEX, typename Arguments::StdTuple>;

		static constexpr size_t argument_count() { return Arguments::size(); }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return false; }

		static constexpr bool is_volatile() { return true; }

		static constexpr bool is_lvalue() { return false; }

		static constexpr bool is_rvalue() { return true; }

		static constexpr bool is_noexcept() { return true; }

		static std::string get_signature()
		{
			std::string arguments;
			Arguments::template for_each_types<detail::ArgumentsSignatureBuilder>(arguments);

			return Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " (" + arguments + ") volatile && noexcept";
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType, typename... FunctionArguments>
	struct Function<ResultType(SomeType::*)(FunctionArguments...) const volatile> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<FunctionArguments...>;
		
		template <size_t INDEX>
		using Argument = std::tuple_element_t<INDEX, typename Arguments::StdTuple>;

		static constexpr size_t argument_count() { return Arguments::size(); }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return true; }

		static constexpr bool is_volatile() { return true; }

		static constexpr bool is_lvalue() { return true; }

		static constexpr bool is_rvalue() { return true; }

		static constexpr bool is_noexcept() { return false; }

		static std::string get_signature()
		{
			std::string arguments;
			Arguments::template for_each_types<detail::ArgumentsSignatureBuilder>(arguments);

			return Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " (" + arguments + ") const volatile";
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType, typename... FunctionArguments>
	struct Function<ResultType(SomeType::*)(FunctionArguments...) const volatile noexcept> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<FunctionArguments...>;
		
		template <size_t INDEX>
		using Argument = std::tuple_element_t<INDEX, typename Arguments::StdTuple>;

		static constexpr size_t argument_count() { return Arguments::size(); }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return true; }

		static constexpr bool is_volatile() { return true; }

		static constexpr bool is_lvalue() { return true; }

		static constexpr bool is_rvalue() { return true; }

		static constexpr bool is_noexcept() { return true; }

		static std::string get_signature()
		{
			std::string arguments;
			Arguments::template for_each_types<detail::ArgumentsSignatureBuilder>(arguments);

			return Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " (" + arguments + ") const volatile noexcept";
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType, typename... FunctionArguments>
	struct Function<ResultType(SomeType::*)(FunctionArguments...) const volatile &> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<FunctionArguments...>;
		
		template <size_t INDEX>
		using Argument = std::tuple_element_t<INDEX, typename Arguments::StdTuple>;

		static constexpr size_t argument_count() { return Arguments::size(); }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return true; }

		static constexpr bool is_volatile() { return true; }

		static constexpr bool is_lvalue() { return true; }

		static constexpr bool is_rvalue() { return false; }

		static constexpr bool is_noexcept() { return false; }

		static std::string get_signature()
		{
			std::string arguments;
			Arguments::template for_each_types<detail::ArgumentsSignatureBuilder>(arguments);

			return Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " (" + arguments + ") const volatile &";
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType, typename... FunctionArguments>
	struct Function<ResultType(SomeType::*)(FunctionArguments...) const volatile & noexcept> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<FunctionArguments...>;
		
		template <size_t INDEX>
		using Argument = std::tuple_element_t<INDEX, typename Arguments::StdTuple>;

		static constexpr size_t argument_count() { return Arguments::size(); }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return true; }

		static constexpr bool is_volatile() { return true; }

		static constexpr bool is_lvalue() { return true; }

		static constexpr bool is_rvalue() { return false; }

		static constexpr bool is_noexcept() { return true; }

		static std::string get_signature()
		{
			std::string arguments;
			Arguments::template for_each_types<detail::ArgumentsSignatureBuilder>(arguments);

			return Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " (" + arguments + ") const volatile & noexcept";
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType, typename... FunctionArguments>
	struct Function<ResultType(SomeType::*)(FunctionArguments...) const volatile &&> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<FunctionArguments...>;
		
		template <size_t INDEX>
		using Argument = std::tuple_element_t<INDEX, typename Arguments::StdTuple>;

		static constexpr size_t argument_count() { return Arguments::size(); }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return true; }

		static constexpr bool is_volatile() { return true; }

		static constexpr bool is_lvalue() { return false; }

		static constexpr bool is_rvalue() { return true; }

		static constexpr bool is_noexcept() { return false; }

		static std::string get_signature()
		{
			std::string arguments;
			Arguments::template for_each_types<detail::ArgumentsSignatureBuilder>(arguments);

			return Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " (" + arguments + ") const volatile &&";
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType, typename... FunctionArguments>
	struct Function<ResultType(SomeType::*)(FunctionArguments...) const volatile && noexcept> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<FunctionArguments...>;
		
		template <size_t INDEX>
		using Argument = std::tuple_element_t<INDEX, typename Arguments::StdTuple>;

		static constexpr size_t argument_count() { return Arguments::size(); }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return true; }

		static constexpr bool is_volatile() { return true; }

		static constexpr bool is_lvalue() { return false; }

		static constexpr bool is_rvalue() { return true; }

		static constexpr bool is_noexcept() { return true; }

		static std::string get_signature()
		{
			std::string arguments;
			Arguments::template for_each_types<detail::ArgumentsSignatureBuilder>(arguments);

			return Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " (" + arguments + ") const volatile && noexcept";
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	// Specializations for functions without arguments
	// {

	template<typename ResultType>
	struct Function<ResultType()> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<>;

		static constexpr size_t argument_count() { return 0; }

		static constexpr bool is_method() { return false; }

		static std::string get_signature()
		{
			std::string result = Type<Result>::name_with_modifiers() + " ()";

			return result;
		}

		static std::string signature()
		{
			return get_signature();
		}
	};


	template<typename ResultType>
	struct Function<ResultType(*)()> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<>;

		static constexpr size_t argument_count() { return 0; }

		static constexpr bool is_method() { return false; }

		static std::string get_signature()
		{
			std::string result = Type<Result>::name_with_modifiers() + " ()";

			return result;
		}

		static std::string signature()
		{
			return get_signature();
		}

	};


	template<typename ResultType>
	struct Function<std::function<ResultType()>> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<>;

		static constexpr size_t argument_count() { return 0; }

		static constexpr bool is_method() { return false; }

		static std::string get_signature()
		{
			std::string result = Type<Result>::name_with_modifiers() + " ()";

			return result;
		}

		static std::string signature()
		{
			return get_signature();
		}
	};


	template<typename SomeType, typename ResultType>
	struct Function<ResultType(SomeType::*)()> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<>;

		static constexpr size_t argument_count() { return 0; }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return false; }

		static constexpr bool is_volatile() { return false; }

		static constexpr bool is_lvalue() { return true; }

		static constexpr bool is_rvalue() { return true; }

		static constexpr bool is_noexcept() { return false; }

		static std::string get_signature()
		{
			std::string result = Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " ()";

			return result;
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType>
	struct Function<ResultType(SomeType::*)() noexcept> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<>;

		static constexpr size_t argument_count() { return 0; }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return false; }

		static constexpr bool is_volatile() { return false; }

		static constexpr bool is_lvalue() { return true; }

		static constexpr bool is_rvalue() { return true; }

		static constexpr bool is_noexcept() { return true; }

		static std::string get_signature()
		{
			std::string result = Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " () noexcept";

			return result;
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType>
	struct Function<ResultType(SomeType::*)() &> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<>;

		static constexpr size_t argument_count() { return 0; }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return false; }

		static constexpr bool is_volatile() { return false; }

		static constexpr bool is_lvalue() { return true; }

		static constexpr bool is_rvalue() { return false; }

		static constexpr bool is_noexcept() { return false; }

		static std::string get_signature()
		{
			std::string result = Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " () &";

			return result;
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType>
	struct Function<ResultType(SomeType::*)() & noexcept> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<>;

		static constexpr size_t argument_count() { return 0; }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return false; }

		static constexpr bool is_volatile() { return false; }

		static constexpr bool is_lvalue() { return true; }

		static constexpr bool is_rvalue() { return false; }

		static constexpr bool is_noexcept() { return true; }

		static std::string get_signature()
		{
			std::string result = Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " () & noexcept";

			return result;
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType>
	struct Function<ResultType(SomeType::*)() &&> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<>;

		static constexpr size_t argument_count() { return 0; }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return false; }

		static constexpr bool is_volatile() { return false; }

		static constexpr bool is_lvalue() { return false; }

		static constexpr bool is_rvalue() { return true; }

		static constexpr bool is_noexcept() { return false; }

		static std::string get_signature()
		{
			std::string result = Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " () &&";

			return result;
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType>
	struct Function<ResultType(SomeType::*)() && noexcept> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<>;

		static constexpr size_t argument_count() { return 0; }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return false; }

		static constexpr bool is_volatile() { return false; }

		static constexpr bool is_lvalue() { return false; }

		static constexpr bool is_rvalue() { return true; }

		static constexpr bool is_noexcept() { return true; }

		static std::string get_signature()
		{
			std::string result = Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " () && noexcept";

			return result;
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType>
	struct Function<ResultType(SomeType::*)() const> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<>;

		static constexpr size_t argument_count() { return 0; }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return true; }

		static constexpr bool is_volatile() { return false; }

		static constexpr bool is_lvalue() { return true; }

		static constexpr bool is_rvalue() { return true; }

		static constexpr bool is_noexcept() { return false; }

		static std::string get_signature()
		{
			std::string result = Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " () const";

			return result;
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType>
	struct Function<ResultType(SomeType::*)() const noexcept> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<>;

		static constexpr size_t argument_count() { return 0; }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return true; }

		static constexpr bool is_volatile() { return false; }

		static constexpr bool is_lvalue() { return true; }

		static constexpr bool is_rvalue() { return true; }

		static constexpr bool is_noexcept() { return true; }

		static std::string get_signature()
		{
			std::string result = Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " () const noexcept";

			return result;
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType>
	struct Function<ResultType(SomeType::*)() const &> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<>;

		static constexpr size_t argument_count() { return 0; }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return true; }

		static constexpr bool is_volatile() { return false; }

		static constexpr bool is_lvalue() { return true; }

		static constexpr bool is_rvalue() { return false; }

		static constexpr bool is_noexcept() { return false; }

		static std::string get_signature()
		{
			std::string result = Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " () const &";

			return result;
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType>
	struct Function<ResultType(SomeType::*)() const & noexcept> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<>;

		static constexpr size_t argument_count() { return 0; }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return true; }

		static constexpr bool is_volatile() { return false; }

		static constexpr bool is_lvalue() { return true; }

		static constexpr bool is_rvalue() { return false; }

		static constexpr bool is_noexcept() { return true; }

		static std::string get_signature()
		{
			std::string result = Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " () const & noexcept";

			return result;
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType>
	struct Function<ResultType(SomeType::*)() const &&> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<>;

		static constexpr size_t argument_count() { return 0; }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return true; }

		static constexpr bool is_volatile() { return false; }

		static constexpr bool is_lvalue() { return false; }

		static constexpr bool is_rvalue() { return true; }

		static constexpr bool is_noexcept() { return false; }

		static std::string get_signature()
		{
			std::string result = Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " () const &&";

			return result;
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType>
	struct Function<ResultType(SomeType::*)() const && noexcept> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<>;

		static constexpr size_t argument_count() { return 0; }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return true; }

		static constexpr bool is_volatile() { return false; }

		static constexpr bool is_lvalue() { return false; }

		static constexpr bool is_rvalue() { return true; }

		static constexpr bool is_noexcept() { return true; }

		static std::string get_signature()
		{
			std::string result = Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " () const && noexcept";

			return result;
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType>
	struct Function<ResultType(SomeType::*)() const volatile> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<>;

		static constexpr size_t argument_count() { return 0; }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return true; }

		static constexpr bool is_volatile() { return true; }

		static constexpr bool is_lvalue() { return true; }

		static constexpr bool is_rvalue() { return true; }

		static constexpr bool is_noexcept() { return false; }

		static std::string get_signature()
		{
			std::string result = Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " () const volatile";

			return result;
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType>
	struct Function<ResultType(SomeType::*)() const volatile noexcept> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<>;

		static constexpr size_t argument_count() { return 0; }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return true; }

		static constexpr bool is_volatile() { return true; }

		static constexpr bool is_lvalue() { return true; }

		static constexpr bool is_rvalue() { return true; }

		static constexpr bool is_noexcept() { return true; }

		static std::string get_signature()
		{
			std::string result = Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " () const volatile noexcept";

			return result;
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType>
	struct Function<ResultType(SomeType::*)() const volatile &> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<>;

		static constexpr size_t argument_count() { return 0; }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return true; }

		static constexpr bool is_volatile() { return true; }

		static constexpr bool is_lvalue() { return true; }

		static constexpr bool is_rvalue() { return false; }

		static constexpr bool is_noexcept() { return false; }

		static std::string get_signature()
		{
			std::string result = Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " () const volatile &";

			return result;
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType>
	struct Function<ResultType(SomeType::*)() const volatile & noexcept> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<>;

		static constexpr size_t argument_count() { return 0; }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return true; }

		static constexpr bool is_volatile() { return true; }

		static constexpr bool is_lvalue() { return true; }

		static constexpr bool is_rvalue() { return false; }

		static constexpr bool is_noexcept() { return true; }

		static std::string get_signature()
		{
			std::string result = Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " () const volatile & noexcept";

			return result;
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType>
	struct Function<ResultType(SomeType::*)() const volatile &&> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<>;

		static constexpr size_t argument_count() { return 0; }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return true; }

		static constexpr bool is_volatile() { return true; }

		static constexpr bool is_lvalue() { return false; }

		static constexpr bool is_rvalue() { return true; }

		static constexpr bool is_noexcept() { return false; }

		static std::string get_signature()
		{
			std::string result = Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " () const volatile &&";

			return result;
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	template<typename SomeType, typename ResultType>
	struct Function<ResultType(SomeType::*)() const volatile && noexcept> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<>;

		static constexpr size_t argument_count() { return 0; }

		static constexpr bool is_method() { return true; }

		static constexpr bool is_const() { return true; }

		static constexpr bool is_volatile() { return true; }

		static constexpr bool is_lvalue() { return false; }

		static constexpr bool is_rvalue() { return true; }

		static constexpr bool is_noexcept() { return true; }

		static std::string get_signature()
		{
			std::string result = Type<Result>::name_with_modifiers() + " (" + Type<SomeType>::name() + "::*)" + " () const volatile && noexcept";

			return result;
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	// }

	template <typename FirstCallable, typename SecondCallable>
	constexpr bool is_same_signature()
	{
		return Type<typename Function<FirstCallable>::Arguments>() == Type<typename Function<SecondCallable>::Arguments>()
			&& Type<typename Function<FirstCallable>::Result>() == Type<typename Function<SecondCallable>::Result>();
	}

	template <typename FirstCallable, typename SecondCallable>
	constexpr bool is_same_modifiers()
	{
		using F1 = Function<FirstCallable>;
		using F2 = Function<SecondCallable>;

		if constexpr(F1::is_method() && F2::is_method())
			return 
				(F1::is_const() == F2::is_const())
				&& (F1::is_volatile() == F2::is_volatile())
				&& (F1::is_lvalue() == F2::is_lvalue())
				&& (F1::is_rvalue() == F2::is_rvalue())
				&& (F1::is_noexcept() == F2::is_noexcept());
		else 
			return true;
	}

	template <typename FirstCallable, typename SecondCallable>
	constexpr bool is_same_signature(Function<FirstCallable>, Function<SecondCallable>)
	{
		return is_same_signature<FirstCallable, SecondCallable>();
	}

	template <typename FirstCallable, typename SecondCallable>
	constexpr bool is_same_modifiers(Function<FirstCallable>, Function<SecondCallable>)
	{
		return is_same_modifiers<FirstCallable, SecondCallable>();
	}

	template <typename FirstCallable, typename SecondCallable>
	constexpr auto operator==(Function<FirstCallable>, Function<SecondCallable>)
	{
		return is_same_signature<FirstCallable, SecondCallable>() && is_same_modifiers<FirstCallable, SecondCallable>();
	}

	template <typename FirstCallable, typename SecondCallable>
	constexpr auto operator!=(Function<FirstCallable> first, Function<SecondCallable> second)
	{
		return !(first == second);
	}
}

#endif //METAXXA_FUNCTION_H