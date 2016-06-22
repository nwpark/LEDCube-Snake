#include "Direction.h"

// ascii hex values for input keys (w, a, s, d, pgup, pgdn)
const byte Direction::FORWARD = 87, Direction::BACKWARD = 83, Direction::LEFT = 65,
           Direction::RIGHT = 68, Direction::UP = 33, Direction::DOWN = 34;
           
byte Direction::opposite(byte givenDirection)
{
  // cant use switch statement cuz c++ sucks -.-
  if(givenDirection == FORWARD) return BACKWARD;
  if(givenDirection == BACKWARD) return FORWARD;
  if(givenDirection == LEFT) return RIGHT;
  if(givenDirection == RIGHT) return LEFT;
  if(givenDirection == UP) return DOWN;
  if(givenDirection == DOWN) return UP;
} // opposite
