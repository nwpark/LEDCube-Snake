#ifndef Direction_H
#define Direction_H

#include <Arduino.h>

class Direction
{
  public:
    static const byte FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN;
    static byte opposite(byte givenDirection);
}; // class Direction

#endif
