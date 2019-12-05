#include <sceneForGame.h>

SceneForGame::SceneForGame(Player * player1, Player * player2) :
  player1_(player1),
  player2_(player2),
  isPauseGame_(false)
{
  //устанавливаем фокус на сцену(+ фокус ставится на сцену по умолчанию)
  setFocus();

  //соединяем сигналы и слоты по нажатию клавиши
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
    emit keyPressPlayer2(event);
    break;
  case Qt::Key_A:
  case Qt::Key_D:
  case Qt::Key_W:
    emit keyPressPlayer1(event);
    break;
  case Qt::Key_Escape:
    isPauseGame_ = !isPauseGame_;
    emit gameEvent(event, isPauseGame_);
    break;
  case Qt::Key_Space:
    emit gameEvent(event, isPauseGame_);
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

void SceneForGame::resetIsPauseGame()
{
  isPauseGame_ = false;
}
