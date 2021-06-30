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
    * payload.
    */
   template<typename NetTraits>
   class basic_server
   {
      public:
      basic_server(uint16_t port, uint16_t maxConnections,
                   const NetTraits& traits = NetTraits());

      basic_server(const basic_server&) = delete;

      basic_server(basic_server&&);

      /*
       Destructor should send the disconnect message to all clients.
       */
      ~basic_server() noexcept;

      /*
       Disconnects the client.
       It might be a good idea to send the <OP_DISCONNECT> message to the
       client first so they know they will be disconnected.
       */
      void disconnect(socket_t s);

      /*
       Sends the <OP_SEND_NAME> message followed by <playerName> to the
       client.
       Returns true on success.
       */
      bool send_name(socket_t s, const std::string& playerName);

      /*
       Sends the <OP_SEND_LEADERBOARD> message followed by <l> to the client.
       Returns true on success.
       */
      bool send_leaderboard(socket_t s, const leaderboard& l);

      /*
       Sends the <OP_SEND_PLAY> message followed by play <m> to the client.
       Returns true on success.
       */
      bool send_move(socket_t s, const play& m);

      /*
       PREREQ: Send the <OP_YOUR_TURN> message to the client.
       
       Receives a move from the client and puts the result in <m>.
       Returns true on success.
       */
      bool receive_move(socket_t s, play& m);

      /*
       PREREQ: Send the <OP_REQUEST_NAME> message to the client.
       
       Waits for the <OP_SEND_NAME> message. Then reads a string from the
       server socket and puts the result in <name>.
       Returns true on success.
       */
      bool receive_name(socket_t s, std::string& name);

      /*
       Reads an op code from the client socket <s>. Returns OP_ERROR if there
       was a problem.
       */
      NET_OP_CODES read_op(socket_t s);

      /*
       Sends the op code <op> to the client <s>. Returns true on success.
       */
      bool write_op(socket_t s, NET_OP_CODES op);

      /*
       Given a player ID, returns the socket used to communicate with them.
       Throws std::out_of_range if the player ID is not valid.
       */
      socket_t at(int playerID) const;

      /*
       Returns the last error that occurred when calling a network function.
       */
      socket_error_t net_error() const noexcept;

      /*
       * Return the last error that occured while using a system function.
       */
      sys_error_t sys_error() const noexcept;

      STATIC_NET_TRAITS_TESTS(NetTraits);

      private:
      NetTraits m_traits;
   };
}

