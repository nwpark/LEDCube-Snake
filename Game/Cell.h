#ifndef Snake_H
#define Snake_H

#include <Arduino.h>
#include "CubeInterface.h"

class Cell
{
  public:
    byte xPos, yPos, zPos;
    Cell *next;
    Cell(byte requiredX, byte requiredY, byte requiredZ);
    ~Cell();
    void deleteLast();
    void updateCube(CubeInterface cube);
  private:
};

#endif
