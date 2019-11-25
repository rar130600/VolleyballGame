#include <game.h>

Game::Game()
{
  scene = new QGraphicsScene();
  view = new QGraphicsView(scene);

  view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  view->setFixedSize(800, 600);
  scene->setSceneRect(0, 0, 800, 600);
}
