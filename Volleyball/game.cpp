#include <game.h>

#include <config.h>

Game::Game()
{
  scene = new QGraphicsScene();
  view = new QGraphicsView(scene);

  view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  view->setFixedSize(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
  scene->setSceneRect(0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
}
