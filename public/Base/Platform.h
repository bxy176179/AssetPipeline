#pragma once

namespace cd
{

// Inline in cpp doesn't gurantee that compiler will treat it as an inline function.
// Instead, it only suggest the compiler to treat it as an inline function.
// So we still need to use force inline in writing highly performance critical codes.
// Don't need to use it everywhere. Use it after profiling will be better.
#ifdef _MSC_VER
#	define CD_FORCEINLINE __forceinline
#	define CD_NOINLINE __declspec(noinline)
#else
#	define CD_FORCEINLINE inline __attribute__((always_inline))
#	define CD_NOINLINE __attribute__((noinline))
#endif

}