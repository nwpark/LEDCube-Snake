#include "Cell.h"
#include "CubeInterface.h"
#include "Direction.h"

// model the snake as a linked list
Cell *snake;
Cell *food;
// object to control led cube
CubeInterface *cube;

// ascii hex values for input keys (w, a, s, d, pgup, pgdn)
const byte FORWARD = 87, BACKWARD = 83, LEFT = 65,
           RIGHT = 68, UP = 33, DOWN = 34;

int snakeSpeed = 30;
byte noOfLives;
byte maxLength = 8;
byte snakeLength;
byte snakeDirection;
boolean gameRunning;
boolean aiMode = true;

void setup()
{
  Serial.begin(250000);

  cube = new CubeInterface(1);

  setInitialState();
  updateCube();
} // setup

void loop()
{
  updateCube();
  if(gameRunning)
  {
    cube->wait((int)(1000/snakeSpeed));
    moveSnake();
  }
  else if(aiMode)
  {
    cube->wait((int)(1000/snakeSpeed));
    smartMove();
  }
  else
    cube->writeCube();
} // loop

void smartMove()
{
  if(snake->xPos < food->xPos)
    snakeDirection = RIGHT;
  else if(snake->xPos > food->xPos)
    snakeDirection = LEFT;
  else if(snake->yPos < food->yPos)
    snakeDirection = FORWARD;
  else if(snake->yPos > food->yPos)
    snakeDirection = BACKWARD;
  else if(snake->zPos < food->zPos)
    snakeDirection = UP;
  else if(snake->zPos > food->zPos)
    snakeDirection = DOWN;
    
  moveSnake();
}

void moveSnake()
{
  Cell *newHead
    = new Cell(snake->xPos, snake->yPos, snake->zPos);

  switch (snakeDirection)
  {
    case FORWARD: newHead->yPos++; break;
    case BACKWARD: newHead->yPos--; break;
    case LEFT: newHead->xPos--; break;
    case RIGHT: newHead->xPos++; break;
    case UP: newHead->zPos++; break;
    case DOWN: newHead->zPos--; break;
  } // switch

  if (!checkCrash(newHead))
  {
    newHead->next = snake;
    snake = newHead;

    if(snake->xPos == food->xPos && snake->yPos == food->yPos
          && snake->zPos == food ->zPos)
    {
      delete food;
      placeFood();
      if(snakeLength < maxLength)
        snakeLength++;
      else
        moveTail();
    } // if
    else
      moveTail();
  } // if
  else
  {
    noOfLives--;
    delete newHead;
    
    // crash animation
    for(int i=0; i < 4; i++)
    {
      //delay(200);
      cube->clearAll();
      cube->wait(150);
      updateCube();
      cube->wait(150);
    } // for

    if(noOfLives == 0)
      endGame();
  } // else
} // move

void endGame()
{
  // death animation
  for(int i=0; i < 8; i++)
  {
    cube->lightLayer(i);
    cube->wait(30);
  } // for
  for(int i=7; i >= 0; i--)
  {
    cube->clearLayer(i);
    cube->wait(30);
  } // for

  delete food;
  delete snake;
  setInitialState();
} // endGame

void placeFood()
{
  byte foodX, foodY, foodZ;
  do
  {
    foodX = random(0, 8);
    foodY = random(0, 8);
    foodZ = random(0, 8);
  } while(cube->ledStatus[foodX][foodY][foodZ] != LOW);
  
  food = new Cell(foodX, foodY, foodZ);
}

boolean checkCrash(Cell *head)
{
  byte x = head->xPos, y = head->yPos, z = head->zPos;
  return (x < 0) || (x > 7)
            || (y < 0) || (y > 7)
            || (z < 0) || (z > 7);
            //|| cube->ledStatus[x][y][z] == HIGH;
}

void moveTail()
{
  snake->deleteLast();
}

void updateCube()
{
  cube->clearAll();

  // recursively update the cube with the snake position
  snake->updateCube(cube);
  // update the cube with the food position
  food->updateCube(cube);
}

void setInitialState()
{
  gameRunning = false;
  noOfLives = 3;
  snakeLength = 4;
  snakeDirection = FORWARD;
  
  snake = new Cell(0, 3, 0);
  Cell *snakeBody = snake;
  for (int i = 2; i >= 0; i--)
  {
    snakeBody->next = new Cell(0, i, 0);
    snakeBody = snakeBody->next;
  }

  placeFood();
} // setInitialState

void serialEvent()
{
  byte input = (byte)Serial.read();
  // 80 = 'p'
  if(input == 80)
    gameRunning = !gameRunning;
  else if(input != Direction::opposite(snakeDirection))
    snakeDirection = input;
} // serialEvent

