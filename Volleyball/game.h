#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>

#include <ball.h>
#include <player.h>


class Game : public QWidget
{
  Q_OBJECT
public:
  Game();

  void start();

public slots:
  void tick();

private:
  QGraphicsScene * scene;
  QGraphicsView * view;
  QTimer * timer;

  Ball * ball;
  Player  * player;
};

#endif // GAME_H
