#ifndef NET_H
#define NET_H

#include <QObject>
#include <QGraphicsRectItem>

class Net : public QObject, public QGraphicsRectItem
{
  Q_OBJECT
public:
  Net();

private:
  std::size_t width_;
  std::size_t height_;
};

#endif // NET_H
