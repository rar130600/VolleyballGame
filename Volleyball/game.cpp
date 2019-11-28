#include <game.h>

#include <QDebug>
#include <QBrush>
#include <QGraphicsTextItem>

#include "config.h"

Game::Game() :
  ball_(new Ball()),
  player1_(new Player()),
  player2_(new Player()),
  net_(new Net()),
  scene_(new SceneForGame(player1_, player2_)),
  view_(new QGraphicsView(scene_)),
  timer_(new QTimer()),
  rules_(new Rules())
{
  //убираем скролл бары у окна
  view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  //устанавливаем размеры окна
  view_->setFixedSize(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
  scene_->setSceneRect(0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);

  QGraphicsTextItem * tmpScoreText;

  //красим объекты
  player1_->setBrush(QBrush(Qt::darkRed));
  player2_->setBrush(QBrush(Qt::darkBlue));
  ball_->setBrush(QBrush(Qt::yellow));
  net_->setBrush(QBrush(Qt::black));

  tmpScoreText = rules_->getTextItemScorePlayer1();
  tmpScoreText->setDefaultTextColor(Qt::red);
  tmpScoreText = rules_->getTextItemScorePlayer2();
  tmpScoreText->setDefaultTextColor(Qt::blue);

  //расставляем объекты
  player1_->setPos(Config::SCREEN_WIDTH / 4 - Config::PLAYER_WIDTH / 2, Config::SCREEN_HEIGHT - Config::PLAYER_HEIGHT - Config::INDENT);
  player2_->setPos(3 * (Config::SCREEN_WIDTH / 4) - Config::PLAYER_WIDTH / 2, Config::SCREEN_HEIGHT - Config::PLAYER_HEIGHT - Config::INDENT);
  ball_->setPos(Config::SCREEN_WIDTH / 2 - Config::BALL_DIAMETER / 2, Config::SCREEN_HEIGHT / 4);
  net_->setPos((Config::SCREEN_WIDTH - Config::NET_WIDTH) / 2, Config::SCREEN_HEIGHT - Config::NET_HEIGHT);

  tmpScoreText = rules_->getTextItemScorePlayer1();
  tmpScoreText->setPos(20.0, 0.0);
  tmpScoreText = rules_->getTextItemScorePlayer2();
  tmpScoreText->setPos(Config::SCREEN_WIDTH - 165, 0);

  //добавляем объекты на сцену
  scene_->addItem(ball_);
  scene_->addItem(player1_);
  scene_->addItem(player2_);
  scene_->addItem(net_);
  scene_->addItem(rules_->getTextItemScorePlayer1());
  scene_->addItem(rules_->getTextItemScorePlayer2());

  //соединяем сигналы и слоты
  connect(timer_, SIGNAL(timeout()), this, SLOT(tick()));
  connect(timer_, SIGNAL(timeout()), ball_, SLOT(tick()));
  connect(timer_, SIGNAL(timeout()), player1_, SLOT(tick()));
  connect(timer_, SIGNAL(timeout()), player2_, SLOT(tick()));
  connect(timer_, SIGNAL(timeout()), rules_, SLOT(tick()));

  connect(ball_, SIGNAL(startCalc()), timer_, SLOT(stop()));
  connect(ball_, SIGNAL(stopCalc()), timer_, SLOT(start()));
  connect(ball_, SIGNAL(ballOnBottom(qreal)), this, SLOT(ballOnBottom(qreal)));
}

void Game::start()
{
  view_->show();
  timer_->start(Config::TIME);
}

void Game::tick()
{
  timer_->setInterval(Config::TIME);
}

void Game::ballOnBottom(qreal x)
{
  timer_->stop();
  player1_->setPos(Config::SCREEN_WIDTH / 4 - Config::PLAYER_WIDTH / 2, Config::SCREEN_HEIGHT - Config::PLAYER_HEIGHT - Config::INDENT);
  player2_->setPos(3 * (Config::SCREEN_WIDTH / 4) - Config::PLAYER_WIDTH / 2, Config::SCREEN_HEIGHT - Config::PLAYER_HEIGHT - Config::INDENT);

  if (x > Config::SCREEN_WIDTH / 2)
  {
    ball_->setPos(Config::SCREEN_WIDTH / 4 - Config::BALL_DIAMETER / 2, (Config::SCREEN_HEIGHT - Config::BALL_DIAMETER) / 2);
    rules_->increaseScorePlayer1();
  }
  else
  {
    ball_->setPos(3 * (Config::SCREEN_WIDTH / 4) - Config::PLAYER_WIDTH / 2, (Config::SCREEN_HEIGHT - Config::BALL_DIAMETER) / 2);
    rules_->increaseScorePlayer2();
  }
  timer_->setInterval(2000);
  timer_->start();
}
