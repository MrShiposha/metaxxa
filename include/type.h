#ifndef METAXXA_TYPE_H
#define METAXXA_TYPE_H

#include "typelist.h"
#include "parameterscount.h"
#include "moveparameters.h"
#include "times.h"
#include "isinstantiationof.h"
#include "isapplicable.h"
#include "algorithm/algorithm.h"

namespace metaxxa
{
    template <typename T>
    class Type
    {
    public:
        using Unwrap = T;

        template <typename... With>
        using Concat = Type<::metaxxa::Concat<TypeList, T, With...>>;

        template <template <typename...> typename Template>
        using MoveParameters = Type<::metaxxa::MoveParameters<Template, T>>;

        template <std::size_t N>
        using Times = Type<::metaxxa::Times<TypeList, N, T>>;

        template <template <typename> typename Functor>
        using Filter = Type<::metaxxa::Filter<TypeList, T, Functor>>;

        template <template <typename, std::size_t INDEX> typename Functor>
        using IndexFilter = Type<::metaxxa::IndexFilter<TypeList, T, Functor>>;

        template <template <typename, std::size_t INDEX, typename SrcTuple> typename Functor>
        using OverallFilter = Type<::metaxxa::OverallFilter<TypeList, T, Functor>>;

        template <typename Sequence>
        using IndexSeqFilter = Type<SeqFilter<TypeList, T, Sequence>>;

        template <template <typename> typename Functor>
        using Map = Type<::metaxxa::Map<TypeList, T, Functor>>;

        template <template <typename, std::size_t INDEX> typename Functor>
        using IndexMap = Type<::metaxxa::IndexMap<TypeList, T, Functor>>;

        template <template <typename, std::size_t INDEX, typename SrcTuple> typename Functor>
        using OverallMap = Type<::metaxxa::OverallMap<TypeList, T, Functor>>;

        template <std::size_t... INDICES>
        using OnlyIndices = Type<::metaxxa::OnlyIndices<TypeList, T, INDICES...>>;

        template <std::size_t N>
        using SkipFirst = Type<::metaxxa::SkipFirst<TypeList, T, N>>;

        template <std::size_t N>
        using SkipLast = Type<::metaxxa::SkipLast<TypeList, T, N>>;

        template <std::size_t FROM, std::size_t TO>
        using SkipRange = Type<::metaxxa::SkipRange<TypeList, T, FROM, TO>>;

        template <std::size_t N>
        using TakeFirst = Type<::metaxxa::TakeFirst<TypeList, T, N>>;

        template <std::size_t N>
        using TakeLast = Type<::metaxxa::TakeLast<TypeList, T, N>>;

        template <std::size_t FROM, std::size_t TO>
        using TakeRange = Type<::metaxxa::TakeRange<TypeList, T, FROM, TO>>;

        using Unique = Type<::metaxxa::Unique<TypeList, T>>;

        static constexpr std::size_t parameters_count() { return ::metaxxa::parameters_count<T>(); }

        template <template <typename...> typename Template>
        static constexpr bool is_instatiation_of() { return ::metaxxa::is_instatiation_of<T, Template>(); }

        template <typename Callable>
        static constexpr bool is_applicable() { return ::metaxxa::is_applicable<Callable, T>(); }

        template <typename U>
        static constexpr bool contains() { return ::metaxxa::contains<T, U>(); }

        template <typename... Ts>
        static constexpr bool contains_all() { return ::metaxxa::contains_all<T, Ts...>(); }

        template <typename Tuple>
        static constexpr bool contains_packed() { return ::metaxxa::contains_packed<T, Tuple>(); }

        template <template <typename> typename Predicate>
        static constexpr bool every() { return ::metaxxa::Every<Predicate, T>::value; }

        static constexpr bool is_parameters_unique() { return ::metaxxa::is_unique<T>(); }
    };
}

#endif // METAXXA_TYPE_H