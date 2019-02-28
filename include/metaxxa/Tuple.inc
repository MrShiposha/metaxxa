#ifndef METAXXA_TUPLE_INC
#define METAXXA_TUPLE_INC

#include "Tuple.h"

#include "detail/Optional.h"

#include "SkipFirstOfStdTuple.h"
#include "ForEachOfStdTuple.h"
#include "EveryOfStdTuple.h"
#include "IsSameOfStdTuple.h"
#include "MaxOfStdTuple.h"
#include "FirstOfStdTuple.h"
#include "LastOfStdTuple.h"
#include "MapOfStdTuple.h"
#include "SumOfStdTuple.h"
#include "ContainsOfStdTuple.h"
#include "IsConvertsToTypesOfStdTuple.h"
#include "FindOfStdTuple.h"
#include "ToStringOfStdTuple.h"
#include "ExecuteFunctionsOfStdTuple.h"
#include "CallFunctionOfStdTuple.h"
#include "FilterOfStdTuple.h"
#include "WrapOfStdTuple.h"
#include "DistinctOfStdTuple.h"
#include "detail/MoveTemplateTypes.h"

namespace metaxxa
{
    template <typename... Arguments>
    Tuple<Arguments...>::Tuple(const Arguments&... arguments)
			: std_tuple(arguments...)
    {}

    template <typename... Arguments>
    template <typename... OtherArguments>
    Tuple<Arguments...>::Tuple(const Tuple<OtherArguments...> &other)
        : std_tuple(other.std_tuple)
    {}

    template <typename... Arguments>
    Tuple<Arguments...>::Tuple(const StdTuple &tuple)
        : std_tuple(tuple)
    {}

    template <typename... Arguments>
    template <size_t INDEX>
    auto &Tuple<Arguments...>::get() const
    {
        return std::get<INDEX>(std_tuple);
    }

    template <typename... Arguments>
    template <size_t INDEX>
    auto &Tuple<Arguments...>::get()
    {
        return std::get<INDEX>(std_tuple);
    }

    template <typename... Arguments>
    constexpr size_t Tuple<Arguments...>::get_size()
    {
        return std::tuple_size<StdTuple>::value;
    }

    template <typename... Arguments>
    constexpr size_t Tuple<Arguments...>::size()
    {
        return get_size();
    }
    
    template <typename... Arguments>
    constexpr bool Tuple<Arguments...>::is_empty()
    {
        return size() == 0;
    }

    template <typename... Arguments>
    template<typename RHSTuple>
    constexpr auto Tuple<Arguments...>::operator<=(RHSTuple &tuple) const
    {
        return std_tuple <= tuple.std_tuple;
    }

    template <typename... Arguments>
    template<typename RHSTuple>
    constexpr auto Tuple<Arguments...>::operator>=(RHSTuple &tuple) const
    {
        return std_tuple >= tuple.std_tuple;
    }

    template <typename... Arguments>
    template<typename RHSTuple>
    constexpr auto Tuple<Arguments...>::operator<(RHSTuple &tuple) const
    {
        return std_tuple < tuple.std_tuple;
    }

    template <typename... Arguments>
    template<typename RHSTuple>
    constexpr auto Tuple<Arguments...>::operator>(RHSTuple &tuple) const
    {
        return std_tuple > tuple.std_tuple;
    }

    template <typename... Arguments>
    template<typename... RHSArguments>
    constexpr auto Tuple<Arguments...>::operator==(const Tuple<RHSArguments...> &rhs) const
    {
        return std_tuple == rhs.std_tuple;
    }

    template <typename... Arguments>
    template<typename... RHSArguments>
    constexpr auto Tuple<Arguments...>::operator!=(const Tuple<RHSArguments...> &rhs) const
    {
        return std_tuple != rhs.std_tuple;
    }

    template <typename... Arguments>
    template <typename... RHSArguments>
    constexpr auto Tuple<Arguments...>::operator=(const Tuple<RHSArguments...> &rhs)
    {
        std_tuple = rhs.std_tuple;
        return *this;
    }

    template <typename... Arguments>
    template <typename RHSTuple>
    constexpr auto Tuple<Arguments...>::concat(RHSTuple &tuple) const
    {
        auto result = std::tuple_cat
        (
            std_tuple,
            tuple.std_tuple
        );

        return detail::MoveTemplateTypes<::metaxxa::Tuple, decltype(result)>(result);
    }

