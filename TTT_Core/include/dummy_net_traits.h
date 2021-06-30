#pragma once
#include "ttt_core_include.h"
#include "net_op_codes.h"

namespace ttt::dummy
{
   /*
    Dummy version of the NetTraits named requirements.
    IMPORTANT: NetTraits classes should not include a copy constructor.
    Only 1 object should manage a socket. If multiple objects manage a 
    socket, then the socket will be invalid if one of the objects is disposed.
    TODO: Does it make sense to add const versions of the read/write
    functions? Or should reading and writing to a socket be considered a 
    mutable action?
    */
   class dummy_net_traits
   {
      public:
      /*
       Writes <count> number of elements from <a> to socket <s>
       Returns the number of bytes written.
       Since this is a dummy function, it will always return 
       <count> * sizeof(ElementT)
       */
      template<typename ElementT>
      size_t write(socket_t s, const ElementT* const a, size_t count)
      {
         return sizeof(ElementT) * count;
      }

      /*
       Writes <x> to socket <s> and returns the number of bytes written.
       Since this is a dummy function, it will always return sizeof(T)
       */
      template<typename T>
      size_t write(socket_t s, const T& x)
      {
         return sizeof(T);
      }

      /*
       Reads <count> number of elements from socket <s> and puts them into
       <a>. <a> must be allocated to hold count * sizeof(ElementT) bytes.
       It is the caller's responsibility to make sure enough memory is 
       allocated in <a>.
       Returns the number of bytes that were actually read from the socket.
       Since this is a dummy function, it will always return
       <count> * sizeof(ElementT) bytes.
       */
      template<typename ElementT>
      size_t read(socket_t s, ElementT* const out, size_t count)
      {
         return sizeof(ElementT) * count;
      }

      /*
       Reads a T from socket <s> and puts the result in <out>.
       Returns the number of bytes read.
       Since this is a dummy function, it will always return sizeof(T).
       */
      template<typename T>
      size_t read(socket_t s, T& out)
      {
         return sizeof(T);
      }

      /*
       Converts <x> from network order to host order.
       Since this is a dummy function, this just returns x.
       */
      template<typename T>
      T n_to_h(const T x) const
      {
         return x;
      }

      /*
       Converts <x> from host order to network order. Since this is a dummy
       function, this just returns x.
       */
      template<typename T>
      T h_to_n(const T x) const
      {
         return x;
      }

      /*
       Reads an op code from the socket.
       Returns OP_ERROR if there is a problem.
       Since this is a dummy function, this will always return OP_ERROR.
       */
      NET_OP_CODES read_op(socket_t s)
      {
         return NET_OP_CODES::OP_ERROR;
      }

      /*
       Writes an op code to the socket.
       Returns true on success, otherwise false.
       Since this is a dummy function, this will always return true.
       */
      bool write_op(socket_t s, NET_OP_CODES op)
      {
         return true;
      }

      /*
       Returns the last error that occurred when calling a network function.
       Since this is a dummy function, it will always return 0.
       This should abstract errno on Linux and GetLastError() on Windows.
       */
      socket_error_t error() const noexcept
      {
         return 0;
      }
   };
}