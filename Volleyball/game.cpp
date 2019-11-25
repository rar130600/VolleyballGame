#include <game.h>

#include <config.h>

Game::Game()
{
  scene = new QGraphicsScene();
  view = new QGraphicsView(scene);
  timer = new QTimer();

  connect(timer, SIGNAL(timeout()), this, SLOT(tick()));

  view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  view->setFixedSize(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
  scene->setSceneRect(0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);

  timer->start(24);
}

void Game::addItem(QGraphicsItem * item)
{
  scene->addItem(item);
}

void Game::viewShow()
{
  view->show();
}

void Game::tick()
{

}
