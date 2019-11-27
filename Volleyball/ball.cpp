#include "ball.h"

#include "config.h"
#include <QList>
#include <QDebug>
#include <cmath>
#include <math.h>
#include <QBrush>

Ball::Ball() :
  speedX(0.0),
  speedY(0.0),
  diameter(Config::PLAYER_WIDTH)
{
  setBrush(QBrush(Qt::yellow));
  setRect(0, 0, diameter, diameter);
  setPos(Config::SCREEN_WIDTH / 2 - diameter / 2, Config::SCREEN_HEIGHT / 4);

}

void Ball::move()
{
  speedY -= Config::GRAVITY / 4;

  if (speedX > Config::BALL_X_MAX_SPEED)
  {
    speedX = Config::BALL_X_MAX_SPEED;
  }
  else if (speedX < -Config::BALL_X_MAX_SPEED)
  {
    speedX = -Config::BALL_X_MAX_SPEED;
  }

  if (speedY > Config::BALL_Y_MAX_SPEED)
  {
    speedY = Config::BALL_Y_MAX_SPEED;
  }
  else if (speedY < -Config::BALL_Y_MAX_SPEED)
  {
    speedY = -Config::BALL_Y_MAX_SPEED;
  }

  moveBy(speedX, -speedY);

  if (y() + diameter > Config::SCREEN_HEIGHT - Config::BOTTOM_INDENT)
  {
    setPos(x(), Config::SCREEN_HEIGHT - Config::BOTTOM_INDENT - diameter);
    speedY = -speedY * Config::DRAG;
    speedX = speedX * Config::DRAG;
  }

  if (y() < 0)
  {
    setPos(x(), 0);
    speedY = - speedY * Config::DRAG;
    speedX = speedX * Config::DRAG;
  }

  if (x() < 0)
  {
    setPos(0, y());
    speedX = - speedX * Config::DRAG;
  }

  if (x() + diameter > Config::SCREEN_WIDTH)
  {
    setPos(Config::SCREEN_WIDTH - diameter, y());
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

      qreal dx = x() - player->x();
      qreal dy = y() - player->y();
      qreal d = std::sqrt(dx * dx + dy * dy);

      qreal cos = dx / d;
      qreal sin = dy / d;

      qreal vn1 = player->getSpeedX() * cos + player->getSpeedY() * sin;
      qreal vn2 = speedX * cos + speedY * sin;
      qreal vt2 = speedX * sin + speedY * cos;

      qreal newVn2 = vn1 - vn2;

      speedX = newVn2 * cos - vt2 * sin;
      speedY = newVn2 * sin + vt2 * cos;

      if (player->getSpeedY() <= 0)
      {
        speedY = - speedY;
      }

      qreal radiusPlayer = Config::PLAYER_WIDTH / 2;
      qreal radiusBall = diameter / 2;

      if (radiusPlayer + radiusBall > d)
      {
        moveBy(dx / 3, dy / 3);
        if (x() < 0 || x() + diameter > Config::SCREEN_WIDTH)
        {
          moveBy(-dx / 3, 0);
          speedX += -dx / 3;
        }
        if (y() + diameter > Config::SCREEN_HEIGHT + Config::BOTTOM_INDENT)
        {
          moveBy(0, -dy / 3);
          speedY += -dy / 3;
        }
      }

      // does not work well
      /*if (player->getSpeedX() >= 0 && speedX <= 0.0)
      {
        speedX = -(speedX - Config::BALL_BOOST_X - player->getSpeedX());
      }
      if (player->getSpeedX() <= 0 && speedX >= 0)
      {
        speedX = -(speedX + Config::BALL_BOOST_X + player->getSpeedX());
      }
      if (player->getSpeedX() >= 0 && speedX >= 0)
      {
        if (player->x() < x())
        {
          speedX += (Config::BALL_BOOST_X + player->getSpeedX());
        }
        else if (player->x() >= x() + diameter)
        {
          speedX = -(speedX + Config::BALL_BOOST_X + player->getSpeedX());
        }
      }
      if (player->getSpeedX() <= 0 && speedX <= 0)
      {
        if (player->x() >= x() + diameter)
        {
          speedX -= (Config::BALL_BOOST_X + player->getSpeedX());
        }
        else if (player->x() <= x())
        {
          speedX = -(speedX - Config::BALL_BOOST_X - player->getSpeedX());
        }
      }

      if (player->getSpeedY() >= 0 && speedY <= 0)
      {
        speedY = -(speedY - Config::BALL_BOOST_Y - player->getSpeedY());
      }
      if (player->getSpeedY() <= 0 && speedY >= 0)
      {
        speedY = -(speedY + Config::BALL_BOOST_Y + player->getSpeedY());
      }
      if (player->getSpeedY() > 0 && speedY >= 0)
      {
        speedY += (Config::BALL_BOOST_Y + player->getSpeedY());
      }
      if (player->getSpeedY() < 0 && speedY <= 0)
      {
        speedY -= (Config::BALL_BOOST_Y + player->getSpeedY());
      }*/
    }
  }
}

void Ball::tick()
{
  emit startCalc();

  colliding();
  move();

  emit stopCalc();
}
