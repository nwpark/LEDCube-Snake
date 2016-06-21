#ifndef Snake_H
#define Snake_H

#include <Arduino.h>

class Snake
{
  public:
    Snake(byte requiredX, byte requiredY, byte requiredZ);
    ~Snake();
    byte xPos, yPos, zPos;
    Snake *next;
  private:
};

#endif
