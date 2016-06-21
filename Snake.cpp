#include "Snake.h"

byte xPos, yPos, zPos;
Snake *next;

// constructor
Snake::Snake(byte requiredX, byte requiredY, byte requiredZ)
{
  xPos = requiredX;
  yPos = requiredY;
  zPos = requiredZ;
  next = NULL;
} // Snake

// destructor
Snake::~Snake(){}
