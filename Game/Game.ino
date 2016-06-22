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

int snakeSpeed = 5;
byte noOfLives;
byte maxLength = 8;
byte snakeLength;
byte snakeDirection;
boolean gameRunning;
boolean aiMode = false;

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
    snakeDirection = Direction::smartDirectionChange(snake, food);
    moveSnake();
    cube->wait((int)(1000/snakeSpeed));
  }
  else
    cube->writeCube();
} // loop

void moveSnake()
{
  Cell *newHead
    = new Cell(snake->xPos, snake->yPos, snake->zPos);
  
  newHead->xPos += Direction::xDelta(snakeDirection);
  newHead->yPos += Direction::yDelta(snakeDirection);
  newHead->zPos += Direction::zDelta(snakeDirection);

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

boolean checkCrash(Cell *newHead)
{
  byte x = newHead->xPos, y = newHead->yPos, z = newHead->zPos;
  return (x < 0) || (x > 7)
            || (y < 0) || (y > 7)
            || (z < 0) || (z > 7)
            || snake->contains(newHead);
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

