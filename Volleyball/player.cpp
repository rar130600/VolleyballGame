#include <player.h>

#include <config.h>
#include "ball.h"
#include <QDebug>
#include <QBrush>

Player::Player() :
  width_(Config::PLAYER_WIDTH),
  height_(Config::PLAYER_HEIGHT),
  speedX_(0.0),
  speedY_(0.0),
  isRight_(false),
  isLeft_(false),
  isUp_(false)
{
  setBrush(QBrush(Qt::darkGray));
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
    if (y() >= Config::SCREEN_HEIGHT - Config::BOTTOM_INDENT - height_)
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
  speedY_ -= Config::PLAYER_Y_GRAVITY;

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

  moveBy(speedX_, -speedY_);

  if (speedX_ < 0)
  {
    speedX_ += Config::PLAYER_X_GRAVITY;
  }
  else if (speedX_ > 0)
  {
    speedX_ -= Config::PLAYER_X_GRAVITY;
  }

  if (y() + height_ > Config::SCREEN_HEIGHT - Config::BOTTOM_INDENT)
  {
    setPos(x(), Config::SCREEN_HEIGHT - Config::BOTTOM_INDENT - height_);
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

}

qreal Player::getSpeedX() const
{
  return speedX_;
}

qreal Player::getSpeedY() const
{
  return speedY_;
}

void Player::tick()
{
  colliding();
  move();
}
