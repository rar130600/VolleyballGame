#ifndef SCENEFORGAME_H
#define SCENEFORGAME_H

#include <QGraphicsScene>

#include <player.h>

class SceneForGame : public QGraphicsScene
{
  Q_OBJECT
public:
  SceneForGame(Player * player1, Player * player2);
  void start();
  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;

signals:
  void keyPressPlayer1(QKeyEvent * event);
  void keyReleasePlayer1(QKeyEvent * event);
  void keyPressPlayer2(QKeyEvent * event);
  void keyReleasePlayer2(QKeyEvent * event);

private:
  Player * player1_;
  Player * player2_;
};

#endif // SCENEFORGAME_H
