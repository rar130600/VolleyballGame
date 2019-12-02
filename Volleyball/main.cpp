#include <QApplication>

#include <game.h>

int main(int argc, char * argv[])
{
  QApplication volleyball(argc, argv);
  volleyball.setApplicationName("Volleyball");

  Game * game = new Game();

  game->start();

  return volleyball.exec();
}
