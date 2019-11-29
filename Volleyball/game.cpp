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
  backgroundPause_(new QGraphicsRectItem ()),
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

  QGraphicsTextItem * tmpRulesText;

  //красим объекты
  player1_->setBrush(QBrush(Qt::darkRed));
  player2_->setBrush(QBrush(Qt::darkBlue));
  ball_->setBrush(QBrush(Qt::yellow));
  net_->setBrush(QBrush(Qt::black));
  backgroundPause_->setBrush(QBrush(Qt::black));
  backgroundPause_->setOpacity(0.5);

  tmpRulesText = rules_->getTextItemScorePlayer1();
  tmpRulesText->setDefaultTextColor(Qt::red);
  tmpRulesText = rules_->getTextItemScorePlayer2();
  tmpRulesText->setDefaultTextColor(Qt::blue);
  tmpRulesText = rules_->getTextItemInfo();
  tmpRulesText->setDefaultTextColor(Qt::red);

  //расставляем объекты
  player1_->setPos(Config::SCREEN_WIDTH / 4 - Config::PLAYER_WIDTH / 2, Config::SCREEN_HEIGHT - Config::PLAYER_HEIGHT - Config::INDENT);
  player2_->setPos(3 * (Config::SCREEN_WIDTH / 4) - Config::PLAYER_WIDTH / 2, Config::SCREEN_HEIGHT - Config::PLAYER_HEIGHT - Config::INDENT);
  ball_->setPos(Config::SCREEN_WIDTH / 2 - Config::BALL_DIAMETER / 2, Config::SCREEN_HEIGHT / 4);
  net_->setPos((Config::SCREEN_WIDTH - Config::NET_WIDTH) / 2, Config::SCREEN_HEIGHT - Config::NET_HEIGHT);
  backgroundPause_->setRect(0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);

  tmpRulesText = rules_->getTextItemScorePlayer1();
  tmpRulesText->setPos(Config::INDENT, 0.0);
  tmpRulesText = rules_->getTextItemScorePlayer2();
  tmpRulesText->setPos(Config::SCREEN_WIDTH + (tmpRulesText->textWidth() * Config::TEXT_SIZE_SCORE * 6), 0);
  tmpRulesText = rules_->getTextItemInfo();
  tmpRulesText->setPos(Config::SCREEN_WIDTH / 2 + (tmpRulesText->textWidth() * Config::TEXT_SIZE_INFO * 5),
                       Config::SCREEN_HEIGHT / 2 + (tmpRulesText->textWidth() * Config::TEXT_SIZE_INFO * 3));

  //добавляем объекты на сцену
  scene_->addItem(ball_);
  scene_->addItem(player1_);
  scene_->addItem(player2_);
  scene_->addItem(net_);
  scene_->addItem(rules_->getTextItemScorePlayer1());
  scene_->addItem(rules_->getTextItemScorePlayer2());
  scene_->addItem(rules_->getTextItemInfo());

  //соединяем сигналы и слоты
  connect(timer_, SIGNAL(timeout()), this, SLOT(tick()));
  connect(timer_, SIGNAL(timeout()), ball_, SLOT(tick()));
  connect(timer_, SIGNAL(timeout()), player1_, SLOT(tick()));
  connect(timer_, SIGNAL(timeout()), player2_, SLOT(tick()));
  connect(timer_, SIGNAL(timeout()), rules_, SLOT(tick()));

  connect(ball_, SIGNAL(startCalc()), timer_, SLOT(stop()));
  connect(ball_, SIGNAL(stopCalc()), timer_, SLOT(start()));
  connect(ball_, SIGNAL(ballOnBottom(qreal)), this, SLOT(ballOnBottom(qreal)));

  connect(scene_, SIGNAL(gameEvent(QKeyEvent *, bool)), this, SLOT(gameEvent(QKeyEvent *, bool)));
}

void Game::start()
{
  view_->show();
  timer_->start(Config::TIME);
}

void Game::tick()
{
  timer_->setInterval(Config::TIME);
  rules_->resetInfoText();
}

