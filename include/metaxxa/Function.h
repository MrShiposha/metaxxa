#ifndef METAXXA_FUNCTION_H
#define METAXXA_FUNCTION_H

#include <functional>

#include "Tuple.h"
#include "FunctionTag.h"
#include "NonFunctionTag.h"
#include "detail/FunctionBaseResolver.h"

#define DECLARE_FUNCTION_WITH_ARGUMENTS(Signature) 										                   							 \
	template<typename ResultType, typename... FunctionArguments>           				                   							 \
	struct Function<Signature> : metaxxa::FunctionTag							    			                   					 \
	{																					                   							 \
		template <size_t INDEX> 														                   							 \
		using Argument = std::tuple_element_t<INDEX, std::tuple<FunctionArguments...>>;                    							 \
																						                   							 \
		using Result = ResultType;														                   							 \
		using Arguments = Tuple<FunctionArguments...>;									                   							 \
																						                   							 \
		template <typename SomeType>												           	           				    		 \
		using ToMethod = typename metaxxa::detail::CallableToMethod<SomeType, Signature, std::tuple_size_v<Arguments> == 0>::Method; \
																																	 \
		template <typename SomeType>																								 \
		using ToWrappedMethod = Function<ToMethod<SomeType>>;																		 \
																																	 \
		template <template <typename...> typename TemplateType>																		 \
		using MoveArgumentsTo = metaxxa::detail::MoveTemplateTypes<TemplateType, Arguments>;										 \
																						                   							 \
		static constexpr size_t argument_count();										                   							 \
																						                   							 \
		static constexpr bool is_method();												                   							 \
																						                   							 \
		static std::string get_signature();												                   							 \
																						                   							 \
		static std::string signature();													                   							 \
	};

#define DECLARE_FUNCTION_NO_ARGUMENTS(Signature)     																				 \
	template<typename ResultType>				     																				 \
	struct Function<Signature> : metaxxa::FunctionTag 		 																		 \
	{												 																				 \
		using Result = ResultType;					 																				 \
		using Arguments = Tuple<>;				     																				 \
													 																	    		 \
		template <typename SomeType>												           	           				    		 \
		using ToMethod = typename metaxxa::detail::CallableToMethod<SomeType, Signature, std::tuple_size_v<Arguments> == 0>::Method; \
																																	 \
		template <typename SomeType>																								 \
		using ToWrappedMethod = Function<ToMethod<SomeType>>;																		 \
																																	 \
		template <template <typename...> typename TemplateType>																		 \
		using MoveArgumentsTo = metaxxa::detail::MoveTemplateTypes<TemplateType, Arguments>;										 \
												     																				 \
		static constexpr size_t argument_count();	 																				 \
													 																				 \
		static constexpr bool is_method();			 																				 \
													 																				 \
		static std::string get_signature();			 																				 \
													 																				 \
		static std::string signature();				 																				 \
	};

#define DECLARE_METHOD_WITH_ARGUMENTS(Signature) \
	template<typename SomeType, typename ResultType, typename... FunctionArguments>													 \
	struct Function<Signature> : metaxxa::FunctionTag																				 \
	{																																 \
		using OuterType = SomeType;																									 \
																																	 \
		template <size_t INDEX>																										 \
		using Argument = std::tuple_element_t<INDEX, std::tuple<FunctionArguments...>>; 											 \
																																	 \
		using Result = ResultType;																									 \
		using Arguments = Tuple<FunctionArguments...>;																				 \
																																	 \
		template <typename RHSType>												           	           				        		 \
		using ToMethod = typename metaxxa::detail::CallableToMethod<RHSType, Signature, std::tuple_size_v<Arguments> == 0>::Method;  \
																																	 \
		template <typename RHSType>																						    		 \
		using ToWrappedMethod = Function<ToMethod<RHSType>>;																		 \
																																	 \
		template <template <typename...> typename TemplateType>																		 \
		using MoveArgumentsTo = metaxxa::detail::MoveTemplateTypes<TemplateType, Arguments>;										 \
																																	 \
		static constexpr size_t argument_count();																					 \
																																	 \
		static constexpr bool is_method();																							 \
																																	 \
		static constexpr bool is_const();																							 \
																																	 \
		static constexpr bool is_volatile();																						 \
																																	 \
		static constexpr bool is_lvalue();																							 \
																																	 \
		static constexpr bool is_rvalue();																							 \
																																	 \
		static constexpr bool is_noexcept();																						 \
																																	 \
		static std::string get_signature();																							 \
																																	 \
		static std::string signature();																								 \
	};

