#include "rules.h"

#include <QFont>

#include "config.h"

Rules::Rules() :
  scorePlayers_(2, 0),
  textItemScorePlayer1_(new QGraphicsTextItem()),
  textItemScorePlayer2_(new QGraphicsTextItem()),
  textItemInfo_(new QGraphicsTextItem())
{
  //устанавливаем шрифт и размер
  textItemScorePlayer1_->setFont(QFont("Helvetica", Config::TEXT_SIZE_SCORE));
  textItemScorePlayer2_->setFont(textItemScorePlayer1_->font());
  textItemInfo_->setFont(QFont("Helvetica", Config::TEXT_SIZE_INFO));

  //задаем начальный текст
  updateScore();
  resetInfoText();
}

void Rules::increaseScorePlayer1()
{
  scorePlayers_.at(0) += 1;
  //обновляем текст
  updateScore();
}

void Rules::increaseScorePlayer2()
{
  scorePlayers_.at(1) += 1;
  //обновляем текст
  updateScore();
}

QGraphicsTextItem* Rules::getTextItemScorePlayer1()
{
  return textItemScorePlayer1_;
}

QGraphicsTextItem* Rules::getTextItemScorePlayer2()
{
  return textItemScorePlayer2_;
}

QGraphicsTextItem * Rules::getTextItemInfo()
{
  return textItemInfo_;
}

std::size_t Rules::getScorePlayer1()
{
  return scorePlayers_.at(0);
}

std::size_t Rules::getScorePlayer2()
{
  return scorePlayers_.at(1);
}

void Rules::resetScore()
{
  //сбрасывает счет
  scorePlayers_.at(0) = 0;
  scorePlayers_.at(1) = 0;

  //обновляем текст
  updateScore();
}

void Rules::resetInfoText()
{
  textItemInfo_->setPlainText(QString(""));
}

void Rules::setWhoWin(bool isPlayer1)
{
  if (isPlayer1)
  {
    textItemInfo_->setDefaultTextColor(Qt::red);
    textItemInfo_->setPlainText(QString("PLAYER 1 WIN"));
  }
  else
  {
    textItemInfo_->setDefaultTextColor(Qt::blue);
    textItemInfo_->setPlainText(QString("PLAYER 2 WIN"));
  }
}

void Rules::setInfoText(const QString & string)
{
  textItemInfo_->setDefaultTextColor(Qt::black);
  textItemInfo_->setPlainText(string);
}

void Rules::updateScore()
{
  textItemScorePlayer1_->setPlainText(QString("Score: ") + QString::number(scorePlayers_[0]));
  textItemScorePlayer2_->setPlainText(QString("Score: ") + QString::number(scorePlayers_[1]));
}
