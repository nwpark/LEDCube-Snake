#include "Direction.h"

// ascii hex values for input keys (w, a, s, d, pgup, pgdn)
const byte Direction::FORWARD = 87, Direction::BACKWARD = 83, Direction::LEFT = 65,
           Direction::RIGHT = 68, Direction::UP = 33, Direction::DOWN = 34;

// return a direction that will move snake towards the food
byte Direction::smartDirectionChange(Cell *snake, Cell *food)
{
  byte x = snake->xPos, y = snake->yPos, z = snake->zPos;
  if(snake->xPos < food->xPos && !snake->contains(x+1, y, z))
    return RIGHT;
  else if(snake->xPos > food->xPos && !snake->contains(x-1, y, z))
    return LEFT;
  else if(snake->yPos < food->yPos && !snake->contains(x, y+1, z))
    return FORWARD;
  else if(snake->yPos > food->yPos && !snake->contains(x, y-1, z))
    return BACKWARD;
  else if(snake->zPos < food->zPos && !snake->contains(x, y, z+1))
    return UP;
  else if(snake->zPos > food->zPos && !snake->contains(x, y, z-1))
    return DOWN;
} // smartDirectionChange

// return a direction of opposite direction to the given one
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

// return the difference in the x plane after moving in the given
// direction
byte Direction::xDelta(byte givenDirection)
{
  if(givenDirection == LEFT) return -1;
  else if(givenDirection == RIGHT) return 1;
  else return 0;
} // xDelta

// return the difference in the y plane after moving in the given
// direction
byte Direction::yDelta(byte givenDirection)
{
  if(givenDirection == FORWARD) return 1;
  else if(givenDirection == BACKWARD) return -1;
  else return 0;
} // yDelta

// return the difference in the z plane after moving in the given
// direction
byte Direction::zDelta(byte givenDirection)
{
  if(givenDirection == UP) return 1;
  else if(givenDirection == DOWN) return -1;
  else return 0;
} // zDelta
