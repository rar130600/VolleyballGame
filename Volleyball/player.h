#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QTimer>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QKeyEvent>

class Player : public QObject, public QGraphicsEllipseItem
{
  Q_OBJECT
public:
  Player();


  void move();
  void colliding();

  qreal getSpeedX() const;
  qreal getSpeedY() const;

public slots:
  void tick();
  void keyPress(QKeyEvent * event);
  void keyRelease(QKeyEvent * event);

private:
  std::size_t width, height;
  qreal speedX, speedY;
  bool isRight, isLeft, isUp;
};

#endif // PLAYER_H
