#ifndef Direction_H
#define Direction_H

#include <Arduino.h>
#include "Cell.h"

class Direction
{
  public:
    static const byte FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN;
    static byte smartDirectionChange(Cell *snake, Cell *food);
    static byte opposite(byte givenDirection);
    static byte xDelta(byte givenDirection);
    static byte yDelta(byte givenDirection);
    static byte zDelta(byte givenDirection);
}; // class Direction

#endif
