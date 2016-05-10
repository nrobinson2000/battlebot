//  //  //  //  //  //  //  //
//  BATTLE BOT WITH FLIPPER //
//  by Nathan Robinson      //
//  GPL, 2016               //
//  //  //  //  //  //  //  //

// Libraries
#include <SoftwareSerial.h>
#include <PS2X.h>

#define FL_PWM 7
#define FR_PWM 6  // Robot PWM Pins
#define BL_PWM 5
#define BR_PWM 4

#define FL_DIR 28
#define FR_DIR 26  // Robot Direction Pins
#define BL_DIR 24
#define BR_DIR 22

#define FLIPPER 34

#define RED 0
#define GREEN 1
#define BLUE 2
#define YELLOW 3
#define ORANGE 4

PS2X ps2x; // create PS2 Controller Class

bool FL_FORWARDS = false;
bool FR_FORWARDS = false;  // Booleans for if motors are moving forwards
bool BL_FORWARDS = false;
bool BR_FORWARDS = false;

int FL_SPEED = 0;
int FR_SPEED = 0;  // Speed of motors
int BL_SPEED = 0;
int BR_SPEED = 0;

String readString = "";

void stop()
{
  analogWrite(FL_PWM, FL_SPEED / 2);
  analogWrite(FR_PWM, FR_SPEED / 2);  // Slow down halfway
  analogWrite(BL_PWM, BL_SPEED / 2);
  analogWrite(BR_PWM, BR_SPEED / 2);

  delay(150);

  analogWrite(FL_PWM, FL_SPEED / 4);
  analogWrite(FR_PWM, FR_SPEED / 4);  // Slow down to one quarter speed
  analogWrite(BL_PWM, BL_SPEED / 4);
  analogWrite(BR_PWM, BR_SPEED / 4);

  delay(150);

  analogWrite(FL_PWM, FL_SPEED * 0);
  analogWrite(FR_PWM, FR_SPEED * 0);  // Come to a complete stop
  analogWrite(BL_PWM, BL_SPEED * 0);
  analogWrite(BR_PWM, BR_SPEED * 0);

  FL_SPEED = 0;
  FR_SPEED = 0;  // Set speed variables to 0
  BL_SPEED = 0;
  BR_SPEED = 0;
}

void moveForwards(int speed, int wait)
{
  FL_SPEED = speed;
  FR_SPEED = speed;  // Set speed of motors
  BL_SPEED = speed;
  BR_SPEED = speed;

  digitalWrite(FL_DIR, LOW);  // Set front left motor to forwards
  FL_FORWARDS = true;

  digitalWrite(FR_DIR, LOW); // Set front right motor to forwards
  FR_FORWARDS = true;

  digitalWrite(BL_DIR, HIGH); // Set back left motor to forwards
  FR_FORWARDS = true;

  digitalWrite(BR_DIR, HIGH);  // Set back right motor to forwards
  BR_FORWARDS = true;


  analogWrite(FL_PWM, FL_SPEED);
  analogWrite(FR_PWM, FR_SPEED); // Tell motors to go at a certain speed
  analogWrite(BL_PWM, BL_SPEED);
  analogWrite(BR_PWM, BR_SPEED);
  delay(wait);
  stop();
}

void moveBackwards(int speed, int wait)
{
  FL_SPEED = speed;
  FR_SPEED = speed;  // Set speed of motors
  BL_SPEED = speed;
  BR_SPEED = speed;

  digitalWrite(FL_DIR, HIGH);  // Set front left motor to forwards
  FL_FORWARDS = false;

  digitalWrite(FR_DIR, HIGH); // Set front right motor to forwards
  FR_FORWARDS = false;

  digitalWrite(BL_DIR, LOW); // Set back left motor to forwards
  FR_FORWARDS = false;

  digitalWrite(BR_DIR, LOW);  // Set back right motor to forwards
  BR_FORWARDS = false;

  analogWrite(FL_PWM, FL_SPEED);
  analogWrite(FR_PWM, FR_SPEED); // Tell motors to go at a certain speed
  analogWrite(BL_PWM, BL_SPEED);
  analogWrite(BR_PWM, BR_SPEED);
  delay(wait);
  stop();
}

void moveRight(int speed, int wait)
{
  FL_SPEED = speed;
  FR_SPEED = speed;  // Set speed of motors
  BL_SPEED = speed;
  BR_SPEED = speed;

  digitalWrite(FL_DIR, LOW);  // Set front left motor to backwards
  FL_FORWARDS = false;

  digitalWrite(FR_DIR, HIGH);  // Set front right motor to forwards
  FR_FORWARDS = true;

  digitalWrite(BL_DIR, HIGH);  // Set back left motor to backwards
  BL_FORWARDS = false;

  digitalWrite(BR_DIR, LOW);  // Set back right motor to forwards
  BR_FORWARDS = true;

  analogWrite(FL_PWM, FL_SPEED);
  analogWrite(FR_PWM, FR_SPEED); // Tell motors to go at a certain speed
  analogWrite(BL_PWM, BL_SPEED);
  analogWrite(BR_PWM, BR_SPEED);
  delay(wait);
  stop();
}