void Game::ballOnBottom(qreal x)
{
  player1_->setPos(Config::SCREEN_WIDTH / 4 - Config::PLAYER_WIDTH / 2, Config::SCREEN_HEIGHT - Config::PLAYER_HEIGHT - Config::INDENT);
  player2_->setPos(3 * (Config::SCREEN_WIDTH / 4) - Config::PLAYER_WIDTH / 2, Config::SCREEN_HEIGHT - Config::PLAYER_HEIGHT - Config::INDENT);

  if (x > Config::SCREEN_WIDTH / 2)
  {
    ball_->resetSpeeds();
    ball_->setPos(Config::SCREEN_WIDTH / 4 - Config::BALL_DIAMETER / 2, (Config::SCREEN_HEIGHT - Config::BALL_DIAMETER) / 2);
    rules_->increaseScorePlayer1();
  }
  else
  {
    ball_->resetSpeeds();
    ball_->setPos(3 * (Config::SCREEN_WIDTH / 4) - Config::PLAYER_WIDTH / 2, (Config::SCREEN_HEIGHT - Config::BALL_DIAMETER) / 2);
    rules_->increaseScorePlayer2();
  }

  if (rules_->getScorePlayer1() >= Config::SCORE_FOR_WINNING || rules_->getScorePlayer2() >= Config::SCORE_FOR_WINNING)
  {
    if (rules_->getScorePlayer1() >= Config::SCORE_FOR_WINNING)
    {
      rules_->setWhoWin(true);
    }
    else
    {
      rules_->setWhoWin(false);
    }

    QGraphicsTextItem * tmpRulesText = rules_->getTextItemInfo();
    tmpRulesText->setPos(Config::SCREEN_WIDTH / 2 + (tmpRulesText->textWidth() * Config::TEXT_SIZE_INFO * 5),
                         Config::SCREEN_HEIGHT / 2 + (tmpRulesText->textWidth() * Config::TEXT_SIZE_INFO * 3));

    rules_->resetScore();
    ball_->resetSpeeds();
    ball_->setPos(Config::SCREEN_WIDTH / 2 - Config::BALL_DIAMETER / 2, Config::SCREEN_HEIGHT / 4);
    timer_->setInterval(INT_MAX); //delay ~25 days
  }
  else
  {
    timer_->setInterval(1000);
  }
}

void Game::gameEvent(QKeyEvent * event, bool isPause)
{
  switch (event->key())
  {
  case Qt::Key_Escape:
    if (isPause)
    {
      scene_->addItem(backgroundPause_);
      rules_->setInfoText(QString("PAUSE"));
      QGraphicsTextItem * tmpRulesText = rules_->getTextItemInfo();
      tmpRulesText->setPos(Config::SCREEN_WIDTH / 2 + (tmpRulesText->textWidth() * Config::TEXT_SIZE_INFO * 2.5),
                           Config::SCREEN_HEIGHT / 2 + (tmpRulesText->textWidth() * Config::TEXT_SIZE_INFO * 3));

      timer_->setInterval(INT_MAX); //delay ~25 days
    }
    else
    {
      scene_->removeItem(backgroundPause_);
      rules_->resetInfoText();
      timer_->setInterval(Config::TIME);
    }
    break;
  case Qt::Key_Space:
    rules_->resetScore();
    rules_->resetInfoText();
    timer_->setInterval(Config::TIME);
    if (isPause)
    {
      scene_->resetIsPauseGame();
    }

    player1_->setPos(Config::SCREEN_WIDTH / 4 - Config::PLAYER_WIDTH / 2, Config::SCREEN_HEIGHT - Config::PLAYER_HEIGHT - Config::INDENT);
    player2_->setPos(3 * (Config::SCREEN_WIDTH / 4) - Config::PLAYER_WIDTH / 2, Config::SCREEN_HEIGHT - Config::PLAYER_HEIGHT - Config::INDENT);

    ball_->resetSpeeds();
    ball_->setPos(Config::SCREEN_WIDTH / 2 - Config::BALL_DIAMETER / 2, Config::SCREEN_HEIGHT / 4);

    break;
  }
}
