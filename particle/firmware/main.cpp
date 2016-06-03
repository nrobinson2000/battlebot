#include "application.h"
#include <IRremote.h>

// STARTUP(WiFi.selectAntenna(ANT_AUTO));


int RECV_PIN = D0;
int ledpin = D2;
bool flipping = false;

IRrecv irrecv(RECV_PIN);

decode_results results;


// 1XX 1XX 1XX 1XX
// fl - fr - bl - br
// 1 = Move forward; 2 = Move backwards; 0 = Don't move
// XX = speed / 5 ; if XX == 51; then speed = 255 ..; if XX == 00; then speed == 0

int move(String command)
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

void parse(int x)
{
  if (x == 0xFD00FF)
  {
    Serial.println("Button pressed!");
    if (flipping == true)
    {
      Serial1.println("stopflip");
      Serial.println("stopflip");
      flipping = false;
    }
    else
    {
      Serial1.println("flip");
      Serial.println("flip");
      flipping = true;
    }
  }

  if (x == 0xFD807F)
  {
    move("151 151 151 151"); // Forwards
  }

  if (x == 0xFD906F)
  {
    move("251 251 251 251"); // Backwards
  }

  if (x == 0xFD20DF)
  {
    move("235 135 235 135"); // Counter-clockwise
  }

  if (x == 0xFDA05F)
  {
    move("135 235 135 235"); // Clockwise
  }

  if (x == 0xFD40BF)
  {
    move("000 000 000 000");
  }

}


void setup()
{
Particle.function("move", move);
Particle.function("flip", flip);
Serial1.begin(9600);
Serial.begin(9600);
irrecv.enableIRIn(); // Start the receiver
}

void loop()
{
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    parse(results.value);
    irrecv.resume(); // Receive the next value
  }
}
