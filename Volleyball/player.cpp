#include <player.h>

#include <config.h>

Player::Player() :
  points(0),
  width(50),
  height(50),
  speedX(0.0),
  speedY(0.0),
  isRight(false),
  isLeft(false),
  isUp(false)
{
  setRect(0, 0, width, height);
  setPos(Config::SCREEN_WIDTH / 4 - width / 2, Config::SCREEN_HEIGHT - height - Config::BOTTOM_INDENT);

  timer = new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(move()));
  timer->start(Config::TIME);
}

void Player::keyPressEvent(QKeyEvent * event)
{
  switch(event->key())
  {
  case Qt::Key_Left:
    isLeft = true;
    break;
  case Qt::Key_Right:
    isRight = true;
    break;
  case Qt::Key_Up:
    isUp = true;
    break;
  }
}

void Player::keyReleaseEvent(QKeyEvent * event)
{
  switch (event->key())
  {
  case Qt::Key_Left:
    isLeft = false;
    break;
  case Qt::Key_Right:
    isRight = false;
    break;
  }
}

void Player::move()
{
  qreal oldY = y();
  qreal oldX = x();

  speedY -= Config::GRAVITY;

  if (isLeft)
  {
    speedX = -Config::GRAVITY * 7;
  }
  if (isRight)
  {
    speedX = Config::GRAVITY * 7;
  }
  if (isUp)
  {
    speedY = 30.0;
    isUp = false;
  }

  setPos(x() + speedX, y() - speedY);

  if (speedX < 0)
  {
    speedX += Config::GRAVITY;
  }
  else if (speedX > 0)
  {
    speedX -= Config::GRAVITY;
  }

  if (y() + height > Config::SCREEN_HEIGHT - Config::BOTTOM_INDENT)
  {
    setPos(x(), oldY);
  }

  if (x() < 0)
  {
    setPos(oldX, y());
  }
  if (x() + width > Config::SCREEN_WIDTH)
  {
    setPos(oldX, y());
  }
}
