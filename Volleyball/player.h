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
  void setSpeedX(qreal speedX);
  void setSpeedY(qreal speedY);

public slots:
  void tick();
  void keyPress(QKeyEvent * event);
  void keyRelease(QKeyEvent * event);

private:
  std::size_t width_, height_;
  qreal speedX_, speedY_;
  bool isRight_, isLeft_, isUp_;
};

#endif // PLAYER_H
