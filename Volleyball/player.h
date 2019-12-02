#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <entity.h>

class Player : public Entity, public QGraphicsPixmapItem
{
  Q_OBJECT
public:
  Player();

  qreal getSpeedX() const;
  qreal getSpeedY() const;
  void setSpeedX(qreal speedX);
  void setSpeedY(qreal speedY);

public slots:
  void tick() override;
  void keyPress(QKeyEvent * event);
  void keyRelease(QKeyEvent * event);

private:
  std::size_t width_, height_;
  qreal speedX_, speedY_;
  bool isRight_, isLeft_, isUp_;

protected:
  void move() override;
  void colliding() override;
  void checkMaxSpeed() override;
  void checkCollisionWithScene() override;
};

#endif // PLAYER_H
