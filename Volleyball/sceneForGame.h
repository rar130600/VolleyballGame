#ifndef SCENEFORGAME_H
#define SCENEFORGAME_H

#include <QGraphicsScene>
#include <QObject>

#include <player.h>

class SceneForGame : public QGraphicsScene
{
  Q_OBJECT
public:
  SceneForGame(Player * player1, Player * player2);

  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;
  void resetIsPauseGame();

signals:
  void keyPressPlayer1(QKeyEvent * event);
  void keyReleasePlayer1(QKeyEvent * event);
  void keyPressPlayer2(QKeyEvent * event);
  void keyReleasePlayer2(QKeyEvent * event);
  void gameEvent(QKeyEvent * event, bool isPause);

private:
  Player * player1_;
  Player * player2_;
  bool isPauseGame_;
};

#endif // SCENEFORGAME_H
