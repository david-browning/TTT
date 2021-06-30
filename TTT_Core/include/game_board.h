#pragma once
#include "ttt_core_include.h"
#include "play.h"

namespace ttt
{
   class game_board
   {
      public:
      game_board(uint32_t dimension);

      uint32_t dimension() const noexcept;

      bool occupied(uint32_t row, uint32_t col) const;

      char& at(uint32_t row, uint32_t col);

      char at(uint32_t row, uint32_t col) const;

      const play& last() const noexcept;
   };
}