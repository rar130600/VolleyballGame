#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>

struct Config
{
  constexpr static qreal GRAVITY = 0.5;
  constexpr static qreal DRAG = 0.9;
  constexpr static qreal BALL_MAX_SPEED_X = 10.0;
  constexpr static qreal BALL_MAX_SPEED_Y = 10.0;
  constexpr static qreal BALL_BOOST_X = 5.0;
  constexpr static qreal BALL_BOOST_Y = 5.0;

  constexpr static int TIME = 17; // ~60 fps
  constexpr static int BOTTOM_INDENT = 5;
  constexpr static std::size_t SCREEN_WIDTH = 1200;
  constexpr static std::size_t SCREEN_HEIGHT = 900;
  constexpr static std::size_t PLAYER_WIDTH = SCREEN_WIDTH / 16;
  constexpr static std::size_t PLAYER_HEIGHT = SCREEN_HEIGHT / 12;
};

#endif // CONFIG_H
