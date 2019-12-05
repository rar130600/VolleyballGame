#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsView>
#include <QTimer>
#include <map>
#include <QTime>
#include <string>

#include "ball.h"
#include "player.h"
#include "sceneForGame.h"
#include "net.h"
#include "rules.h"

class Game : public QWidget
{
  Q_OBJECT
public:
  Game();

  void start();

public slots:
  void tick();
  void ballOnBottom(qreal x);
  void gameEvent(QKeyEvent * event, bool isPause);

private:
  Ball * ball_;
  Player * player1_;
  Player * player2_;
  Net * net_;
  QGraphicsRectItem * backgroundPause_;
  QGraphicsRectItem * backgroundTable_;

  SceneForGame * scene_;
  QGraphicsView * view_;
  QTimer * timer_;
  Rules * rules_;
  std::map<QTime, std::string> timeScore_;
  QGraphicsTextItem * textScoreTime_;
  bool tableInScene_;

  void setDefaultPositionPlayers();
  void setDefaultPositionBall();
};

#endif // GAME_H
