#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsView>
#include <QTimer>

#include <ball.h>
#include <player.h>
#include <sceneForGame.h>
#include <net.h>

class Game : public QWidget
{
  Q_OBJECT
public:
  Game();

  void start();

public slots:
  void tick();

private:
  Ball * ball_;
  Player * player1_;
  Player * player2_;
  Net * net_;

  SceneForGame * scene_;
  QGraphicsView * view_;
  QTimer * timer_;
};

#endif // GAME_H
