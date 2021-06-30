#pragma once
#include "ttt_core_include.h"
#include "play.h"
#include "game_board.h"

namespace ttt::dummy
{
   /*
    Returns a play at the next available spot in the board.
    */
   template<char shape>
   class dummy_input_traits
   {
      public:
      dummy_input_traits() : board(nullptr)
      { 
      }

      dummy_input_traits(const dummy_input_traits&) = default;

      dummy_input_traits(dummy_input_traits&&) = default;

      /*
       Returns the play that the player will make.
       This dummy player will just play the next open spot.
       */
      play get()
      {
         #ifdef DEBUG
         if (!board)
         {
            throw std::runtime_error(
               "You must call \"update()\" before \"get()\". "
               "Board pointer is null.");
         }
         #endif

         // Iterate through each row/column pair until finding an empty spot.
         // auto is a way to deduce a type from a function call.
         auto dim = board->dimension();
         // decltype is a way of determining the type from an expression.
         for (auto row = static_cast<decltype(dim)>(0); row < dim; row++)
         {
            for (auto col = static_cast<decltype(dim)>(0); col < dim; col++)
            {
               if (!board->occupied(row, col))
               {
                  return play{ board->last().id(), row, col, shape };
               }
            }
         }
      }

      /*
       Sets the trait's internal reference to the board.
       */
      void update(const game_board& b) noexcept
      {
         this->board = std::addressof(b);
      }

      private:
      /*
       const pointer to the game board. Use a pointer instead of a reference
       because we need to construct this class before the board has been 
       initialized. References do not allow null.
       Use const to enforce that the traits cannot modify the board.
       This is a weak pointer. Do not try to free it in the destructor.
       */
      const game_board* board;
   };

   /*
    Dummy player who plays as x
    */
   using dummy_input_traits_x = dummy_input_traits<'x'>;

   /*
    Dummy player who plays as o
    */
   using dummy_input_traits_o = dummy_input_traits<'o'>;
}