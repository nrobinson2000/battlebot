# Stuff To do:
* Connect power to weapon and board
* Drill hole for DC
* Connect relay for weapon
* Make 'spatula'


"backward"

digitalWrite(FL_DIR, HIGH);  // Set front left motor to forwards
FL_FORWARDS = false;

digitalWrite(FR_DIR, HIGH); // Set front right motor to forwards
FR_FORWARDS = false;

digitalWrite(BL_DIR, LOW); // Set back left motor to forwards
FR_FORWARDS = false;

digitalWrite(BR_DIR, LOW);  // Set back right motor to forwards
BR_FORWARDS = false;

"forward"

digitalWrite(FL_DIR, LOW);  // Set front left motor to forwards
FL_FORWARDS = true;

digitalWrite(FR_DIR, LOW); // Set front right motor to forwards
FR_FORWARDS = true;

digitalWrite(BL_DIR, HIGH); // Set back left motor to forwards
FR_FORWARDS = true;

digitalWrite(BR_DIR, HIGH);  // Set back right motor to forwards
BR_FORWARDS = true;
