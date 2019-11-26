#include "ball.h"

#include "config.h"
#include <QList>
#include <QDebug>
#include <cmath>
#include <math.h>

Ball::Ball() :
  speedX(0.0),
  speedY(0.0),
  diameter(50)
{
  setRect(0, 0, diameter, diameter);
  setPos(Config::SCREEN_WIDTH / 2 - diameter / 2, Config::SCREEN_HEIGHT / 4);

  timer = new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
  timer->start(24);
}

void Ball::move()
{
  qreal oldY = y();
  qreal oldX = x();

  speedY -= Config::GRAVITY;

  if (speedX > Config::MAX_SPEED_X)
  {
    speedX = Config::MAX_SPEED_X;
  }
  else if (speedX < -Config::MAX_SPEED_X)
  {
    speedX = -Config::MAX_SPEED_X;
  }

  moveBy(speedX, -speedY);

  if (y() + diameter > Config::SCREEN_HEIGHT - Config::BOTTOM_INDENT)
  {
    setPos(x(), oldY);
    speedY = -speedY * Config::DRAG;
    speedX = speedX * Config::DRAG;
  }

  if (y() < 0)
  {
    setPos(x(), oldY);
    speedY = - speedY * Config::DRAG;
    speedX = speedX * Config::DRAG;
  }

  if (x() < 0)
  {
    setPos(oldX, y());
    speedX = - speedX * Config::DRAG;
  }

  if (x() + diameter > Config::SCREEN_WIDTH)
  {
    setPos(oldX, y());
    speedX = - speedX * Config::DRAG;
  }
}

void Ball::colliding()
{
  QList<QGraphicsItem *> colliding_items = collidingItems(Qt::IntersectsItemBoundingRect);
  int num = colliding_items.size();
  for (int i = 0; i < num; i++)
  {
    auto item = colliding_items[i];
    if (typeid(* item) == typeid(Player))
    {
      qDebug() << speedX << " " << speedY;
      auto * player = static_cast<Player *>(item);

      if (player->speedX >= 0 && speedX <= 0.0)
      {
        speedX = -(speedX - 5);
      }
      if (player->speedX <= 0 && speedX >= 0)
      {
        speedX = -(speedX + 5);
      }
      if (player->speedX >= 0 && speedX >= 0)
      {
        speedX += 5;
      }
      if (player->speedX <= 0 && speedX <= 0)
      {
        speedX -= 5;
      }

      if (player->speedY >= 0 && speedY <= 0)
      {
        speedY = -(speedY + 5);
      }
      if (player->speedY <= 0 && speedY >= 0)
      {
        speedY = -(speedY - 5);
      }
      if (player->speedY >= 0 && speedY >= 0)
      {
        speedY += 5;
      }
      if (player->speedY <= 0 && speedY <= 0)
      {
        speedY -= 5;
      }

      /*qreal radiusBall = diameter / 2;
      qreal radiusPlayer = player->width / 2;

      qreal dx = (x() + radiusBall) - (player->x() + radiusPlayer);
      qreal dy = (y() + radiusBall) - (player->y() + radiusPlayer);
      qreal distance = sqrt(dx*dx + dy*dy);

      qreal angle = atan2(dy, dx);

//      speedX = (cos(angle) * speedX) + (dy/distance);
//      speedY = (sin(angle) * speedY) + (dx/distance);
      if (distance == 0) {distance = 0.01;}

      qreal ax = dx/distance;
      qreal ay = dy/distance;

      if (distance < radiusBall + radiusPlayer)
      {
        qreal vn1 = player->speedX * ax + player->speedY * ay;
        qreal vn2 = speedX * ax + speedY * ay;
        qreal dt = (radiusBall + radiusPlayer - distance) / (vn1 - vn2);
        if (dt > 0.8) dt = 0.8; if (dt < -0.8) dt = -0.8;

        setPos(x() - speedX * dt, y() - speedY * dt);

        dx = x() - player->x();
        dy = y() - player->y();
        distance = sqrt(dx * dx + dy * dy);
        if (distance == 0) {distance = 0.01;}

        ax = dx/distance;
        ay = dy/distance * -1;

        vn1 = player->speedX * ax + player->speedY * ay;
        vn2 = speedX * ax + speedY * ay;

        qreal vt2 = -speedX * ay + speedY * ax;

        vn2 = vn1 - vn2;

        speedX = (vn2 * ax - vt2 * ay) * dt;
        speedY = (vn2 * ay + vt2 * ax) * dt;
      }*/
    }
  }
}

void Ball::tick()
{
  colliding();
  move();
}
