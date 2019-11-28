#include <sceneForGame.h>

SceneForGame::SceneForGame(Player * player1, Player * player2) :
  player1_(player1),
  player2_(player2)
{
  connect(this, SIGNAL(keyPressPlayer1(QKeyEvent *)), player1_, SLOT(keyPress(QKeyEvent *)));
  connect(this, SIGNAL(keyReleasePlayer1(QKeyEvent *)), player1_, SLOT(keyRelease(QKeyEvent *)));
  connect(this, SIGNAL(keyPressPlayer2(QKeyEvent *)), player2_, SLOT(keyPress(QKeyEvent*)));
  connect(this, SIGNAL(keyReleasePlayer2(QKeyEvent *)), player2_, SLOT(keyRelease(QKeyEvent *)));
}

void SceneForGame::keyPressEvent(QKeyEvent * event)
{
  switch (event->key())
  {
  case Qt::Key_Left:
  case Qt::Key_Right:
  case Qt::Key_Up:
  case Qt::Key_Down:
    emit keyPressPlayer2(event);
    break;
  case Qt::Key_A:
  case Qt::Key_D:
  case Qt::Key_W:
  case Qt::Key_S:
    emit keyPressPlayer1(event);
    break;
  }

}

void SceneForGame::keyReleaseEvent(QKeyEvent * event)
{
  switch (event->key())
  {
  case Qt::Key_Left:
  case Qt::Key_Right:
  case Qt::Key_Up:
    emit keyReleasePlayer2(event);
    break;
  case Qt::Key_A:
  case Qt::Key_D:
  case Qt::Key_W:
    emit keyReleasePlayer1(event);
    break;
  }
}
