#include <player.h>

#include <QDebug>
#include <cmath>

#include "config.h"
#include "ball.h"
#include "net.h"

Player::Player() :
  width_(Config::PLAYER_WIDTH),
  height_(Config::PLAYER_HEIGHT),
  speedX_(0.0),
  speedY_(0.0),
  isRight_(false),
  isLeft_(false),
  isUp_(false)
{
  setRect(0, 0, width_, height_);
}

void Player::keyPress(QKeyEvent * event)
{
  switch(event->key())
  {
  case Qt::Key_Left:
  case Qt::Key_A:
    isLeft_ = true;
    break;
  case Qt::Key_Right:
  case Qt::Key_D:
    isRight_ = true;
    break;
  case Qt::Key_Up:
  case Qt::Key_W:
    if (y() >= Config::SCREEN_HEIGHT - Config::INDENT - height_)
    {
      isUp_ = true;
    }
    break;
  }
}

void Player::keyRelease(QKeyEvent * event)
{
  switch (event->key())
  {
  case Qt::Key_Left:
  case Qt::Key_A:
    isLeft_ = false;
    break;
  case Qt::Key_Right:
  case Qt::Key_D:
    isRight_ = false;
    break;
  }
}

void Player::move()
{
  if (isLeft_)
  {
    speedX_ = -Config::PLAYER_X_BOOST;
  }
  if (isRight_)
  {
    speedX_ = Config::PLAYER_X_BOOST;
  }
  if (isUp_)
  {
    speedY_ = Config::PLAYER_Y_BOOST;
    isUp_ = false;
  }

  speedY_ -= Config::PLAYER_Y_GRAVITY;

  if (speedX_ < 0.0)
  {
    speedX_ += Config::PLAYER_X_GRAVITY;
  }
  else if (speedX_ > 0.0)
  {
    speedX_ -= Config::PLAYER_X_GRAVITY;
  }
  if (std::abs(speedX_) < 0.01)
  {
    speedX_ = 0.0;
  }

  if (speedY_ < -Config::PLAYER_Y_BOOST)
  {
    speedY_ = -Config::PLAYER_Y_BOOST;
  }
  if (speedY_ > Config::PLAYER_Y_BOOST)
  {
    speedY_ = Config::PLAYER_Y_BOOST;
  }

  moveBy(speedX_, -speedY_);


  //collision with Scene
  if (y() + height_ > Config::SCREEN_HEIGHT - Config::INDENT)
  {
    setPos(x(), Config::SCREEN_HEIGHT - Config::INDENT - height_);
  }

  if (x() < 0)
  {
    setPos(0, y());
  }
  if (x() + width_ > Config::SCREEN_WIDTH)
  {
    setPos(Config::SCREEN_WIDTH - width_, y());
  }
}

void Player::colliding()
{
  QList<QGraphicsItem *> colliding_items = collidingItems(Qt::IntersectsItemBoundingRect);
  int num = colliding_items.size();
  for (int i = 0; i < num; i++)
  {
    auto item = colliding_items[i];

    if (typeid(* item) == typeid (Net))
    {
      qDebug() << "Player colliding with Net " << speedX_ << " " << speedY_;

      if (speedX_ > 0.0)
      {
        setPos(((Config::SCREEN_WIDTH - Config::NET_WIDTH) / 2) - width_ - 1, y());
      }
      else if (speedX_ < 0.0)
      {
        setPos((Config::SCREEN_WIDTH + Config::NET_WIDTH) / 2 + 1, y());
      }

      speedX_ = 0.0;
    }
  }
}

qreal Player::getSpeedX() const
{
  return speedX_;
}

qreal Player::getSpeedY() const
{
  return speedY_;
}

void Player::setSpeedX(qreal speedX)
{
  speedX_ = speedX;
}

void Player::setSpeedY(qreal speedY)
{
  speedY_ = speedY;
}

void Player::tick()
{
  colliding();
  move();
}
