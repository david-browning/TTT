#pragma once
#include "ttt_core_include.h"
#include "play.h"
#include "game_board.h"

namespace ttt
{
   template<typename InputTraits>
   class basic_player
   {
      public:
      basic_player(uint32_t playerID,
                   const std::string& playerName,
                   char playerShape,
                   InputTraits traits = InputTraits()) :
         m_id(playerID), m_name(playerName), 
         m_shape(playerShape), m_traits(traits)
      {

      }

      /*
       Do not allow copying a player.
       */
      basic_player(const basic_player&) = delete;

      /*
       Move constructor. Default because all private members have move 
       constructors defined.
       */
      basic_player(basic_player&&) = default;

      /*
       Destructor. Defaults because all private members have destructors.
       */
      ~basic_player() noexcept = default;

      /*
       Gets the player's move.
       */
      play get_play()
      {
         return m_traits.get();
      }

      /*
       Updates the player so it can plan its next move.
       */
      void update(const game_board& b) noexcept
      {
         m_traits.update(b);
      }

      /*
       Returns the player's unique ID.
       */
      uint32_t id() const noexcept
      {
         return m_id;
      }

      /*
       Returns the player's name.
       */
      const std::string& name() const noexcept
      {
         return m_name;
      }

      /*
       Returns the player's shape. Either X or O.
       */
      char shape() const noexcept
      {
         return m_shape;
      }

      ////////Assert that the traits template has the correct functions.////////
      static_assert(
         std::is_invocable_r_v<
            play, 
            decltype(&InputTraits::get), 
            InputTraits&>, 
         "InputTraits does not have \"play get() noexcept\"");

      static_assert(
         std::is_invocable_r_v<
            void, 
            decltype(&InputTraits::update), 
            InputTraits&, 
            const game_board& >,
         "InputTraits does not have \"void update(const game_board& b) noexcept\"");

      private:

      InputTraits m_traits;
      uint32_t m_id;
      std::string m_name;
      char m_shape;
   };
}