    template <typename... Arguments>
    template <typename RHSTuple>
    constexpr auto Tuple<Arguments...>::operator+(RHSTuple &tuple) const
    {
        return concat(tuple);
    }
    
    template <typename... Arguments>
    template <typename RHSTuple>
    constexpr auto Tuple<Arguments...>::concat(RHSTuple &&tuple)
    {
        auto result = std::tuple_cat
        (
            std_tuple,
            tuple.std_tuple
        );
        
        return detail::MoveTemplateTypes<::metaxxa::Tuple, decltype(result)>(result);
    }
    
    template <typename... Arguments>
    template <typename RHSTuple>
    constexpr auto Tuple<Arguments...>::operator+(RHSTuple &&tuple)
    {
        return concat(tuple);
    }

    template <typename... Arguments>
    template <size_t COUNT>
    constexpr auto Tuple<Arguments...>::skip_first() const
    {
        auto tuple = ::metaxxa::skip_first<COUNT>(std_tuple);

        return detail::MoveTemplateTypes<::metaxxa::Tuple, decltype(tuple)>(tuple);
    }

    template <typename... Arguments>
    template <size_t COUNT>
    constexpr auto Tuple<Arguments...>::skip_first_types()
    {
        return std::declval
        <
            detail::MoveTemplateTypes
            <
                ::metaxxa::Tuple,
                decltype(::metaxxa::skip_first_types<COUNT, StdTuple>())
            >
        >();
    }

    template <typename... Arguments>
    template <typename Callable>
    constexpr void Tuple<Arguments...>::for_each(Callable callable) const
    {
        ::metaxxa::for_each(std_tuple, callable);
    }

    template <typename... Arguments>
    template 
    <
        template <typename ValueType> typename Functor,
        typename... FunctorArguments
    >
    constexpr void Tuple<Arguments...>::for_each_types(FunctorArguments&&... arguments)
    {
        ::metaxxa::for_each_types<StdTuple, Functor>(std::forward<FunctorArguments>(arguments)...);
    }

    template <typename... Arguments>
    template <typename Callable>
    constexpr bool Tuple<Arguments...>::every(Callable callable) const
    {
        return ::metaxxa::every(std_tuple, callable);
    }

    template <typename... Arguments>
    template
    <
        template <typename ValueType> typename Functor,
        typename... FunctorArguments
    >
    constexpr bool Tuple<Arguments...>::every_types(FunctorArguments&&... arguments)
    {
        return ::metaxxa::every_types<StdTuple, Functor>(std::forward<FunctorArguments>(arguments)...);
    }

    template <typename... Arguments>
    constexpr bool Tuple<Arguments...>::is_same() const
    {
        return ::metaxxa::is_same(std_tuple);
    }

    template <typename... Arguments>
    constexpr bool Tuple<Arguments...>::is_same_types() 
    {
        return ::metaxxa::is_same_types<StdTuple>();
    }

    template <typename... Arguments>
    constexpr auto Tuple<Arguments...>::max() const
    {
        return ::metaxxa::max(std_tuple);
    }

    template <typename... Arguments>
    constexpr auto &Tuple<Arguments...>::first() const
    {
        return ::metaxxa::first(std_tuple);
    }

    template <typename... Arguments>
    constexpr auto &Tuple<Arguments...>::first()
    {
        return ::metaxxa::first(std_tuple);
    }

    template <typename... Arguments>
    constexpr auto Tuple<Arguments...>::first_types() const
    {
        return ::metaxxa::first_types<StdTuple>();
    }

    template <typename... Arguments>
    constexpr auto &Tuple<Arguments...>::last() const
    {
        return ::metaxxa::last(std_tuple);
    }

    template <typename... Arguments>
    constexpr auto &Tuple<Arguments...>::last()
    {
        return ::metaxxa::last(std_tuple);
    }

    template <typename... Arguments>
    constexpr auto Tuple<Arguments...>::last_types() const
    {
        return ::metaxxa::last_types<StdTuple>();
    }

