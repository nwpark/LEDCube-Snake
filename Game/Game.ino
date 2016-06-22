#include "Cell.h"
#include "CubeInterface.h"
#include "Direction.h"

// model the snake as a linked list
Cell *snake;
Cell *food;
// object to control led cube
CubeInterface *cube;

int snakeSpeed = 30;
byte maxLength = 8;

// these values set by setInitialState()
byte noOfLives;
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
    // move snake every x milliseconds
    cube->wait((int)(1000/snakeSpeed));
    moveSnake();
  }
  else if(aiMode)
  {
    // move snake every x milliseconds and automatically change
    // direction to move toward food
    snakeDirection = Direction::smartDirectionChange(snake, food);
    moveSnake();
    cube->wait((int)(1000/snakeSpeed));
  }
  else
    cube->writeCube();
} // loop

// move snake forward by one cell
void moveSnake()
{
  Cell *newHead
    = new Cell(snake->xPos, snake->yPos, snake->zPos);
  
  newHead->xPos += Direction::xDelta(snakeDirection);
  newHead->yPos += Direction::yDelta(snakeDirection);
  newHead->zPos += Direction::zDelta(snakeDirection);

  // only move if new position doesnt cause snake to crash
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
  // snake must have crashed at this point
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

// animation to end game, delete unused objects and restart game
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

// place food at random coordinates
void placeFood()
{
  byte foodX, foodY, foodZ;
  // dont place food at an occupied location
  do
  {
    foodX = random(0, 8);
    foodY = random(0, 8);
    foodZ = random(0, 8);
  } while(cube->ledStatus[foodX][foodY][foodZ] != LOW);
  
  food = new Cell(foodX, foodY, foodZ);
}

// check if new position is occupied or out of bounds
boolean checkCrash(Cell *newHead)
{
  byte x = newHead->xPos, y = newHead->yPos, z = newHead->zPos;
  return (x < 0) || (x > 7)
            || (y < 0) || (y > 7)
            || (z < 0) || (z > 7)
            || snake->contains(newHead);
}

// delete the last segment of the snake
void moveTail()
{
  snake->deleteLast();
}

// update the cube display with current snake and food
void updateCube()
{
  cube->clearAll();

  // recursively update the cube with the snake position
  snake->updateCube(cube);
  // update the cube with the food position
  food->updateCube(cube);
} // updateCube

// place snake and food in initial positions
void setInitialState()
{
  gameRunning = false;
  noOfLives = 1;
  snakeLength = 4;
  snakeDirection = Direction::FORWARD;
  
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

