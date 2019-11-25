#include "ball.h"

#include "config.h"

Ball::Ball() :
  speedX(0.0),
  speedY(0.0),
  diameter(50)
{
  setRect(0, 0, diameter, diameter);
  setPos(Config::SCREEN_WIDTH / 2 - diameter / 2, Config::SCREEN_HEIGHT / 4);

  timer = new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(move()));
  timer->start(24);
}

void Ball::move()
{
  qreal oldY = y();
  qreal oldX = x();

  speedY -= Config::GRAVITY;

  setPos(x() + speedX, y() - speedY);

  if (y() + diameter > Config::SCREEN_HEIGHT - Config::BOTTOM_INDENT)
  {
    setPos(x(), oldY);
    speedY = -speedY * Config::DRAG;
    speedX = speedX * Config::DRAG;
  }

  if (x() < 0)
  {
    setPos(oldX, y());
    speedX = - speedX;
  }

  if (x() + diameter > Config::SCREEN_WIDTH)
  {
    setPos(oldX, y());
    speedX = - speedX;
  }
}
