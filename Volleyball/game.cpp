#include <game.h>

#include <config.h>
#include <QDebug>

Game::Game() :
  scene(new QGraphicsScene()),
  view(new QGraphicsView(scene)),
  timer(new QTimer()),
  ball(new Ball()),
  player(new Player())
{
  view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  view->setFixedSize(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
  scene->setSceneRect(0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);

  scene->addItem(ball);
  scene->addItem(player);

  connect(timer, SIGNAL(timeout()), ball, SLOT(tick()));
  connect(timer, SIGNAL(timeout()), player, SLOT(tick()));
  connect(timer, SIGNAL(timeout()), this, SLOT(tick()));

  player->setFocus();
}

void Game::start()
{
  timer->start(Config::TIME);
  view->show();
}

void Game::tick()
{
  //qDebug() << "GAME";
}
