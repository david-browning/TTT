#pragma once
#include "ttt_core_include.h"

namespace ttt
{
   /*
    Op codes used to communicate between the client and server.
    DO NOT CHANGE THESE VALUES. Doing so can cause different versions of the
    client and server to communicate incorrectly.
    */
   enum class NET_OP_CODES : uint8_t
   {
      //////////////Bi-directional messages//////////////

      // Communication Error
      OP_ERROR = 0,

      // Tell the client or server that they are disconnecting.
      OP_DISCONNECT = 0x11,

      // Tell the server or client that the next message in the socket is a 
      // play.
      OP_SEND_PLAY = 0x12,

      // Tell the server or client that the next message is a string.
      OP_SEND_NAME = 0x13,

      // Ask the server or client to send a string.
      OP_REQUEST_NAME = 0x14,

      //////////////Messages only the client sends//////////////

      // Client requests the leaderboard from server.
      // Only the client should send this message. Server receives this.
      OP_REQUEST_LEADERBOARD = 0x22,

      // Client requests the server to get the last move.
      // Only the client should send this message. Server receives this.
      OP_REQUEST_LAST_MOVE = 0x23,

      // Client requests if the move is valid.
      // Only the client should send this message. Server receives this.
      OP_ASK_MOVE_VALID = 0x24,


      //////////////Messages only the server sends//////////////

      // Tell the client that the game is starting.
      // Only the server should send this message. Client receives this.
      OP_GAME_START = 0x31,

      // Tell the client that it is their turn to make a move.
      // Only the server should send this message. Client receives this.
      OP_YOUR_TURN = 0x32,

      // Tell the client that the game is over.
      // Only the server should send this. Client receives it.
      OP_GAME_OVER = 0x33,

      OP_SEND_LEADERBOARD = 0x34,
   };
}