#include <player.h>

#include <config.h>
#include "ball.h"
#include <QDebug>
#include <cmath>

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

  setFlag(QGraphicsItem::ItemIsFocusable);

  timer = new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
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
    if (y() >= Config::SCREEN_HEIGHT - Config::BOTTOM_INDENT - height)
    {
      isUp = true;
    }
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
    speedY = Config::GRAVITY * 21;
    isUp = false;
  }

  moveBy(speedX, -speedY);

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

void Player::colliding()
{
  QList<QGraphicsItem *> colliding_items = collidingItems(Qt::IntersectsItemShape);
  if (colliding_items.isEmpty())
  {
    return;
  }
  int n = colliding_items.size();
  for (int i = 0; i < n; i++)
  {
    auto item = colliding_items[i];
    if (typeid (* item) == typeid (Ball))
    {
      //qDebug() << "Colliding " << item->x() << " " << item->y();

    }
  }
}

qreal Player::getSpeedX()
{
  return speedX;
}

qreal Player::getSpeedY()
{
  return speedY;
}

void Player::tick()
{
  colliding();
  move();
}
