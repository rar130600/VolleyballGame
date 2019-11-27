#include "ball.h"

#include "config.h"
#include <QList>
#include <QDebug>
#include <cmath>
#include <math.h>
#include <QBrush>

Ball::Ball() :
  speedX_(0.0),
  speedY_(0.0),
  diameter_(Config::PLAYER_WIDTH)
{
  setBrush(QBrush(Qt::yellow));
  setRect(0, 0, diameter_, diameter_);
  setPos(Config::SCREEN_WIDTH / 2 - diameter_ / 2, Config::SCREEN_HEIGHT / 4);

}

void Ball::move()
{
  speedY_ -= Config::GRAVITY / 4;

  if (speedX_ > Config::BALL_X_MAX_SPEED)
  {
    speedX_ = Config::BALL_X_MAX_SPEED;
  }
  else if (speedX_ < -Config::BALL_X_MAX_SPEED)
  {
    speedX_ = -Config::BALL_X_MAX_SPEED;
  }

  if (speedY_ > Config::BALL_Y_MAX_SPEED)
  {
    speedY_ = Config::BALL_Y_MAX_SPEED;
  }
  else if (speedY_ < -Config::BALL_Y_MAX_SPEED)
  {
    speedY_ = -Config::BALL_Y_MAX_SPEED;
  }

  moveBy(speedX_, -speedY_);

  if (y() + diameter_ > Config::SCREEN_HEIGHT - Config::BOTTOM_INDENT)
  {
    setPos(x(), Config::SCREEN_HEIGHT - Config::BOTTOM_INDENT - diameter_);
    speedY_ = -speedY_ * Config::DRAG;
    speedX_ = speedX_ * Config::DRAG;
  }

  if (y() < 0)
  {
    setPos(x(), 0);
    speedY_ = -speedY_ * Config::DRAG;
    speedX_ = speedX_ * Config::DRAG;
  }

  if (x() < 0)
  {
    setPos(0, y());
    speedX_ = -speedX_ * Config::DRAG;
  }

  if (x() + diameter_ > Config::SCREEN_WIDTH)
  {
    setPos(Config::SCREEN_WIDTH - diameter_, y());
    speedX_ = -speedX_ * Config::DRAG;
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

      qDebug() << speedX_ << " " << speedY_;
      auto * player = static_cast<Player *>(item);

      qreal dx = x() - player->x();
      qreal dy = y() - player->y();
      qreal d = std::sqrt(dx * dx + dy * dy);

      qreal cos = dx / d;
      qreal sin = dy / d;

      qreal vn1 = player->getSpeedX() * cos + player->getSpeedY() * sin;
      qreal vn2 = speedX_ * cos + speedY_ * sin;
      qreal vt2 = speedX_ * sin + speedY_ * cos;

      qreal newVn2 = vn1 - vn2;

      speedX_ = newVn2 * cos - vt2 * sin;
      speedY_ = newVn2 * sin + vt2 * cos;

      if (player->getSpeedY() <= 0)
      {
        speedY_ = -speedY_;
      }

      qreal radiusPlayer = Config::PLAYER_WIDTH / 2;
      qreal radiusBall = diameter_ / 2;

      if (radiusPlayer + radiusBall > d)
      {
        moveBy(dx / 3, dy / 3);
        if (x() < 0 || x() + diameter_ > Config::SCREEN_WIDTH)
        {
          moveBy(-dx / 3, 0);
          speedX_ += -dx / 3;
        }
        if (y() + diameter_ > Config::SCREEN_HEIGHT + Config::BOTTOM_INDENT)
        {
          moveBy(0, -dy / 3);
          speedY_ += -dy / 3;
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
