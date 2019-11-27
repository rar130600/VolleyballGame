#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>

struct Config
{
  constexpr static qreal GRAVITY = 0.3;
  constexpr static qreal DRAG = 0.5;

  constexpr static int TIME = 17; // ~60 fps
  constexpr static int BOTTOM_INDENT = 5;
  constexpr static std::size_t SCREEN_WIDTH = 1200;
  constexpr static std::size_t SCREEN_HEIGHT = 900;

  constexpr static qreal BALL_X_MAX_SPEED = 15.0;
  constexpr static qreal BALL_Y_MAX_SPEED = 15.0;
  constexpr static qreal BALL_X_BOOST = 1.0;
  constexpr static qreal BALL_Y_BOOST = 1.0;

  constexpr static qreal PLAYER_X_GRAVITY = GRAVITY;
  constexpr static qreal PLAYER_Y_GRAVITY = GRAVITY * 4;
  constexpr static qreal PLAYER_X_BOOST = GRAVITY * 32;
  constexpr static qreal PLAYER_Y_BOOST = GRAVITY * 106;
  constexpr static std::size_t PLAYER_WIDTH = SCREEN_WIDTH / 16;
  constexpr static std::size_t PLAYER_HEIGHT = SCREEN_HEIGHT / 12;
};

#endif // CONFIG_H
