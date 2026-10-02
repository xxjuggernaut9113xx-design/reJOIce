#pragma once
// UE5.3 predates MSVC14.44's ASAN header discovery. MSVC has no Clang
// __has_feature predicate; define its fallback before any engine header.
#if defined(_MSC_VER) && !defined(__clang__) && !defined(__has_feature)
#define __has_feature(x) 0
#endif