void moveLeft(int speed, int wait)
{
  FL_SPEED = speed;
  FR_SPEED = speed;  // Set speed of motors
  BL_SPEED = speed;
  BR_SPEED = speed;

  digitalWrite(FL_DIR, HIGH);  // Set front left motor to forwards
  FL_FORWARDS = true;

  digitalWrite(FR_DIR, LOW);  // Set front right motor to backwards
  FR_FORWARDS = false;

  digitalWrite(BL_DIR, LOW);  // Set back left motor to forwards
  BL_FORWARDS = true;

  digitalWrite(BR_DIR, HIGH);  // Set back right motor to backwards
  BR_FORWARDS = false;

  analogWrite(FL_PWM, FL_SPEED);
  analogWrite(FR_PWM, FR_SPEED); // Tell motors to go at a certain speed
  analogWrite(BL_PWM, BL_SPEED);
  analogWrite(BR_PWM, BR_SPEED);
  delay(wait);
  stop();
}

void flip()
{
  digitalWrite(FLIPPER, LOW);  //  Activate the flipper for time miliseconds
}

void stopflip()
{
  digitalWrite(FLIPPER, HIGH);
}

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);

  ps2x.config_gamepad(47, 51, 49, 53); // Clock => 47, Command=> 51, Attention => 49, Data => 53

  pinMode(FL_PWM, OUTPUT);
  pinMode(FR_PWM, OUTPUT);  //  Set PWMs to OUTPUT
  pinMode(BL_PWM, OUTPUT);
  pinMode(BR_PWM, OUTPUT);

  pinMode(FL_DIR, OUTPUT);
  pinMode(FR_DIR, OUTPUT);  // Set DIRs to OUTPUT
  pinMode(BL_DIR, OUTPUT);
  pinMode(BR_DIR, OUTPUT);

  pinMode(FLIPPER, OUTPUT);

  Serial.begin(9600);
  Serial1.begin(9600);
  digitalWrite(FLIPPER, HIGH);
}

// 1XX 1XX 1XX 1XX
// fl-fr-bl-br
// 1 = Move forward; 2 = Move backwards; 0 = Don't move
// XX = speed / 5 ; if XX == 51; then speed = 255 ..; if XX == 00; then speed == 0




void parseCommand(String command)
{
  String cmd = command.substring(3);

  if (command.startsWith("fl"))
  {
    String dir = String(cmd.charAt(0));
    String speed = cmd.substring(1,3);

    if (dir == "1")
    {
      digitalWrite(FL_DIR, LOW);  // Set front left motor to forwards
      FL_FORWARDS = true;
      analogWrite(FL_PWM, speed.toInt() * 5);
    }

    if (dir == "2")
    {
      digitalWrite(FL_DIR, HIGH);  // Set front left motor to backwards
      FL_FORWARDS = false;
      analogWrite(FL_PWM, speed.toInt() * 5);
    }

    if (dir == "0")
    {
      analogWrite(FL_PWM, 0);
    }
  }

  if (command.startsWith("fr"))
  {
    String dir = String(cmd.charAt(0));
    String speed = cmd.substring(1,3);

    if (dir == "1")
    {
      digitalWrite(FR_DIR, LOW); // Set front right motor to forwards
      FR_FORWARDS = true;
      analogWrite(FR_PWM, speed.toInt() * 5);
    }

    if (dir == "2")
    {
      digitalWrite(FR_DIR, HIGH);  // Set front left motor to backwards
      FR_FORWARDS = false;
      analogWrite(FR_PWM, speed.toInt() * 5);
    }

    if (dir == "0")
    {
      analogWrite(FR_PWM, 0);
    }
  }

  if (command.startsWith("bl"))
  {
    String dir = String(cmd.charAt(0));
    String speed = cmd.substring(1,3);

    if (dir == "1")
    {
      digitalWrite(BL_DIR, HIGH); // Set front right motor to forwards
      BL_FORWARDS = true;
      analogWrite(BL_PWM, speed.toInt() * 5);
    }

    if (dir == "2")
    {
      digitalWrite(BL_DIR, LOW);  // Set front left motor to backwards
      BL_FORWARDS = false;
      analogWrite(BL_PWM, speed.toInt() * 5);
    }

    if (dir == "0")
    {
      analogWrite(BL_PWM, 0);
    }
  }

  if (command.startsWith("br"))
  {
    String dir = String(cmd.charAt(0));
    String speed = cmd.substring(1,3);

    if (dir == "1")
    {
      digitalWrite(BR_DIR, HIGH); // Set front right motor to forwards
      BR_FORWARDS = true;
      analogWrite(BR_PWM, speed.toInt() * 5);
    }

    if (dir == "2")
    {
      digitalWrite(BR_DIR, LOW);  // Set front left motor to backwards
      BR_FORWARDS = false;
      analogWrite(BR_PWM, speed.toInt() * 5);
    }

    if (dir == "0")
    {
      analogWrite(BR_PWM, 0);
    }
  }

  if (command == "flip")
  {
    flip();
  }

  if (command == "stopflip")
  {
    stopflip();
  }
}

void loop()
{

  while (Serial1.available())
  {
    delay(3);
    char c = Serial1.read();
    readString += c;
  }

  readString.trim();

  if (readString.length() > 0)
  {
    Serial.println("Command: " + readString);
    parseCommand(readString);
    readString = "";
  }
}
