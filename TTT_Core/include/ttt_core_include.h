#pragma once
#include "platform_abstraction.h"

#ifdef TTT_CORE_EXPORTS
#define TTT_CORE_API __declspec(dllexport)
#else
#define TTT_CORE_API __declspec(dllimport)
#endif

namespace ttt
{
   namespace internal
   {
      /*
       Compile-time endianness swap from http://stackoverflow.com/a/36937049
       Also see https://en.cppreference.com/w/cpp/language/fold
       */
      template<class T, std::size_t... N>
      constexpr T bswap(T i, std::index_sequence<N...>)
      {
         return (((i >> N * CHAR_BIT & std::uint8_t(-1)) <<
            (sizeof(T) - 1 - N)*CHAR_BIT) | ...);
      }
   }

   /*
    Swaps the endianess of a value.
    */
   template<typename T>
   constexpr T bswap(T val)
   {
      return internal::bswap<T>(val, std::make_index_sequence<sizeof(T)>{});
   }

   /*
    Assert that the bswap function is correct.
    */
   static_assert(bswap<uint16_t>(0x1234u) == static_cast<uint16_t>(0x3412u));
   static_assert(bswap<uint64_t>(0x0123456789abcdefULL) ==
                 static_cast<uint64_t>(0xefcdab8967452301ULL));

   /*
    Counts the number of elements until a terminator is found.
    The returned count does not include the null terminator.
    str: The string of elements to search.
    terminator: The value to search for.
    i: Recursive parameter. Index of which element to check. The caller can set
    this to something besides 0 to start searching str at an offset.
    */
   template<typename T, typename SizeT = size_t>
   constexpr size_t mem_length(const T* str,
                               const T terminator = 0,
                               const SizeT i = 0)
   {
      return (str && str[i] != terminator) ?
         mem_length(str, terminator, i + 1) + 1 : 0;
   }

}


/*
 While macros are usually bad, here is an example of when they might be
 appropriate:
 Instead of duplicating the static_asserts in all classes that reference
 the named requirement "NetTraits", wrap the tests into a macro and
 put the macro in classes with the "NetTraits" template.
 */
#define STATIC_NET_TRAITS_TESTS(NET_TRAITS_TEMPLATE_TYPE_NAME)\
   static_assert( \
      std::is_invocable_r_v<NET_OP_CODES, \
         decltype(&NET_TRAITS_TEMPLATE_TYPE_NAME::read_op), \
         NET_TRAITS_TEMPLATE_TYPE_NAME&, \
         socket_t>, \
      "NetTraits does not have \"NET_OP_CODES read_op(socket_t s)\"" \
      ); \
   static_assert( \
      std::is_invocable_r_v<bool, \
         decltype(&NET_TRAITS_TEMPLATE_TYPE_NAME::write_op), \
         NET_TRAITS_TEMPLATE_TYPE_NAME&, \
         socket_t, \
         NET_OP_CODES>, \
      "NetTraits does not have \"bool write_op(socket_t s, NET_OP_CODES op)\"" \
      ); \
   static_assert( \
      std::is_invocable_r_v<socket_error_t, \
         decltype(&NET_TRAITS_TEMPLATE_TYPE_NAME::error), \
         NET_TRAITS_TEMPLATE_TYPE_NAME&>, \
      "NetTraits does not have \"socket_error_t error() const noexcept\"" \
      );