    template <typename... Arguments>
    template <typename Callable>
    constexpr auto Tuple<Arguments...>::map(Callable callable) const
    {
        auto tuple = ::metaxxa::map(std_tuple, callable);

        return detail::MoveTemplateTypes<::metaxxa::Tuple, decltype(tuple)>(tuple);
    }

    template <typename... Arguments>
    template 
    <
        template <typename ValueType> typename Functor,
        typename... FunctorArguments
    >
    constexpr auto Tuple<Arguments...>::map_types(FunctorArguments&&... arguments)
    {
        auto tuple = ::metaxxa::map_types<StdTuple, Functor, FunctorArguments...>(std::forward<FunctorArguments>(arguments)...);

        return detail::MoveTemplateTypes<::metaxxa::Tuple, decltype(tuple)>(tuple);
    }

    template <typename... Arguments>
    constexpr auto Tuple<Arguments...>::sum() const
    {
        return ::metaxxa::sum(std_tuple);
    }

    template <typename... Arguments>
    template <typename Callable>
    auto Tuple<Arguments...>::find(Callable callable) const
    {
        return ::metaxxa::find(std_tuple, callable);
    }

    template <typename... Arguments>
    template
    <
        template <typename ValueType> typename Functor,
        typename... FunctorArguments
    >
    constexpr auto Tuple<Arguments...>::find_types(FunctorArguments&&... arguments)
    {
        return ::metaxxa::find_types<StdTuple, Functor, FunctorArguments...>
        (
            std::forward<FunctorArguments>(arguments)...
        );
    }

    template <typename... Arguments>
    template <typename Callable>
    auto constexpr Tuple<Arguments...>::filter(Callable callable)
    {
        auto tuple = ::metaxxa::filter(std_tuple, callable);

        return detail::MoveTemplateTypes<::metaxxa::Tuple, decltype(tuple)>(tuple);
    }

    template <typename... Arguments>
    template
    <
        template <typename ValueType> typename Functor,
        typename... FunctorArguments
    >
    constexpr auto Tuple<Arguments...>::filter_types(FunctorArguments&&... arguments)
    {
        auto tuple = ::metaxxa::filter_types<StdTuple, Functor, FunctorArguments...>
        (
            std::forward<FunctorArguments>(arguments)...
        );

        return detail::MoveTemplateTypes<::metaxxa::Tuple, decltype(tuple)>(tuple);

    } 

    template <typename... Arguments>
    template <typename Type>
    constexpr auto Tuple<Arguments...>::contains(Type &value)
    {
        return ::metaxxa::contains(std_tuple, value);
    }

    template <typename... Arguments>
    template <typename Type>
    constexpr auto Tuple<Arguments...>::contains(Type &&value)
    {
        return ::metaxxa::contains(std_tuple, std::forward<Type>(value));
    }

    template <typename... Arguments>
    template <typename... Types>
    constexpr bool Tuple<Arguments...>::contains_types()
    {
        return ::metaxxa::contains_types<StdTuple, Types...>();
    }

    template <typename... Arguments>
    constexpr auto Tuple<Arguments...>::distinct_types()
    {
        return std::declval<detail::MoveTemplateTypes<::metaxxa::Tuple, decltype(::metaxxa::distinct_types<StdTuple>())>>();
    }

    template <typename... Arguments>
    template <typename Type>
    constexpr bool Tuple<Arguments...>::is_converts_to_types()
    {
        return ::metaxxa::is_converts_to_types<StdTuple, Type>();
    }

    template <typename... Arguments>
    template <template <typename> typename TemplateType>
    constexpr auto Tuple<Arguments...>::wrap()
    {
        auto tuple = wrap_of_std_tuple<StdTuple, TemplateType>(std_tuple);

        return detail::MoveTemplateTypes<::metaxxa::Tuple, decltype(tuple)>(tuple);
    }

    template <typename... Arguments>
    template <template <typename> typename TemplateType>
    constexpr auto Tuple<Arguments...>::wrap_types()
    {
        return std::declval<detail::MoveTemplateTypes<::metaxxa::Tuple, decltype(wrap_of_std_tuple_types<StdTuple, TemplateType>())>>();
    }

    template <typename... Arguments>
    template <typename... RHSArguments>
    void Tuple<Arguments...>::execute_functions(RHSArguments&&... arguments) const
    {
        ::metaxxa::execute_functions(std_tuple, std::forward<RHSArguments>(arguments)...);
    }

