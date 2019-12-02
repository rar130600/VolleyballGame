#ifndef ENTITY_H
#define ENTITY_H

#include <QObject>

class Entity : public QObject
{
  Q_OBJECT
public:
  Entity() = default;

public slots:
  virtual void tick() = 0;

protected:
  virtual void move() = 0;
  virtual void colliding() = 0;
  virtual void checkMaxSpeed() = 0;
  virtual void checkCollisionWithScene() = 0;
};

#endif // ENTITY_H
