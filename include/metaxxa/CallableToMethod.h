#ifndef METAXXA_CALLABLETOMETHOD_H
#define METAXXA_CALLABLETOMETHOD_H

#include "Function.h"

#include "detail/MethodToMethod.h"

namespace metaxxa
{
	namespace detail
	{
		template <typename SomeType, typename Callable, bool IS_METHOD, typename... Arguments>
		struct CallableOrMethodResolver
		{};
		
		template <typename SomeType, typename Callable, typename... Arguments>
		struct CallableOrMethodResolver<SomeType, Callable, true, Arguments...>
		{
			using Type = typename MethodToMethod
			<
				SomeType, 
				Callable, 
				Function<Callable>::is_const(),
				Function<Callable>::is_volatile(),
				Function<Callable>::is_lvalue(),
				Function<Callable>::is_rvalue(),
				Function<Callable>::is_noexcept(),
				Arguments...
			>::Method;
		};

		template <typename SomeType, typename Callable, typename... Arguments>
		struct CallableOrMethodResolver<SomeType, Callable, false, Arguments...>
		{
			using MethodResult = typename Function<Callable>::Result;

			using Type = MethodResult(SomeType::*)(Arguments...);
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
			using Method = typename CallableOrMethodResolver
			<
				SomeType, 
				Callable, 
				Function<Callable>::is_method(), 
				Arguments...
			>::Type;
		};
	}

	template <typename SomeType, typename Callable>
	using CallableToMethod = typename detail::CallableToMethod<SomeType, Callable, Function<Callable>::argument_count() == 0>::Method;
}

#endif // METAXXA_CALLABLETOMETHOD_H