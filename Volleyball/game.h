#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>


class Game : public QWidget
{
public:
  Game();


  QGraphicsScene * scene;
  QGraphicsView * view;
};

#endif // GAME_H
