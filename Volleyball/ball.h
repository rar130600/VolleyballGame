#ifndef BALL_H
#define BALL_H

#include <QGraphicsEllipseItem>
#include <QObject>
#include <QTimer>

const qreal GRAVITY = 1.85;
const qreal DRAG = 0.9;

class Ball : public QObject, public QGraphicsEllipseItem
{
  Q_OBJECT
public:
  Ball();
public slots:
  void move();

private:
  QTimer * timer;
  qreal speedX, speedY;
  int diameter;
};

#endif // BALL_H