#define DECLARE_METHOD_NO_ARGUMENTS(Signature) \
	template<typename SomeType, typename ResultType> 																				 \
	struct Function<Signature> : metaxxa::FunctionTag 		 																		 \
	{												 																				 \
		using OuterType = SomeType;					 																				 \
												     																				 \
		using Result = ResultType;					 																				 \
		using Arguments = Tuple<>;					 																				 \
													 																				 \
		template <typename RHSType>												           	           				        		 \
		using ToMethod = typename metaxxa::detail::CallableToMethod<RHSType, Signature, std::tuple_size_v<Arguments> == 0>::Method;  \
																																	 \
		template <typename RHSType>																						    		 \
		using ToWrappedMethod = Function<ToMethod<RHSType>>;																		 \
																																	 \
		template <template <typename...> typename TemplateType>																		 \
		using MoveArgumentsTo = metaxxa::detail::MoveTemplateTypes<TemplateType, Arguments>;										 \
													 																				 \
		static constexpr size_t argument_count();	 																				 \
													 																				 \
		static constexpr bool is_method();			 																				 \
													 																				 \
		static constexpr bool is_const();			 																				 \
													 																				 \
		static constexpr bool is_volatile();		 																				 \
													 																				 \
		static constexpr bool is_lvalue();			 																				 \
													 																				 \
		static constexpr bool is_rvalue();			 																				 \
													 																				 \
		static constexpr bool is_noexcept();		 																				 \
													 																				 \
		static std::string get_signature();			 																				 \
													 																				 \
		static std::string signature();				 																				 \
	};

namespace metaxxa
{
	namespace detail
	{
		template <typename SomeType, typename Callable, bool IS_ENOUGH, typename... Arguments>
		struct CallableToMethod;
	}
}

template<typename T>
struct Function : metaxxa::detail::FunctionBaseResolver<T, Function>::Base
{
};

DECLARE_FUNCTION_WITH_ARGUMENTS(ResultType(FunctionArguments...))
DECLARE_FUNCTION_WITH_ARGUMENTS(ResultType(*)(FunctionArguments...))
DECLARE_FUNCTION_WITH_ARGUMENTS(std::function<ResultType(FunctionArguments...)>)

DECLARE_FUNCTION_NO_ARGUMENTS(ResultType())
DECLARE_FUNCTION_NO_ARGUMENTS(ResultType(*)())
DECLARE_FUNCTION_NO_ARGUMENTS(std::function<ResultType()>)


DECLARE_METHOD_WITH_ARGUMENTS(ResultType(SomeType::*)(FunctionArguments...));
DECLARE_METHOD_WITH_ARGUMENTS(ResultType(SomeType::*)(FunctionArguments...) noexcept);
DECLARE_METHOD_WITH_ARGUMENTS(ResultType(SomeType::*)(FunctionArguments...) &);
DECLARE_METHOD_WITH_ARGUMENTS(ResultType(SomeType::*)(FunctionArguments...) & noexcept);
DECLARE_METHOD_WITH_ARGUMENTS(ResultType(SomeType::*)(FunctionArguments...) &&);
DECLARE_METHOD_WITH_ARGUMENTS(ResultType(SomeType::*)(FunctionArguments...) && noexcept);

DECLARE_METHOD_WITH_ARGUMENTS(ResultType(SomeType::*)(FunctionArguments...) const);
DECLARE_METHOD_WITH_ARGUMENTS(ResultType(SomeType::*)(FunctionArguments...) const noexcept);
DECLARE_METHOD_WITH_ARGUMENTS(ResultType(SomeType::*)(FunctionArguments...) const  &);
DECLARE_METHOD_WITH_ARGUMENTS(ResultType(SomeType::*)(FunctionArguments...) const  & noexcept);
DECLARE_METHOD_WITH_ARGUMENTS(ResultType(SomeType::*)(FunctionArguments...) const  &&);
DECLARE_METHOD_WITH_ARGUMENTS(ResultType(SomeType::*)(FunctionArguments...) const  && noexcept);

DECLARE_METHOD_WITH_ARGUMENTS(ResultType(SomeType::*)(FunctionArguments...) volatile);
DECLARE_METHOD_WITH_ARGUMENTS(ResultType(SomeType::*)(FunctionArguments...) volatile noexcept);
DECLARE_METHOD_WITH_ARGUMENTS(ResultType(SomeType::*)(FunctionArguments...) volatile  &);
DECLARE_METHOD_WITH_ARGUMENTS(ResultType(SomeType::*)(FunctionArguments...) volatile  & noexcept);
DECLARE_METHOD_WITH_ARGUMENTS(ResultType(SomeType::*)(FunctionArguments...) volatile  &&);
DECLARE_METHOD_WITH_ARGUMENTS(ResultType(SomeType::*)(FunctionArguments...) volatile  && noexcept);

