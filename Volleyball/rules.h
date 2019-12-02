#ifndef RULES_H
#define RULES_H

#include <QObject>
#include <QGraphicsTextItem>
#include <vector>

class Rules : public QObject
{
  Q_OBJECT
public:
  Rules();

  void increaseScorePlayer1();
  void increaseScorePlayer2();
  QGraphicsTextItem* getTextItemScorePlayer1();
  QGraphicsTextItem* getTextItemScorePlayer2();
  QGraphicsTextItem* getTextItemInfo();
  std::size_t getScorePlayer1();
  std::size_t getScorePlayer2();
  void resetScore();
  void resetInfoText();
  void setWhoWin(bool isPlayer1);
  void setInfoText(const QString & string);

private:
  using vector_score = std::vector<std::size_t>;

  vector_score scorePlayers_;
  QGraphicsTextItem * textItemScorePlayer1_;
  QGraphicsTextItem * textItemScorePlayer2_;
  QGraphicsTextItem * textItemInfo_;

  void updateScore();
};

#endif // RULES_H
