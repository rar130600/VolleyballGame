#include "ball.h"

#include <QList>
#include <cmath>

#include "config.h"
#include "player.h"
#include "net.h"

Ball::Ball() :
  speedX_(0.0),
  speedY_(0.0),
  diameter_(Config::BALL_DIAMETER)
{
  QPixmap image;
  image.load(":/images/resource/ball.png");
  setPixmap(image.scaled(static_cast<int>(diameter_), static_cast<int>(diameter_), Qt::KeepAspectRatio));
}

void Ball::move()
{
  speedY_ -= Config::BALL_Y_GRAVITY;

  checkMaxSpeed();

  //если скорость мяча слишком маленькая, то сбрасываем
  if (std::abs(speedX_) < 0.01)
  {
    speedX_ = 0.0;
  }
  if (std::abs(speedY_) < 0.01)
  {
    speedY_ = 0.0;
  }

  //двигаем мяч
  moveBy(speedX_, -speedY_);


  checkCollisionWithScene();
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
      auto * player = static_cast<Player *>(item);

      //считаем угол и скорость отскока
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

      //если игрок не в прыжке
      if (player->getSpeedY() <= 0)
      {
        speedY_ = -speedY_ * Config::DRAG;
      }

      //останавливаем игрока после удара мяча
      player->setSpeedX(0.0);
      player->setSpeedY(0.0);

      qreal radiusPlayer = Config::PLAYER_HEIGHT / 2;
      qreal radiusBall = diameter_ / 2;

      //если мяч внутри игрока (возникает из-за большой скорости мяча)
      if (radiusPlayer + radiusBall > d)
      {
          //если мяч ниже игрока, то выталкиваем мяч наверх
          if (y() > player->y())
          {
            dy = -dy;
          }

          //выталкиваем мяч
          moveBy(dx / 6 , dy / 6);

          checkCollisionWithScene();
      }
    }

    if (typeid(* item) == typeid(Net))
    {
      auto * net = static_cast<Net *>(item);

      //если мяч на уровне с сеткой
      if (y() + diameter_ - 5 > net->y())
      {
        //если мяч прилетел слева
        if ( x() < item->x())
        {
          setPos(net->x() - diameter_ - 10, y());
        }
        else if (speedX_ <= 0.0 && x() > item->x()) //если - слева
        {
          setPos(net->x() + Config::NET_WIDTH + 10, y());
        }
      }
      else
      {
        setPos(x(), y() + speedY_);
        speedY_ = -speedY_ * Config::DRAG;
      }

      speedX_ = -speedX_ * Config::DRAG;
    }
  }
}

void Ball::resetSpeeds()
{
  speedY_ = 0.0;
  speedX_ = 0.0;
}

void Ball::tick()
{
  emit startCalc();

  colliding();
  move();

  emit stopCalc();
}

void Ball::checkMaxSpeed()
{
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
}

void Ball::checkCollisionWithScene()
{
  //если столкновение с низом сцены
  if (y() + diameter_ > Config::SCREEN_HEIGHT - Config::INDENT)
  {
    //устанавливаем мяч в максимально возможную нижнюю точку
    setPos(x(), Config::SCREEN_HEIGHT - Config::INDENT - diameter_);
    //вызываем сигнал
    emit ballOnBottom(x());
  }

  //если столкновение с верхом сцены
  if (y() < 0)
  {
    //устанавливаем мяч в максимально возможную верхнюю точку
    setPos(x(), 0.0);
    //рассчитываем скорость
    speedY_ = -speedY_ * Config::DRAG;
    speedX_ = speedX_ * Config::DRAG;
  }

  //если столкновение с левой стороной сцены
  if (x() < 0)
  {
    //устанавливаем мяч в максимально возможную левую точку
    setPos(0.0, y());
    //рассчитываем скорость
    speedX_ = -speedX_ * Config::DRAG;
  }

  //если столкновение с правой стороной сцены
  if (x() + diameter_ > Config::SCREEN_WIDTH)
  {
    //устанавливаем мяч в максимально возможную правую точку
    setPos(Config::SCREEN_WIDTH - diameter_, y());
    //расчитываем скорость
    speedX_ = -speedX_ * Config::DRAG;
  }
}