    template <typename... Arguments>
    template <typename Callable>
    auto Tuple<Arguments...>::call_function(Callable &callable) const
    {
        return ::metaxxa::call_function(std_tuple, callable);
    }

    template <typename... Arguments>
    std::string Tuple<Arguments...>::to_string() const
    {
        return ::metaxxa::to_string(std_tuple);
    }

    template <typename... Arguments>
    std::string Tuple<Arguments...>::to_string_types() 
    {
        return ::metaxxa::to_string_types<StdTuple>();
    }

    
    Tuple<>::Tuple(const std::tuple<> &) {}

    
    template<typename... Arguments>
    constexpr auto Tuple<>::operator==(const Tuple<Arguments...> &rhs) const
    {
        return std_tuple == rhs.std_tuple;
    }

    
    template<typename... Arguments>
    constexpr auto Tuple<>::operator!=(const Tuple<Arguments...> &rhs) const
    {
        return std_tuple != rhs.std_tuple;
    }

    
    template <typename RHSTuple>
    constexpr auto Tuple<>::concat(RHSTuple &tuple) const
    {
        auto result = std::tuple_cat
        (
            std_tuple,
            tuple.std_tuple
        );

        return detail::MoveTemplateTypes<::metaxxa::Tuple, decltype(result)>(result);
    }

    
    template <typename RHSTuple>
    constexpr auto Tuple<>::operator+(RHSTuple &tuple) const
    {
        return concat(tuple);
    }

    
    template <typename RHSTuple>
    constexpr auto Tuple<>::concat(RHSTuple &&tuple)
    {
        auto result = std::tuple_cat
        (
            std_tuple,
            tuple.std_tuple
        );

        return detail::MoveTemplateTypes<::metaxxa::Tuple, decltype(result)>(result);
    }

    
    template <typename RHSTuple>
    constexpr auto Tuple<>::operator+(RHSTuple &&tuple)
    {
        return concat(tuple);
    }

    
    constexpr size_t Tuple<>::get_size()
    {
        return 0;
    }

    
    constexpr size_t Tuple<>::size()
    {
        return get_size();
    }
    
    
    constexpr bool Tuple<>::is_empty()
    {
        return true;
    }

    
    template <typename Callable>
    constexpr void Tuple<>::for_each(Callable callable) const
    {}

    
    template
    <
        template <typename ValueType> typename Functor,
        typename... FunctorArguments
    >
    constexpr void Tuple<>::for_each_types(FunctorArguments&&... arguments)
    {}

    
    template <typename Callable>
    constexpr bool Tuple<>::every(Callable callable) const
    {
        return false;
    }

    
    template
    <
        template <typename ValueType> typename Functor,
        typename... FunctorArguments
    >
    constexpr bool Tuple<>::every_types()
    {
        return false;
    }
    
    
    template <typename... Types>
    constexpr bool Tuple<>::contains_types()
    {
        return ::metaxxa::contains_types<StdTuple, Types...>();
    }

    
    constexpr auto Tuple<>::distinct_types() 
    {
        return Tuple<>();
    }

    
    template <typename Type>
    constexpr bool Tuple<>::is_converts_to_types()
    {
        return false;
    }

    
    template <template <typename> typename TemplateType>
    constexpr auto Tuple<>::wrap_all_types()
    {
        return std::tuple<>();
    }

    
    template <typename... RHSArguments>
    void Tuple<>::execute_functions(RHSArguments&&... arguments) const
    {}
    
    
    template <typename Callable>
    auto Tuple<>::call_function(Callable &callable) const
    {
        return callable();
    }

    
    std::string Tuple<>::to_string() const
    {
        return to_string_types();
    }

    
    std::string Tuple<>::to_string_types()
    {
        return ::metaxxa::to_string(std::tuple<>());
    }

    
    template <typename... Arguments>
	auto tuple_ref(Arguments&&... arguments)
	{
		return Tuple<Arguments...>(std::forward<Arguments>(arguments)...);
	}

	template <typename... Arguments>
	auto tuple(Arguments... arguments)
	{
		Tuple<Arguments...> result(std::forward<Arguments>(arguments)...);

		return result;
	}
}

#endif // METAXXA_TUPLE_INC