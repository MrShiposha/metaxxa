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

		static constexpr bool is_const() { return false; }

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
	struct Function<ResultType(SomeType::*)(FunctionArguments...) const> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<FunctionArguments...>;
		
		template <size_t INDEX>
		using Argument = std::tuple_element_t<INDEX, typename Arguments::StdTuple>;

		static constexpr size_t argument_count() { return Arguments::size(); }

		static constexpr bool is_const() { return true; }

		static std::string get_signature()
		{
			std::string arguments;
			Arguments::template for_each_types<detail::ArgumentsSignatureBuilder>(arguments);

			return Type<Result>::name_with_modifiers() + " (" + arguments + ") const";
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

		static constexpr bool is_const() { return false; }

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
	struct Function<ResultType(SomeType::*)() const> : detail::FunctionTag
	{
		using Result = ResultType;
		using Arguments = Tuple<>;

		static constexpr size_t argument_count() { return 0; }

		static constexpr bool is_const() { return true; }

		static std::string get_signature()
		{
			std::string result = Type<Result>::name_with_modifiers() + " () const";

			return result;
		}

		static std::string signature()
		{
			return get_signature();
		}
	};

	// }

	template <typename FirstCallable, typename SecondCallable>
	constexpr auto operator==(Function<FirstCallable> &&, Function<SecondCallable> &&)
	{
		return Type<typename Function<FirstCallable>::Arguments>() == Type<typename Function<SecondCallable>::Arguments>()
			&& Type<typename Function<FirstCallable>::Result>() == Type<typename Function<SecondCallable>::Result>();
	}

	template <typename FirstCallable, typename SecondCallable>
	constexpr auto operator!=(Function<FirstCallable> &&first, Function<SecondCallable> &&second)
	{
		return !(first == second);
	}
}

#endif //METAXXA_FUNCTION_H