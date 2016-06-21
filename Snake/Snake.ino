#include <StackArray.h>
#include <Snake.h>
#include <CubeInterface.h>

Snake *snake;
CubeInterface cube(1);

void setup()
{
  setInitialPosition();
} // setup

void loop()
{
  Serial.begin(9600);
  updateCube();
  cube.wait(1000);
  snake->xPos++;
} // loop

void updateCube()
{
  Snake *body = snake;

  while(body != NULL)
  {
    cube.light(body->xPos, body->yPos, body->zPos);
    body = body->next;
  }
}

void setInitialPosition()
{
  snake = new Snake(0, 3, 0);
  
  Snake *body = snake;
  for(int i=2; i >= 0; i--)
  {
    body->next = new Snake(0, i, 0);
    body = body->next;
  }
} // setInitialPosition

