#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>

#include <game.h>
#include <player.h>
#include <ball.h>

int main(int argc, char * argv[])
{
  QApplication volleyball(argc, argv);
  volleyball.setApplicationName("Volleyball");

  Game * game = new Game();

  Player * player1 = new Player();
  player1->setFocus();

  Ball * ball = new Ball();

  game->addItem(player1);
  game->addItem(ball);

  game->viewShow();

  return volleyball.exec();
}
