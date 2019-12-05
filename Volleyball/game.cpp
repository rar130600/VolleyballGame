 #include <game.h>

#include <QBrush>
#include <QGraphicsTextItem>
#include <QPixmap>
#include <QImage>
#include <algorithm>

#include <QDebug>

#include "config.h"

Game::Game() :
  ball_(new Ball()),
  player1_(new Player()),
  player2_(new Player()),
  net_(new Net()),
  backgroundPause_(new QGraphicsRectItem()),
  backgroundTable_(new QGraphicsRectItem()),
  scene_(new SceneForGame(player1_, player2_)),
  view_(new QGraphicsView(scene_)),
  timer_(new QTimer()),
  rules_(new Rules()),
  timeScore_(),
  textScoreTime_(new QGraphicsTextItem()),
  tableInScene_(false)
{
  //устанавливаем размеры окна
  view_->setFixedSize(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
  scene_->setSceneRect(0, 0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);

  //убираем скролл бары у окна и устанавливаем фон
  view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  view_->setBackgroundBrush(QBrush(QImage(":/images/resource/background2.png")));

  //раскрашиваем и устанавливаем текстуры предметов
  QPixmap imagePlayer1;
  QPixmap imagePlayer2;

  imagePlayer1.load(":/images/resource/newPlayer1.png");
  imagePlayer2.load(":/images/resource/newPlayer2.png");

  player1_->setPixmap(imagePlayer1.scaled(static_cast<int>(Config::PLAYER_WIDTH), static_cast<int>(Config::PLAYER_HEIGHT), Qt::KeepAspectRatio));
  player2_->setPixmap(imagePlayer2.scaled(static_cast<int>(Config::PLAYER_WIDTH), static_cast<int>(Config::PLAYER_HEIGHT), Qt::KeepAspectRatio));

  net_->setBrush(QBrush(Qt::gray));
  backgroundPause_->setBrush(QBrush(Qt::black));
  backgroundPause_->setOpacity(0.5);
  backgroundTable_->setBrush(QBrush(Qt::yellow));
  backgroundTable_->setOpacity(0.7);

  QGraphicsTextItem * tmpRulesText;
  tmpRulesText = rules_->getTextItemScorePlayer1();
  tmpRulesText->setDefaultTextColor(Qt::red);
  tmpRulesText = rules_->getTextItemScorePlayer2();
  tmpRulesText->setDefaultTextColor(Qt::blue);
  tmpRulesText = rules_->getTextItemInfo();
  tmpRulesText->setDefaultTextColor(Qt::red);
  textScoreTime_->setFont(QFont("Helvetica", Config::TEXT_SIZE_SCORE));

  //расставляем объекты
  setDefaultPositionPlayers();
  setDefaultPositionBall();
  net_->setPos((Config::SCREEN_WIDTH - Config::NET_WIDTH) / 2, Config::SCREEN_HEIGHT - Config::NET_HEIGHT);
  backgroundPause_->setRect(0.0, 0.0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT);
  backgroundTable_->setRect(0.0, 0.0, 300.0, 300.0);
  backgroundTable_->setPos(Config::SCREEN_WIDTH / 2 - 160, Config::SCREEN_HEIGHT / 2 - 45);

  tmpRulesText = rules_->getTextItemScorePlayer1();
  tmpRulesText->setPos(Config::INDENT, 0.0);
  tmpRulesText = rules_->getTextItemScorePlayer2();
  tmpRulesText->setPos(Config::SCREEN_WIDTH + (tmpRulesText->textWidth() * Config::TEXT_SIZE_SCORE * 6), 0);
  tmpRulesText = rules_->getTextItemInfo();
  tmpRulesText->setPos(Config::SCREEN_WIDTH / 2 + (tmpRulesText->textWidth() * Config::TEXT_SIZE_INFO * 5),
                       Config::SCREEN_HEIGHT / 2 + (tmpRulesText->textWidth() * Config::TEXT_SIZE_INFO * 3));
  textScoreTime_->setPos(Config::SCREEN_WIDTH / 2 + (textScoreTime_->textWidth() * Config::TEXT_SIZE_SCORE * 6),
                           Config::SCREEN_HEIGHT / 2 - 50);


  //добавляем объекты на сцену
  scene_->addItem(ball_);
  scene_->addItem(player1_);
  scene_->addItem(player2_);
  //scene_->addItem(player3_);
  scene_->addItem(net_);
  scene_->addItem(rules_->getTextItemScorePlayer1());
  scene_->addItem(rules_->getTextItemScorePlayer2());
  scene_->addItem(rules_->getTextItemInfo());

  //соединяем сигналы и слоты
  connect(timer_, SIGNAL(timeout()), this, SLOT(tick()));
  connect(timer_, SIGNAL(timeout()), ball_, SLOT(tick()));
  connect(timer_, SIGNAL(timeout()), player1_, SLOT(tick()));
  connect(timer_, SIGNAL(timeout()), player2_, SLOT(tick()));

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
  setDefaultPositionPlayers();

  //если мяч упал на правую площадку
  if (x > Config::SCREEN_WIDTH / 2)
  {
    ball_->resetSpeeds();
    //устанавливаем мяч над левым игроком
    ball_->setPos(Config::SCREEN_WIDTH / 4 - Config::BALL_DIAMETER / 2, (Config::SCREEN_HEIGHT - Config::BALL_DIAMETER) / 2);
    rules_->increaseScorePlayer1();
    timeScore_.insert(std::pair<QTime, std::string>(QTime::currentTime(), "player 1"));
  }
  else //если - на левую
  {
    ball_->resetSpeeds();
    //устанавливаем мяч над правым игроком
    ball_->setPos(3 * (Config::SCREEN_WIDTH / 4) - Config::PLAYER_WIDTH / 2, (Config::SCREEN_HEIGHT - Config::BALL_DIAMETER) / 2);
    rules_->increaseScorePlayer2();
    timeScore_.insert(std::pair<QTime, std::string>(QTime::currentTime(), "player 2"));
  }

  //если кто-то набрал выигрышное количество очков
  if (rules_->getScorePlayer1() >= Config::SCORE_FOR_WINNING || rules_->getScorePlayer2() >= Config::SCORE_FOR_WINNING)
  {
    //если это левый игрок
    if (rules_->getScorePlayer1() >= Config::SCORE_FOR_WINNING)
    {
      rules_->setWhoWin(true);
    }
    else //если - правый
    {
      rules_->setWhoWin(false);
    }

    //ставим победную надпись в центр
    QGraphicsTextItem * tmpRulesText = rules_->getTextItemInfo();
    tmpRulesText->setPos(Config::SCREEN_WIDTH / 2 + (tmpRulesText->textWidth() * Config::TEXT_SIZE_INFO * 5),
                         Config::SCREEN_HEIGHT / 2 + (tmpRulesText->textWidth() * Config::TEXT_SIZE_INFO * 3));

    QString line;
    std::for_each(timeScore_.begin(), timeScore_.end(), [&](const std::pair<QTime, std::string> & i) {
      line += QString(i.first.toString() + "  " + i.second.c_str() + "\n");
    });

    textScoreTime_->setPlainText(line);
    backgroundTable_->setRect(0.0, 0.0, 300.0, 45.0 * timeScore_.size());

    scene_->addItem(backgroundTable_);
    scene_->addItem(textScoreTime_);
    tableInScene_ = true;

    rules_->resetScore();
    ball_->resetSpeeds();
    setDefaultPositionBall();
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
  //Pause
  case Qt::Key_Escape:
    //если паузу включили
    if (isPause)
    {
      scene_->addItem(backgroundPause_);
      rules_->setInfoText(QString("PAUSE"));
      //устанавливаем надпись в центр
      QGraphicsTextItem * tmpRulesText = rules_->getTextItemInfo();
      tmpRulesText->setPos(Config::SCREEN_WIDTH / 2 + (tmpRulesText->textWidth() * Config::TEXT_SIZE_INFO * 2.5),
                           Config::SCREEN_HEIGHT / 2 + (tmpRulesText->textWidth() * Config::TEXT_SIZE_INFO * 3));

      timer_->setInterval(INT_MAX); //delay ~25 days
    }
    else //если паузу выключили
    {
      scene_->removeItem(backgroundPause_);

      if (tableInScene_)
      {
        scene_->removeItem(backgroundTable_);
        scene_->removeItem(textScoreTime_);
        tableInScene_ = false;
      }
      rules_->resetInfoText();
      timer_->setInterval(Config::TIME);
    }
    break;
  //restart game
  case Qt::Key_Space:
    rules_->resetScore();
    rules_->resetInfoText();
    timer_->setInterval(Config::TIME);

    //если в момент рестарта игры включена пауза
    if (isPause)
    {
      scene_->removeItem(backgroundPause_);
      scene_->resetIsPauseGame();
    }
    if (tableInScene_)
    {
      scene_->removeItem(backgroundTable_);
      scene_->removeItem(textScoreTime_);
      tableInScene_ = false;
    }

    setDefaultPositionPlayers();
    ball_->resetSpeeds();
    setDefaultPositionBall();

    break;
  }
}

void Game::setDefaultPositionPlayers()
{
  player1_->setPos(Config::SCREEN_WIDTH / 4 - Config::PLAYER_WIDTH / 2, Config::SCREEN_HEIGHT - Config::PLAYER_HEIGHT - Config::INDENT);
  player2_->setPos(3 * (Config::SCREEN_WIDTH / 4) - Config::PLAYER_WIDTH / 2, Config::SCREEN_HEIGHT - Config::PLAYER_HEIGHT - Config::INDENT);
}

void Game::setDefaultPositionBall()
{
  ball_->setPos((Config::SCREEN_WIDTH - Config::BALL_DIAMETER) / 2, Config::SCREEN_HEIGHT / 4);
}
