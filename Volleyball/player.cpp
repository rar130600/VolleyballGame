#include <player.h>

#include <config.h>
#include "ball.h"
#include <QDebug>
#include <QBrush>

Player::Player() :
  width(Config::PLAYER_WIDTH),
  height(Config::PLAYER_HEIGHT),
  speedX(0.0),
  speedY(0.0),
  isRight(false),
  isLeft(false),
  isUp(false)
{
  setBrush(QBrush(Qt::darkGray));
  setRect(0, 0, width, height);
}

void Player::keyPress(QKeyEvent * event)
{
  switch(event->key())
  {
  case Qt::Key_Left:
  case Qt::Key_A:
    isLeft = true;
    break;
  case Qt::Key_Right:
  case Qt::Key_D:
    isRight = true;
    break;
  case Qt::Key_Up:
  case Qt::Key_W:
    if (y() >= Config::SCREEN_HEIGHT - Config::BOTTOM_INDENT - height)
    {
      isUp = true;
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
    isLeft = false;
    break;
  case Qt::Key_Right:
  case Qt::Key_D:
    isRight = false;
    break;
  }
}

void Player::move()
{
  speedY -= Config::PLAYER_Y_GRAVITY;

  if (isLeft)
  {
    speedX = -Config::PLAYER_X_BOOST;
  }
  if (isRight)
  {
    speedX = Config::PLAYER_X_BOOST;
  }
  if (isUp)
  {
    speedY = Config::PLAYER_Y_BOOST;
    isUp = false;
  }

  moveBy(speedX, -speedY);

  if (speedX < 0)
  {
    speedX += Config::PLAYER_X_GRAVITY;
  }
  else if (speedX > 0)
  {
    speedX -= Config::PLAYER_X_GRAVITY;
  }

  if (y() + height > Config::SCREEN_HEIGHT - Config::BOTTOM_INDENT)
  {
    setPos(x(), Config::SCREEN_HEIGHT - Config::BOTTOM_INDENT - height);
  }

  if (x() < 0)
  {
    setPos(0, y());
  }
  if (x() + width > Config::SCREEN_WIDTH)
  {
    setPos(Config::SCREEN_WIDTH - width, y());
  }
}

void Player::colliding()
{

}

qreal Player::getSpeedX() const
{
  return speedX;
}

qreal Player::getSpeedY() const
{
  return speedY;
}

void Player::tick()
{
  colliding();
  move();
}
