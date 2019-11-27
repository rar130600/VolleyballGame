#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsView>
#include <QTimer>

#include <ball.h>
#include <player.h>
#include <sceneForGame.h>

class Game : public QWidget
{
  Q_OBJECT
public:
  Game();

  void start();

public slots:
  void tick();

private:
  Ball * ball;
  Player * player1;
  Player * player2;

  SceneForGame * scene;
  QGraphicsView * view;
  QTimer * timer;
};

#endif // GAME_H
