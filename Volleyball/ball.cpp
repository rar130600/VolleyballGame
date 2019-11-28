#include "ball.h"

#include <QList>
#include <QDebug>
#include <cmath>

#include "config.h"
#include "player.h"
#include "net.h"

Ball::Ball() :
  speedX_(0.0),
  speedY_(0.0),
  diameter_(Config::BALL_DIAMETER)
{
  setRect(0, 0, diameter_, diameter_);
}

void Ball::move()
{
  speedY_ -= Config::BALL_Y_GRAVITY;

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

  if (y() + diameter_ > Config::SCREEN_HEIGHT - Config::INDENT)
  {
    setPos(x(), Config::SCREEN_HEIGHT - Config::INDENT - diameter_);
    /*speedY_ = -speedY_ * Config::DRAG;
    speedX_ = speedX_ * Config::DRAG;*/
    speedY_ = 0.0;
    speedX_ = 0.0;
    emit ballOnBottom(x());
  }

  if (y() < 0)
  {
    setPos(x(), 0.0);
    speedY_ = -speedY_ * Config::DRAG;
    speedX_ = speedX_ * Config::DRAG;
  }

  if (x() < 0)
  {
    setPos(0.0, y());
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

      qDebug() << "Ball colliding with Player " << speedX_ << " " << speedY_;
      auto * player = static_cast<Player *>(item);

      qreal dx = x() - player->x();
      qreal dy = y() - player->y();
      qreal d = std::sqrt(dx * dx + dy * dy);

      qreal cos = dx / d;
      qreal sin = dy / d;

      qreal vn1 = player->getSpeedX() * cos + player->getSpeedY() * sin;
      qreal vn2 = speedX_ * cos + speedY_ * sin;
      qreal vt2 = -speedX_ * sin + speedY_ * cos;

      qreal newVn2 = vn1 - vn2;

      speedX_ = newVn2 * cos - vt2 * sin;
      speedY_ = newVn2 * sin + vt2 * cos;

      if (player->getSpeedY() <= 0)
      {
        speedY_ = -speedY_ * Config::DRAG;
      }

      player->setSpeedX(0.0);
      player->setSpeedY(0.0);

      qreal radiusPlayer = Config::PLAYER_WIDTH / 2;
      qreal radiusBall = diameter_ / 2;

      if (radiusPlayer + radiusBall > d)
      {
          if (y() > player->y())
          {
            dy = -dy;
          }
          moveBy(dx / 6 , dy / 6);
          if (x() < 0 || x() + diameter_ > Config::SCREEN_WIDTH)
          {
            moveBy(-dx / 6, 0.0);
            speedX_ += -dx / 6;
          }
          if (y() + diameter_ > Config::SCREEN_HEIGHT + Config::INDENT)
          {
            moveBy(0.0, -dy / 6);
            speedY_ += -dy / 6;
          }

      }
    }

    if (typeid(* item) == typeid(Net))
    {
      qDebug() << "Ball colliding with Net " << speedX_ << " " << speedY_;
      auto * net = static_cast<Net *>(item);

      if (y() + diameter_ - 5 > net->y())
      {
        if (speedX_ < 0)
        {
          setPos(net->x() + Config::NET_WIDTH + 10, y());
        }
        if (speedX_ > 0)
        {
          setPos(net->x() - diameter_ - 10, y());
        }
      }
      else
      {
        speedY_ = -speedY_ * Config::DRAG * 2;
      }

      speedX_ = -speedX_ * Config::DRAG * 2;
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
