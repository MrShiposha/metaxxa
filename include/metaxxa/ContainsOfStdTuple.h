#ifndef METAXXA_CONTAINSTYPEOFSTDTUPLE_H
#define METAXXA_CONTAINSTYPEOFSTDTUPLE_H

#include <tuple>

namespace metaxxa
{
	namespace detail
	{
		template <typename Tuple, typename Type, size_t INDEX>
		constexpr bool contains(Tuple &tuple, Type &value)
		{
			if constexpr (INDEX == std::tuple_size_v<Tuple>)
				return false;
			else
			{
				if (std::get<INDEX>(tuple) == value)
					return true;
				else
					return contains<Tuple, Type, INDEX + 1>(tuple, value);
			}
		}

		template <typename Tuple, typename Type, size_t INDEX>
		constexpr bool contains_type()
		{
			if constexpr (INDEX + 1 == std::tuple_size_v<Tuple>)
				return std::is_same_v<typename std::tuple_element_t<INDEX, Tuple>, Type>;
			else if constexpr (std::is_same_v<typename std::tuple_element_t<INDEX, Tuple>, Type>)
				return true;
			else
				return contains_type<Tuple, Type, INDEX + 1>();
		}

		struct NoType {};

		template <typename Tuple, typename Type = NoType, typename... Types>
		constexpr bool contains_types()
		{
			if constexpr (std::is_same_v<Type, NoType>)
				return true;
			else if constexpr (sizeof...(Types) == 0)
				return contains_type<Tuple, Type, 0>();
			else
				return contains_type<Tuple, Type, 0>() && contains_types<Tuple, Types...>();
		}
	}

	template <typename Tuple, typename Type>
	constexpr bool contains(Tuple &tuple, Type &value)
	{
		return detail::contains<Tuple, Type, 0>(tuple, value);
	}

	template <typename Tuple, typename Type>
	constexpr bool contains(Tuple &tuple, Type &&value)
	{
		return detail::contains<Tuple, Type, 0>(tuple, value);
	}

	template <typename Tuple, typename... Types>
	constexpr bool contains_types(typename std::enable_if<!std::is_same_v<Tuple, std::tuple<>>>::type * = nullptr)
	{
		return detail::contains_types<Tuple, Types...>();
	}

	template <typename Tuple, typename... Types>
	constexpr bool contains_types(typename std::enable_if<std::is_same_v<Tuple, std::tuple<>>>::type * = nullptr)
	{
		return false;
	}
}

#endif // METAXXA_CONTAINSTYPEOFSTDTUPLE_H