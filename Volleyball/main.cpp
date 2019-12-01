#include <QApplication>

#include <game.h>
#include <player.h>
#include <ball.h>

int main(int argc, char * argv[])
{
  QApplication volleyball(argc, argv);
  volleyball.setApplicationName("Volleyball");

  Game * game = new Game();

  game->start();

  return volleyball.exec();
}
