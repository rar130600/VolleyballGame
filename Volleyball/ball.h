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
  std::size_t diameter;
};

#endif // BALL_H
