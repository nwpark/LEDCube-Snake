#include "Cell.h"

byte xPos, yPos, zPos;
Cell *next;

// constructor
Cell::Cell(byte requiredX, byte requiredY, byte requiredZ)
{
  xPos = requiredX;
  yPos = requiredY;
  zPos = requiredZ;
  next = NULL;
} // Cell

// destructor
Cell::~Cell(){}
