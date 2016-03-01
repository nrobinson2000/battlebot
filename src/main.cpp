//  //  //  //  //  //  //  //
//  BATTLE BOT WITH FLIPPER //
//  by Nathan Robinson      //
//  GPL, 2016               //
//  //  //  //  //  //  //  //

// Libraries
#include <PS2X.h> //  PS2 Controller
#include <SoftwareSerial.h>

#define FL_PWM 7
#define FR_PWM 6  // Robot PWM Pins
#define BL_PWM 5
#define BR_PWM 4

#define FL_DIR 28
#define FR_DIR 26  // Robot Direction Pins
#define BL_DIR 24
#define BR_DIR 22
#define FLIPPER 50

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

  digitalWrite(FL_DIR, HIGH);  // Set front left motor to forwards
  FL_FORWARDS = true;

  digitalWrite(FR_DIR, HIGH); // Set front right motor to forwards
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

  digitalWrite(FL_DIR, LOW);  // Set front left motor to backwards
  FL_FORWARDS = false;

  digitalWrite(FR_DIR, LOW);  // Set front right motor to backwards
  FR_FORWARDS = false;

  digitalWrite(BL_DIR, LOW);  // Set back left motor to backwards
  BL_FORWARDS = false;

  digitalWrite(BR_DIR, LOW);  // Set back right motor to backwards
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

  digitalWrite(BL_DIR, LOW);  // Set back left motor to backwards
  BL_FORWARDS = false;

  digitalWrite(BR_DIR, HIGH);  // Set back right motor to forwards
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

  digitalWrite(BL_DIR, HIGH);  // Set back left motor to forwards
  BL_FORWARDS = true;

  digitalWrite(BR_DIR, LOW);  // Set back right motor to backwards
  BR_FORWARDS = false;

  analogWrite(FL_PWM, FL_SPEED);
  analogWrite(FR_PWM, FR_SPEED); // Tell motors to go at a certain speed
  analogWrite(BL_PWM, BL_SPEED);
  analogWrite(BR_PWM, BR_SPEED);
  delay(wait);
  stop();

}

void flip(int time)
{
  digitalWrite(FLIPPER, HIGH);  //  Activate the flipper for time miliseconds
  delay(time);
  digitalWrite(FLIPPER, LOW);  // Turn off flipper
}

void setup()
{
  Serial.begin(9600);
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

  Serial1.begin(9600);

}

void loop()
{

  float flip_bar = ps2x.Analog(WHAMMY_BAR);
  ps2x.read_gamepad();


  if (ps2x.ButtonPressed(RED_FRET))
  {
    moveForwards(255, 100);
  }

  if (ps2x.ButtonReleased(RED_FRET))
  {
    stop();
  }

  if (ps2x.ButtonPressed(GREEN_FRET))
  {
    moveBackwards(255, 100);
  }

  if (ps2x.ButtonReleased(GREEN_FRET))
  {
    stop();
  }

  if (ps2x.ButtonPressed(BLUE_FRET))
  {

  }

  if (ps2x.ButtonReleased(BLUE_FRET))
  {

  }

  if (ps2x.ButtonPressed(YELLOW_FRET))
  {
    digitalWrite(FLIPPER, LOW);
  }

  if (ps2x.ButtonReleased(YELLOW_FRET))
  {
    digitalWrite(FLIPPER, HIGH);
  }

  if (ps2x.ButtonPressed(ORANGE_FRET))
  {
    flip(500);
  }
  if (ps2x.ButtonReleased(ORANGE_FRET))
  {

  }

  //only turn a color on it if strummed
  if (ps2x.ButtonPressed(UP_STRUM))
  {
    moveRight(70, 100);
  }

  if (ps2x.ButtonPressed(DOWN_STRUM))
  {
    moveLeft(70, 100);
  }

  if (ps2x.ButtonReleased(UP_STRUM))
  {
    stop();
  }

  if (ps2x.ButtonReleased(DOWN_STRUM))
  {
    stop();
  }

  if (flip_bar == 0)
  {
    digitalWrite(FLIPPER, LOW);
  }

  if (flip_bar > 0)
  {
    digitalWrite(FLIPPER, HIGH);
  }

}