DECLARE_METHOD_WITH_ARGUMENTS(ResultType(SomeType::*)(FunctionArguments...) const volatile);
DECLARE_METHOD_WITH_ARGUMENTS(ResultType(SomeType::*)(FunctionArguments...) const volatile noexcept);
DECLARE_METHOD_WITH_ARGUMENTS(ResultType(SomeType::*)(FunctionArguments...) const volatile  &);
DECLARE_METHOD_WITH_ARGUMENTS(ResultType(SomeType::*)(FunctionArguments...) const volatile  & noexcept);
DECLARE_METHOD_WITH_ARGUMENTS(ResultType(SomeType::*)(FunctionArguments...) const volatile  &&);
DECLARE_METHOD_WITH_ARGUMENTS(ResultType(SomeType::*)(FunctionArguments...) const volatile  && noexcept);


DECLARE_METHOD_NO_ARGUMENTS(ResultType(SomeType::*)());
DECLARE_METHOD_NO_ARGUMENTS(ResultType(SomeType::*)() noexcept);
DECLARE_METHOD_NO_ARGUMENTS(ResultType(SomeType::*)() &);
DECLARE_METHOD_NO_ARGUMENTS(ResultType(SomeType::*)() & noexcept);
DECLARE_METHOD_NO_ARGUMENTS(ResultType(SomeType::*)() &&);
DECLARE_METHOD_NO_ARGUMENTS(ResultType(SomeType::*)() && noexcept);

DECLARE_METHOD_NO_ARGUMENTS(ResultType(SomeType::*)() const);
DECLARE_METHOD_NO_ARGUMENTS(ResultType(SomeType::*)() const noexcept);
DECLARE_METHOD_NO_ARGUMENTS(ResultType(SomeType::*)() const  &);
DECLARE_METHOD_NO_ARGUMENTS(ResultType(SomeType::*)() const  & noexcept);
DECLARE_METHOD_NO_ARGUMENTS(ResultType(SomeType::*)() const  &&);
DECLARE_METHOD_NO_ARGUMENTS(ResultType(SomeType::*)() const  && noexcept);

DECLARE_METHOD_NO_ARGUMENTS(ResultType(SomeType::*)() volatile);
DECLARE_METHOD_NO_ARGUMENTS(ResultType(SomeType::*)() volatile noexcept);
DECLARE_METHOD_NO_ARGUMENTS(ResultType(SomeType::*)() volatile  &);
DECLARE_METHOD_NO_ARGUMENTS(ResultType(SomeType::*)() volatile  & noexcept);
DECLARE_METHOD_NO_ARGUMENTS(ResultType(SomeType::*)() volatile  &&);
DECLARE_METHOD_NO_ARGUMENTS(ResultType(SomeType::*)() volatile  && noexcept);

DECLARE_METHOD_NO_ARGUMENTS(ResultType(SomeType::*)() const volatile);
DECLARE_METHOD_NO_ARGUMENTS(ResultType(SomeType::*)() const volatile noexcept);
DECLARE_METHOD_NO_ARGUMENTS(ResultType(SomeType::*)() const volatile  &);
DECLARE_METHOD_NO_ARGUMENTS(ResultType(SomeType::*)() const volatile  & noexcept);
DECLARE_METHOD_NO_ARGUMENTS(ResultType(SomeType::*)() const volatile  &&);
DECLARE_METHOD_NO_ARGUMENTS(ResultType(SomeType::*)() const volatile  && noexcept);

template <typename FirstCallable, typename SecondCallable>
constexpr bool is_same_signature();

template <typename FirstCallable, typename SecondCallable>
constexpr bool is_same_modifiers();

template <typename FirstCallable, typename SecondCallable>
constexpr bool is_same_signature(Function<FirstCallable>, Function<SecondCallable>);

template <typename FirstCallable, typename SecondCallable>
constexpr bool is_same_modifiers(Function<FirstCallable>, Function<SecondCallable>);

template <typename FirstCallable, typename SecondCallable>
constexpr auto operator==(Function<FirstCallable>, Function<SecondCallable>);

template <typename FirstCallable, typename SecondCallable>
constexpr auto operator!=(Function<FirstCallable> first, Function<SecondCallable> second);

#undef DECLARE_FUNCTION_WITH_ARGUMENTS
#undef DECLARE_FUNCTION_NO_ARGUMENTS
#undef DECLARE_METHOD_WITH_ARGUMENTS
#undef DECLARE_METHOD_NO_ARGUMENTS

#endif //METAXXA_FUNCTION_H