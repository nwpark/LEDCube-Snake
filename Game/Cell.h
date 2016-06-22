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
    boolean contains(Cell *otherCell);
    boolean contains(byte otherX, byte otherY, byte otherZ);
    void deleteLast();
    void updateCube(CubeInterface *cube);
    boolean equals(Cell *otherCell);
    boolean equals(byte otherX, byte otherY, byte otherZ);
  private:
};

#endif
