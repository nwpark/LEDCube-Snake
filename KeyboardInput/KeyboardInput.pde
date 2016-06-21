import processing.serial.*;

private static Serial arduinoPort = null;

void setup()
{
  // open a connection to the arduino (serial port at index 1)
  try
  {
    arduinoPort = new Serial(this, Serial.list()[1], 250000);
    arduinoPort.bufferUntil('\n');
  }
  catch(ArrayIndexOutOfBoundsException e)
    { println("No serial port available at index 1"); }
  catch(NullPointerException e)
    { println("Failed to open serial port"); }
} // setup

void draw()
{
} // draw

void keyPressed()
{
  arduinoPort.write(key);
} // keyPressed