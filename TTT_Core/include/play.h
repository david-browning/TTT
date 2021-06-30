#pragma once
#include "ttt_core_include.h"

namespace ttt
{
   /*
    Describes a move.
    */
   struct play
   {
      play(uint32_t moveID,
           uint32_t rowPosition,
           uint32_t colPosition,
           char playerShape);

      play(const play&) = default;

      play(play&&) = default;

      ~play() noexcept = default;

      uint32_t id() const noexcept;

      uint32_t row() const noexcept;

      uint32_t col() const noexcept;

      char shape() const noexcept;
   };
}