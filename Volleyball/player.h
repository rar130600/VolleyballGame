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

private:
  std::size_t points;
  QTimer * timer;
};

#endif // PLAYER_H
