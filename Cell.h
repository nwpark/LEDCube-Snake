#ifndef Snake_H
#define Snake_H

#include <Arduino.h>

class Cell
{
  public:
    Cell(byte requiredX, byte requiredY, byte requiredZ);
    ~Cell();
    byte xPos, yPos, zPos;
    Cell *next;
  private:
};

#endif
