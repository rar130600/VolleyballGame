#include <game.h>

#include <config.h>
#include <QDebug>

Game::Game() :
  ball_(new Ball()),
  player1_(new Player()),
  player2_(new Player()),
  scene_(new SceneForGame(player1_, player2_)),
  view_(new QGraphicsView(scene_)),
  timer_(new QTimer())
{
  view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  view_->setFixedSize(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
  scene_->setSceneRect(0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);

  player1_->setPos(Config::SCREEN_WIDTH / 4 - Config::PLAYER_WIDTH / 2, Config::SCREEN_HEIGHT - Config::PLAYER_HEIGHT - Config::BOTTOM_INDENT);
  player2_->setPos(3 * (Config::SCREEN_WIDTH / 4) - Config::PLAYER_WIDTH / 2, Config::SCREEN_HEIGHT - Config::PLAYER_HEIGHT - Config::BOTTOM_INDENT);

  scene_->addItem(ball_);
  scene_->addItem(player1_);
  scene_->addItem(player2_);

  scene_->start();

  connect(timer_, SIGNAL(timeout()), ball_, SLOT(tick()));
  connect(timer_, SIGNAL(timeout()), player1_, SLOT(tick()));
  connect(timer_, SIGNAL(timeout()), player2_, SLOT(tick()));
  connect(timer_, SIGNAL(timeout()), this, SLOT(tick()));

  connect(ball_, SIGNAL(startCalc()), timer_, SLOT(stop()));
  connect(ball_, SIGNAL(stopCalc()), timer_, SLOT(start()));
}

void Game::start()
{
  timer_->start(Config::TIME);
  view_->show();
}

void Game::tick()
{

}
