#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>


class Game : public QWidget
{
  Q_OBJECT
public:
  Game();

  void addItem(QGraphicsItem * item);
  void viewShow();

public slots:
  void tick();

private:
  QGraphicsScene * scene;
  QGraphicsView * view;
  QTimer * timer;
};

#endif // GAME_H
