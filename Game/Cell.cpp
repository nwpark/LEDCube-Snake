#include "Cell.h"

// Cell has 3 coordinates
byte xPos, yPos, zPos;
// model a Cell as a linked list
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
Cell::~Cell()
{
  // recursively delete all Cells linked to this one
  if(next != NULL)
  {
    delete next;
    next = NULL;
  } // if
} // ~Cell

boolean Cell::contains(Cell *otherCell)
{
  if(next == NULL)
    return this->equals(otherCell);
  else if(!this->equals(otherCell))
    return next->contains(otherCell);
} // contains

boolean Cell::contains(byte otherX, byte otherY, byte otherZ)
{
  if(next == NULL)
    return this->equals(otherX, otherY, otherZ);
  else if(!this->equals(otherX, otherY, otherZ))
    return next->contains(otherX, otherY, otherZ);
} // contains

// delete the last element in the linked list
void Cell::deleteLast()
{
  // recursively search for the last Cell in the list
  // then delete it
  if(next->next == NULL)
  {
    delete next;
    next = NULL;
  } // if
  else
    next->deleteLast();
} // deleteLast

// update the cube to light the led at coordinates given by each
// Cell in the linked list
void Cell::updateCube(CubeInterface *cube)
{
  // update the cube with this position then recursively update
  // the cube with the next Cell
  cube->light(xPos, yPos, zPos);
  if(next != NULL)
    next->updateCube(cube);
} // updateCube

boolean Cell::equals(Cell *otherCell)
{
  return xPos == otherCell->xPos && yPos == otherCell->yPos
               && zPos == otherCell->zPos;
} // equals

boolean Cell::equals(byte otherX, byte otherY, byte otherZ)
{
  return xPos == otherX && yPos == otherY && zPos == otherZ;
} // equals
