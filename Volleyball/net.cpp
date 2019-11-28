#include "net.h"

#include "config.h"

Net::Net() :
  width_(Config::NET_WIDTH),
  height_(Config::NET_HEIGHT)
{
  setRect(0, 0, width_, height_);
}
