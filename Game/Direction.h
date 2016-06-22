class Direction
{
  public:
    byte FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN;
    byte opposite(byte givenDirection);
}; // class Direction

// ascii hex values for input keys (w, a, s, d, pgup, pgdn)
const byte FORWARD = 87, BACKWARD = 83, LEFT = 65,
           RIGHT = 68, UP = 33, DOWN = 34;
           
byte Direction::opposite(byte givenDirection)
{
  switch(givenDirection)
  {
    case FORWARD: return BACKWARD;
    case BACKWARD: return FORWARD;
    case LEFT: return RIGHT;
    case RIGHT: return LEFT;
    case UP: return DOWN;
    case DOWN: return UP;
  } // switch
} // opposite

