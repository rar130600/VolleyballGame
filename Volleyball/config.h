#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>

namespace Config
{
  constexpr static qreal GRAVITY = 0.3;
  constexpr static qreal DRAG = 0.8;

  constexpr static int TIME = 17; // ~60 fps
  constexpr static int INDENT = 5;
  constexpr static std::size_t SCREEN_WIDTH = 1200;
  constexpr static std::size_t SCREEN_HEIGHT = 900;

  constexpr static std::size_t SCORE_FOR_WINNING = 5;

  constexpr static std::size_t TEXT_SIZE_SCORE = 24;
  constexpr static std::size_t TEXT_SIZE_INFO = 36;

  constexpr static qreal BALL_Y_GRAVITY = GRAVITY / 4;
  constexpr static qreal BALL_X_BOOST = 1.0;
  constexpr static qreal BALL_Y_BOOST = 1.0;
  constexpr static qreal BALL_X_MAX_SPEED = 14.0;
  constexpr static qreal BALL_Y_MAX_SPEED = 14.0;
  constexpr static std::size_t BALL_DIAMETER = SCREEN_WIDTH / 16;

  constexpr static qreal PLAYER_X_GRAVITY = GRAVITY;
  constexpr static qreal PLAYER_Y_GRAVITY = GRAVITY * 4;
  constexpr static qreal PLAYER_X_BOOST = GRAVITY * 32;
  constexpr static qreal PLAYER_Y_BOOST = GRAVITY * 110;
  constexpr static std::size_t PLAYER_WIDTH = 120;
  constexpr static std::size_t PLAYER_HEIGHT = 200;

  constexpr static std::size_t NET_WIDTH = 10;
  constexpr static std::size_t NET_HEIGHT = SCREEN_HEIGHT / 2;
};

#endif // CONFIG_H
