#ifndef BALL_H
#define BALL_H

#include <QGraphicsPixmapItem>
#include "entity.h"

class Ball : public Entity, public QGraphicsPixmapItem
{
  Q_OBJECT
public:
  Ball();

  void resetSpeeds();

signals:
  void startCalc();
  void stopCalc();
  void ballOnBottom(qreal x);

public slots:
  void tick() override;

private:
  qreal speedX_, speedY_;
  std::size_t diameter_;

  void move() override;
  void colliding() override;
  void checkMaxSpeed() override;
  void checkCollisionWithScene() override;
};

#endif // BALL_H
