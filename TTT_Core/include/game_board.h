#pragma once
#include "ttt_core_include.h"
#include "play.h"

namespace ttt
{
   class game_board
   {
      public:
      game_board(uint32_t dimension);

      game_board(const game_board&) = default;
      game_board(game_board&&) = default;
      ~game_board() = default;

      uint32_t dimension() const noexcept;

      bool occupied(uint32_t row, uint32_t col) const;

      char& at(uint32_t row, uint32_t col);

      char at(uint32_t row, uint32_t col) const;
   };
}