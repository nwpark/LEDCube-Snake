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
  if(next != NULL)
  {
    delete next;
    next = NULL;
  } // if
} // ~Cell

// delete the last element in the linked list
void Cell::deleteLast()
{
  if(next->next == NULL)
  {
    delete next;
    next = NULL;
  } // if
  else
    next->deleteLast();
} // deleteLast

void Cell::updateCube(CubeInterface cube)
{
  cube.light(xPos, yPos, zPos);
//  if(next != NULL)
//    next->updateCube(cube);
}
