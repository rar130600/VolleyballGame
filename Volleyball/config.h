#ifndef CONFIG_H
#define CONFIG_H

#include <QObject>

struct Config
{
  constexpr static qreal GRAVITY = 1.5;
  constexpr static qreal DRAG = 0.9;
  constexpr static int TIME = 24;
  constexpr static int BOTTOM_INDENT = 5;
  constexpr static int SCREEN_WIDTH = 800;
  constexpr static int SCREEN_HEIGHT = 600;

};

#endif // CONFIG_H
