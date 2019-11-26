#ifndef BALL_H
#define BALL_H

#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QObject>
#include <QTimer>
#include <player.h>

class Ball : public QObject, public QGraphicsEllipseItem
{
  Q_OBJECT
public:
  Ball();

  void move();
  void colliding();

public slots:
  void tick();

private:
  qreal speedX, speedY;
  int diameter;
  QTimer * timer;
};

#endif // BALL_H
