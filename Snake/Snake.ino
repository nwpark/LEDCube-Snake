#include <Snake.h>
#include <CubeInterface.h>

Snake *snake;
Snake *food;
CubeInterface cube(1);

const byte FORWARD = 87, BACKWARD = 83, LEFT = 65,
           RIGHT = 68, UP = 33, DOWN = 34;

byte snakeDirection;

void setup()
{
  setInitialPosition();
  placeFood();
} // setup

void loop()
{
  Serial.begin(9600);
  updateCube();
  cube.wait(600);
  moveSnake();
} // loop

void moveSnake()
{
  Snake *head
    = new Snake(snake->xPos, snake->yPos, snake->zPos);

  switch (snakeDirection)
  {
    case FORWARD: head->yPos++; break;
    case BACKWARD: head->yPos--; break;
    case LEFT: head->xPos--; break;
    case RIGHT: head->xPos++; break;
    case UP: head->zPos++; break;
    case DOWN: head->zPos--; break;
  } // switch

  if (!checkCrash(head))
  {
    head->next = snake;
    snake = head;

    if(snake->xPos == food->xPos && snake->yPos == food->yPos
           && snake->zPos == food ->zPos)
    {
      delete food;
      placeFood();
    } // if
    else
      moveTail();
  } // if
  else
  {
    deathAnimation();
  }
} // move

void placeFood()
{
  byte foodX, foodY, foodZ;
  do
  {
    foodX = random(0, 8);
    foodY = random(0, 8);
    foodZ = random(0, 8);
  } while(cube.ledStatus[foodX][foodY][foodZ] != LOW);
  
  food = new Snake(foodX, foodY, foodZ);
}

void deathAnimation()
{
  for (int i = 0; i < 5; i++)
  {
    delay(200);
    cube.wait(400);
  }
} // deathAnimation

boolean checkCrash(Snake *head)
{
  return (head->xPos < 0) || (head->xPos > 7)
         || (head->yPos < 0) || (head->yPos > 7)
         || (head->zPos < 0) || (head->zPos > 7);
}

void moveTail()
{
  Snake *tail = snake;
  while (tail->next->next != NULL)
  {
    tail = tail->next;
  }
  delete tail->next;
  tail->next = NULL;
}

void updateCube()
{
  cube.clearAll();

  Snake *snakeBody = snake;

  while (snakeBody != NULL)
  {
    cube.light(snakeBody->xPos, snakeBody->yPos,
               snakeBody->zPos);
    snakeBody = snakeBody->next;
  }

  cube.light(food->xPos, food->yPos, food->zPos);
}

void setInitialPosition()
{
  snakeDirection = FORWARD;
  snake = new Snake(0, 3, 0);

  Snake *body = snake;
  for (int i = 2; i >= 0; i--)
  {
    body->next = new Snake(0, i, 0);
    body = body->next;
  }
} // setInitialPosition

void serialEvent()
{
  snakeDirection = (byte)Serial.read();
} // serialEvent
