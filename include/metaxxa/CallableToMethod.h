#ifndef METAXXA_CALLABLETOMETHOD_H
#define METAXXA_CALLABLETOMETHOD_H

#include "Function.h"

namespace metaxxa
{
	namespace detail
	{
		template <typename SomeType, typename Callable, bool IS_CALLABLE_METHOD, typename... Arguments>
		struct MethodResolver
		{};

		template <typename SomeType, typename Callable, bool IS_CONST_METHOD, typename... Arguments>
		struct ConstMethodResolver
		{};

		template <typename SomeType, typename Callable, typename... Arguments>
		struct ConstMethodResolver<SomeType, Callable, true, Arguments...>
		{
			using MethodResult = typename Function<Callable>::Result;

			using Method = MethodResult(SomeType::*)(Arguments...) const;
		};

		template <typename SomeType, typename Callable, typename... Arguments>
		struct ConstMethodResolver<SomeType, Callable, false, Arguments...>
		{
			using MethodResult = typename Function<Callable>::Result;

			using Method = MethodResult(SomeType::*)(Arguments...);
		};


		template <typename SomeType, typename Callable, typename... Arguments>
		struct MethodResolver<SomeType, Callable, true, Arguments...>
		{
			using Method = typename ConstMethodResolver<SomeType, Callable, Function<Callable>::is_const(), Arguments...>::Method;
		};

		template <typename SomeType, typename Callable, typename... Arguments>
		struct MethodResolver<SomeType, Callable, false, Arguments...>
		{
			using MethodResult = typename Function<Callable>::Result;

			using Method = MethodResult(SomeType::*)(Arguments...);
		};

		template <typename SomeType, typename Callable, bool IS_ENOUGH, typename... Arguments>
		struct CallableToMethod 
			: CallableToMethod
			<
				SomeType, 
				Callable, 
				sizeof...(Arguments) + 1 >= Function<Callable>::argument_count(),
				Arguments..., typename Function<Callable>::template Argument<sizeof...(Arguments)>
			>
			{
			};

		template <typename SomeType, typename Callable, typename... Arguments>
		struct CallableToMethod<SomeType, Callable, true, Arguments...>
		{
			using Method = typename MethodResolver
			<
				SomeType, 
				Callable, 
				Function<Callable>::is_method(), 
				Arguments...
			>::Method;
		};
	}

	template <typename SomeType, typename Callable>
	using CallableToMethod = typename detail::CallableToMethod<SomeType, Callable, Function<Callable>::argument_count() == 0>::Method;
}

#endif // METAXXA_CALLABLETOMETHOD_H