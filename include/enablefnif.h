#ifndef METAXXA_ENABLEFNIF_H
#define METAXXA_ENABLEFNIF_H

#include <type_traits>

#define ENABLE_FN_IF(CONDITION) std::enable_if_t<CONDITION> * = nullptr

#endif // METAXXA_ENABLEFNIF_H