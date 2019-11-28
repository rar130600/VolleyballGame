#ifndef BALL_H
#define BALL_H

#include <QGraphicsEllipseItem>
#include <QObject>

class Ball : public QObject, public QGraphicsEllipseItem
{
  Q_OBJECT
public:
  Ball();

  void move();
  void colliding();
signals:
  void startCalc();
  void stopCalc();

public slots:
  void tick();

private:
  qreal speedX_, speedY_;
  std::size_t diameter_;
};

#endif // BALL_H
