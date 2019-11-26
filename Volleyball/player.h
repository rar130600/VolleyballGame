#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QTimer>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QKeyEvent>

class Player : public QObject, public QGraphicsRectItem
{
  Q_OBJECT
public:
  Player();

  void keyPressEvent(QKeyEvent * event);
  void keyReleaseEvent(QKeyEvent * event);
  void move();
  void colliding();

  qreal getSpeedX();
  qreal getSpeedY();

public slots:
  void tick();

public:
  std::size_t points;
  std::size_t width, height;
  qreal speedX, speedY;
  bool isRight, isLeft, isUp;
  QTimer * timer;
};

#endif // PLAYER_H
