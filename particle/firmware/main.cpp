#include "application.h"
STARTUP(WiFi.selectAntenna(ANT_AUTO));

// 1XX 1XX 1XX 1XX
// fl - fr - bl - br
// 1 = Move forward; 2 = Move backwards; 0 = Don't move
// XX = speed / 5 ; if XX == 51; then speed = 255 ..; if XX == 00; then speed == 0

int moveMotors(String command)
{
  String flcom = command.substring(0,3);
  String frcom = command.substring(4,7);
  String blcom = command.substring(8,11);
  String brcom = command.substring(12,15);

  Serial1.println("fl " + flcom);
  Serial.println("fl " + flcom);
  delay(50);
  Serial1.println("fr " + frcom);
  Serial.println("fr " + frcom);
  delay(50);
  Serial1.println("bl " + blcom);
  Serial.println("bl " + blcom);
  delay(50);
  Serial1.println("br " + brcom);
  Serial.println("br " + brcom);

  return 1;
}

int flip(String command)
{
  if (command == "flip")
  {
    Serial1.println(command);
  }
  if (command == "stopflip")
  {
    Serial1.println(command);
  }
  return 1;
}

void setup()
{
Particle.function("move", moveMotors);
Particle.function("flip", flip);
Serial1.begin(9600);
Serial.begin(9600);

}

void loop()
{

}
