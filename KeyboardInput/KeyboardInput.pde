import java.util.HashSet;
import processing.serial.*;

private static Serial arduinoPort = null;
private static HashSet<Integer> acceptedKeys;

void setup()
{
  // open a connection to the arduino (serial port at index 1)
  try
  {
    arduinoPort = new Serial(this, Serial.list()[1], 9600);
    arduinoPort.bufferUntil('\n');
  }
  catch(ArrayIndexOutOfBoundsException e)
    { println("No serial port available at index 1"); }
  catch(NullPointerException e)
    { println("Failed to open serial port"); }
    
  acceptedKeys = new HashSet<Integer>();
  acceptedKeys.add(87); // W
  acceptedKeys.add(83); // S
  acceptedKeys.add(65); // A
  acceptedKeys.add(68); // D
  acceptedKeys.add(33); // PgUp
  acceptedKeys.add(34); // PgDn
} // setup

void draw()
{
} // draw

// method is called every time keyboard input detected
void keyPressed()
{
  if(acceptedKeys.contains(keyCode))
    arduinoPort.write(keyCode);
  println("pressed " + int(key) + " " + keyCode);
} // keyPressed