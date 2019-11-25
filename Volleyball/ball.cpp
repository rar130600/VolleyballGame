#include "ball.h"

Ball::Ball()
{
  speedX = 10.0;
  speedY = 0.0;
  diameter = 50;

  setRect(0, 0, diameter, diameter);

  timer = new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(move()));
  timer->start(24);
}

void Ball::move()
{
  qreal oldY = y();
  qreal oldX = x();

  speedY -= GRAVITY;

  setPos(x() + speedX, y() - speedY);

  if (y() + diameter > 600 - 5)
  {
    setPos(x(), oldY);
    speedY = -speedY * DRAG;
    speedX = speedX * DRAG;
  }

  if (x() < 0)
  {
    setPos(oldX, y());
    speedX = - speedX;
  }

  if (x() + diameter > 800)
  {
    setPos(oldX, y());
    speedX = - speedX;
  }
}
