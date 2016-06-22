#include "Cell.h"
#include "CubeInterface.h"

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
