#ifndef METAXXA_TUPLE_H
#define METAXXA_TUPLE_H

#include <tuple>

namespace metaxxa
{
	template <typename... Arguments>
	class Tuple
	{
	public:
		using StdTuple = std::tuple<Arguments...>;

		template <size_t INDEX>
		using Parameter = typename std::tuple_element<INDEX, StdTuple>::type;

		constexpr Tuple() = default;

		constexpr Tuple(const Arguments&... arguments);

		template <typename... OtherArguments>
		constexpr Tuple(const Tuple<OtherArguments...> &other);

		constexpr Tuple(const StdTuple &tuple);
		
		constexpr Tuple(const Tuple &) = default;
		
		Tuple &operator=(const Tuple &tuple) = default;

		template <size_t INDEX>
		auto &get() const;

		template <size_t INDEX>
		auto &get();

		static constexpr size_t get_size();

		static constexpr size_t size();
		
		static constexpr bool is_empty();

		template<typename Tuple>
		constexpr auto operator<=(Tuple &tuple) const;

		template<typename Tuple>
		constexpr auto operator>=(Tuple &tuple) const;

		template<typename Tuple>
		constexpr auto operator<(Tuple &tuple) const;

		template<typename Tuple>
		constexpr auto operator>(Tuple &tuple) const;

		template<typename... RHSArguments>
		constexpr auto operator==(const Tuple<RHSArguments...> &rhs) const;

		template<typename... RHSArguments>
		constexpr auto operator!=(const Tuple<RHSArguments...> &rhs) const;

		template <typename... RHSArguments>
		constexpr auto operator=(const Tuple<RHSArguments...> &rhs);

		template <typename Tuple>
		constexpr auto concat(Tuple &tuple) const;

		template <typename Tuple>
		constexpr auto operator+(Tuple &tuple) const;
		
		template <typename Tuple>
		constexpr auto concat(Tuple &&tuple);
		
		template <typename Tuple>
		constexpr auto operator+(Tuple &&tuple);

		template <size_t COUNT>
		constexpr auto skip_first() const;

		template <size_t COUNT>
		static constexpr auto skip_first_types();

		template <typename Callable>
		constexpr void for_each(Callable callable) const;

		template 
		<
			template <typename ValueType> typename Functor,
			typename... FunctorArguments
		>
		static constexpr void for_each_types(FunctorArguments&&... arguments);

		template <typename Callable>
		constexpr bool every(Callable callable) const;

		template
		<
			template <typename ValueType> typename Functor,
			typename... FunctorArguments
		>
		static constexpr bool every_types(FunctorArguments&&... arguments);

		constexpr bool is_same() const;

		static constexpr bool is_same_types();

		constexpr auto max() const;

		constexpr auto &first() const;

		constexpr auto &first();

		constexpr auto first_types() const;

		constexpr auto &last() const;

		constexpr auto &last();

		constexpr auto last_types() const;


		template <typename Callable>
		constexpr auto map(Callable callable) const;

		template 
		<
			template <typename ValueType> typename Functor,
			typename... FunctorArguments
		>
		static constexpr auto map_types(FunctorArguments&&... arguments);

		constexpr auto sum() const;

		template <typename Callable>
		auto find(Callable callable) const;

		template
		<
			template <typename ValueType> typename Functor,
			typename... FunctorArguments
		>
		static constexpr auto find_types(FunctorArguments&&... arguments);

		template <typename Callable>
		auto constexpr filter(Callable callable);

		template
		<
			template <typename ValueType> typename Functor,
			typename... FunctorArguments
		>
		static constexpr auto filter_types(FunctorArguments&&... arguments);

		template <typename Type>
		constexpr auto contains(Type &value);

		template <typename Type>
		constexpr auto contains(Type &&value);

		template <typename... Types>
		static constexpr bool contains_types();

		static constexpr auto distinct_types();

		template <typename Type>
		static constexpr bool is_converts_to_types();

		template <template <typename> typename TemplateType>
		constexpr auto wrap();

		template <template <typename> typename TemplateType>
		static constexpr auto wrap_types();

		// template <typename... RHSArguments>
		// void execute_functions(RHSArguments&&... arguments) const;

		template <typename Callable>
		auto call_function(Callable &callable) const;

		std::string to_string() const;

		static std::string to_string_types();

		template<typename...> friend class Tuple;
		friend class Tuple<>;

		template<typename...> friend class Tuple;
	
	private:
		StdTuple std_tuple;
	};

	template<>
	class Tuple<>
	{
	public:
		using StdTuple = std::tuple<>;

		constexpr Tuple() = default;

		constexpr Tuple(const std::tuple<> &);

		template<typename... Arguments>
		constexpr auto operator==(const Tuple<Arguments...> &rhs) const;

		template<typename... Arguments>
		constexpr auto operator!=(const Tuple<Arguments...> &rhs) const;

		template <typename Tuple>
		constexpr auto concat(Tuple &tuple) const;

		template <typename Tuple>
		constexpr auto operator+(Tuple &tuple) const;

		template <typename Tuple>
		constexpr auto concat(Tuple &&tuple);

		template <typename Tuple>
		constexpr auto operator+(Tuple &&tuple);

		static constexpr size_t get_size();

		static constexpr size_t size();
		
		static constexpr bool is_empty();

		template <typename Callable>
		constexpr void for_each(Callable callable) const;

		template
		<
			template <typename ValueType> typename Functor,
			typename... FunctorArguments
		>
		static constexpr void for_each_types(FunctorArguments&&... arguments);

		template <typename Callable>
		constexpr bool every(Callable callable) const;

		template
		<
			template <typename ValueType> typename Functor,
			typename... FunctorArguments
		>
		static constexpr bool every_types();
		
		template <typename... Types>
		static constexpr bool contains_types();

		static constexpr auto distinct_types();

		template <typename Type>
		static constexpr bool is_converts_to_types();

		template <template <typename> typename TemplateType>
		static constexpr auto wrap_all_types();

		// template <typename... RHSArguments>
		// void execute_functions(RHSArguments&&... arguments) const;
		
		template <typename Callable>
		auto call_function(Callable &callable) const;

		std::string to_string() const;

		static std::string to_string_types();

	private:
		StdTuple std_tuple;

		template<typename...> friend class Tuple;
	};		

	template <typename... Arguments>
	auto tuple_ref(Arguments&&... arguments);

	template <typename... Arguments>
	auto tuple(Arguments... arguments);
}

namespace std
{
	template <typename... Arguments>
	class tuple_size<metaxxa::Tuple<Arguments...>> 
		: public std::integral_constant<size_t, metaxxa::Tuple<Arguments...>::size()>
	{};

	template <size_t INDEX, typename... Arguments>
	class tuple_element<INDEX, metaxxa::Tuple<Arguments...>>
	{
	public:
		using type = std::tuple_element_t<INDEX, typename metaxxa::Tuple<Arguments...>::StdTuple>;
	};

	template <>
	class tuple_size<metaxxa::Tuple<>> 
		: public std::integral_constant<size_t, 0>
	{};
}

#endif // METAXXA_TUPLE_H