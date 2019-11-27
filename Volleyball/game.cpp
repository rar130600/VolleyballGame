#include <game.h>

#include <config.h>
#include <QDebug>

Game::Game() :
  ball(new Ball()),
  player1(new Player()),
  player2(new Player()),
  scene(new SceneForGame(player1, player2)),
  view(new QGraphicsView(scene)),
  timer(new QTimer())
{
  view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  view->setFixedSize(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
  scene->setSceneRect(0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);

  player1->setPos(Config::SCREEN_WIDTH / 4 - Config::PLAYER_WIDTH / 2, Config::SCREEN_HEIGHT - Config::PLAYER_HEIGHT - Config::BOTTOM_INDENT);
  player2->setPos(3 * (Config::SCREEN_WIDTH / 4) - Config::PLAYER_WIDTH / 2, Config::SCREEN_HEIGHT - Config::PLAYER_HEIGHT - Config::BOTTOM_INDENT);

  scene->addItem(ball);
  scene->addItem(player1);
  scene->addItem(player2);

  scene->start();

  connect(timer, SIGNAL(timeout()), ball, SLOT(tick()));
  connect(timer, SIGNAL(timeout()), player1, SLOT(tick()));
  connect(timer, SIGNAL(timeout()), player2, SLOT(tick()));
  connect(timer, SIGNAL(timeout()), this, SLOT(tick()));

  connect(ball, SIGNAL(startCalc()), timer, SLOT(stop()));
  connect(ball, SIGNAL(stopCalc()), timer, SLOT(start()));
}

void Game::start()
{
  timer->start(Config::TIME);
  view->show();
}

void Game::tick()
{

}
