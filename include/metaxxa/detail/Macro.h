#ifndef METAXXA_detail_MACRO_H
#define METAXXA_detail_MACRO_H

#define ___METAXXA___EXPAND_DEEP(...) __VA_ARGS__

#define ___METAXXA___EXPAND(...) ___METAXXA___EXPAND_DEEP(__VA_ARGS__)

#endif // METAXXA_detail_MACRO_H