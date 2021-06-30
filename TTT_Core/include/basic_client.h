#pragma once
#include "ttt_core_include.h"
#include "net_op_codes.h"
#include "leaderboard.h"
#include "play.h"
#include "dummy_net_traits.h"

namespace ttt
{
   /*
    Before calling a <send_> function, you should send the prerequisite
    NET_OP_CODES.
    Before calling a <receive_> function, you should send the prerequisite
    NET_OP_CODES. Then, wait for the server to send a message describing the
    payload. Finally, read the payload.
    */
   template<typename NetTraits>
   class basic_client
   {
      basic_client(const std::string& ip, uint16_t port,
                   const NetTraits& traits = NetTraits());

      basic_client(const basic_client&) = delete;

      basic_client(basic_client&&);

      /*
       Destructor should disconnect from the server if not already.
       */
      ~basic_client() noexcept;

      /*
       PREREQ: Send <OP_ASK_MOVE_VALID> message.
       
       Writes <m> to the server and waits for the server to send a message
       back if the move was valid.
       Returns true if the move is valid.
       */
      bool check_move(const play& m);

      /*
       PREREQ: Send the <OP_SEND_PLAY> message.
       
       Write <m> to the server socket..
       Returns true if the server successfully processed the move.
       */
      bool send_move(const play& m);

      /*
       PREREQ: Send the <OP_REQUEST_LAST_MOVE> message to the server.
       
       Waits for the server to send back <OP_SEND_PLAY> followed by the move.
       Puts the response from the server in <m>.
       Returns true if the server successfully sent the move to you.
       */
      bool receive_move(play& m);

      /*
       PREREQ: Send the <OP_SEND_NAME> message to the server.
       
       Writes <str> to the server socket.
       Returns true on success.
       */
      bool send_str(const std::string& str);

      /*
       PREREQ: Send the <OP_REQUEST_NAME> message to the server.
       
       Waits for the <OP_SEND_NAME> message. Then reads a string from the
       server socket and puts the result in <str>.
       Returns true on success.
       */
      bool receive_str(std::string& str);

      /*
       PREREQ: Send the <OP_REQUEST_LEADERBOARD> message to the server.
       
       Waits for the <OP_SEND_LEADERBOARD> message. Then reads the
       leaderboard from the socket and puts the result in <l>
       Returns true on success.
       */
      bool receive_leaderboard(leaderboard& l);

      /*
       Reads an op code from the server socket. Returns OP_ERROR if there
       was a problem.
       */
      NET_OP_CODES read_op();

      /*
       Sends the op code <op> to the server. Returns true on success.
       */
      bool write_op(NET_OP_CODES op);

      /*
       Sends the disconnect message to the server and disconnects.
       */
      void disconnect() noexcept;

      /*
       Returns the last error that occurred when calling a network function.
       */
      socket_error_t net_error() const noexcept;

      /*
       Return the last error that occured while using a system function.
       */
      sys_error_t sys_error() const noexcept;

      STATIC_NET_TRAITS_TESTS(NetTraits);

      private:
      NetTraits m_traits;
   };
}