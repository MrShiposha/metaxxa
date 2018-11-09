#ifndef METAXXA_MOVEFUNCTIONARGUMENTTYPES_H
#define METAXXA_MOVEFUNCTIONARGUMENTTYPES_H

#include "Function.h"
#include "detail/MoveTemplateTypes.h"

namespace metaxxa
{
	template<template<typename...> typename TemplateType, typename Callable>
	using MoveFunctionArgumentTypes = detail::MoveTemplateTypes<TemplateType, typename Function<Callable>::Arguments>;
}

#endif //METAXXA_MOVEFUNCTIONARGUMENTTYPES_H