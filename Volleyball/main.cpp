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
  player1->setFlag(QGraphicsItem::ItemIsFocusable);
  player1->setFocus();

  Ball * ball = new Ball();

  game->scene->addItem(player1);
  game->scene->addItem(ball);

  game->view->show();

  return volleyball.exec();
}
