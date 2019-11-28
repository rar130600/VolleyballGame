#include "net.h"

#include <QBrush>

#include "config.h"

Net::Net() :
  width_(Config::NET_WIDTH),
  height_(Config::NET_HEIGHT)
{
  setBrush(QBrush(Qt::black));
  setRect(0, 0, width_, height_);
}
