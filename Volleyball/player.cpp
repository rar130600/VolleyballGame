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

  speedY -= Config::GRAVITY * 2;

  if (isLeft)
  {
    speedX = -Config::GRAVITY * 16;
  }
  if (isRight)
  {
    speedX = Config::GRAVITY * 16;
  }
  if (isUp)
  {
    speedY = Config::GRAVITY * 56;
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
