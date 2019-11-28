#include "rules.h"

#include <QFont>

#include "config.h"

Rules::Rules() :
  scorePlayer1_(0),
  scorePlayer2_(0),
  textItemScorePlayer1_(new QGraphicsTextItem()),
  textItemScorePlayer2_(new QGraphicsTextItem())
{
  //задаем начальный текст
  textItemScorePlayer1_->setPlainText(QString("Score: ") + QString::number(scorePlayer1_));
  textItemScorePlayer2_->setPlainText(QString("Score: ") + QString::number(scorePlayer2_));

  //устанавливаем шрифт и размер
  textItemScorePlayer1_->setFont(QFont("Helvetica", 24));
  textItemScorePlayer2_->setFont(textItemScorePlayer1_->font());
}

void Rules::increaseScorePlayer1()
{
  scorePlayer1_++;
  //обновляем текст
  textItemScorePlayer1_->setPlainText(QString("Score: ") + QString::number(scorePlayer1_));
}

void Rules::increaseScorePlayer2()
{
  scorePlayer2_++;
  //обновляем текст
  textItemScorePlayer2_->setPlainText(QString("Score: ") + QString::number(scorePlayer2_));
}

QGraphicsTextItem* Rules::getTextItemScorePlayer1()
{
  return textItemScorePlayer1_;
}

QGraphicsTextItem* Rules::getTextItemScorePlayer2()
{
  return textItemScorePlayer2_;
}

void Rules::tick()
{

}
