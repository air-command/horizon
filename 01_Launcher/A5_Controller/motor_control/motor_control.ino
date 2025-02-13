// Horizon Launcher - Motor controller
// George Katz 1st January 2019

//#include <Servo.h>

// =================== State Definitions ================================

const int STATE_FILL_START      = 0;
const int STATE_FILL_CLOSED     = 1;
const int STATE_FILL_CLOSING    = 2;
const int STATE_FILL_OPEN       = 3;
const int STATE_FILL_OPENING    = 4;

const int STATE_VENT_START      = 0;
const int STATE_VENT_CLOSED     = 1;
const int STATE_VENT_CLOSING    = 2;
const int STATE_VENT_OPEN       = 3;
const int STATE_VENT_OPENING    = 4;

const int STATUS_LED_OFF		    = 0;
const int STATUS_LED_ON			    = 1;
const int STATUS_LED_FLASH		  = 2;

// =================== Pin definitions ================================
const int FILL_MOTOR_OPEN       = 21;
const int FILL_MOTOR_CLOSE      = 20;
const int VENT_MOTOR_OPEN       = 19;
const int VENT_MOTOR_CLOSE      = 18;

const int LAUNCH_SERVO          = 9;

const int FILL_LIMIT_OPEN       = 15;
const int FILL_LIMIT_CLOSED     = 14;
const int VENT_LIMIT_OPEN       = 16;
const int VENT_LIMIT_CLOSED     = 10;

const int VENT_OPEN_BTN         = 6;
const int FILL_OPEN_BTN         = 7;
const int LAUNCH_BTN            = 8;

const int VENT_OPEN_RPI         = 1;
const int FILL_OPEN_RPI         = 0;
const int LAUNCH_RPI            = 2;

const int VENT_LED				      = 3;
const int FILL_LED				      = 4;
const int LAUNCH_LED			      = 5;

// ==================== Variables ====================================
//Servo launchServo;  // create servo object to control a servo

int launchState               = 0;        // 
unsigned long previousMillis  = 0;        // 
const long interval           = 500;      // 

bool flasher                   = false;					// This value continuously toggles on and off to flash LEDs
const long flashPeriod         = 50;        // period at which to flash LEDs (milliseconds)
unsigned long previousMillis2  = 0;        // 

int fillLimitOpen   = 0;              // Limit Switches
int fillLimitClosed = 0;
int ventLimitOpen   = 0;
int ventLimitClosed = 0;

int fillBtn         = 0;              // Manual Switches
int ventBtn         = 0;
int launchBtn       = 0;

int fill_state      = STATE_FILL_START;   // state of valve motor
int vent_state      = STATE_VENT_START;

int fillLEDState 	  = STATUS_LED_OFF;	    // Status LEDs
int ventLEDState 	  = STATUS_LED_OFF;	
int launchLEDState 	= STATUS_LED_OFF;	

//int servoStartPos   = 60;
//int servoEndPos     = 100;

void setup() {
  pinMode(FILL_MOTOR_OPEN,OUTPUT);          // 
  pinMode(FILL_MOTOR_CLOSE,OUTPUT);         // 
  pinMode(VENT_MOTOR_OPEN,OUTPUT);          // 
  pinMode(VENT_MOTOR_CLOSE,OUTPUT);         // 
  pinMode(LAUNCH_SERVO,OUTPUT);             // 
  pinMode(FILL_LIMIT_OPEN,INPUT_PULLUP);    // 
  pinMode(FILL_LIMIT_CLOSED,INPUT_PULLUP);  // 
  pinMode(VENT_LIMIT_OPEN,INPUT_PULLUP);    // 
  pinMode(VENT_LIMIT_CLOSED,INPUT_PULLUP);  // 
  pinMode(VENT_OPEN_BTN,INPUT_PULLUP);      // 
  pinMode(FILL_OPEN_BTN,INPUT_PULLUP);      // 
  pinMode(LAUNCH_BTN,INPUT_PULLUP);         // 
  pinMode(VENT_OPEN_RPI,INPUT);             // 
  pinMode(FILL_OPEN_RPI,INPUT);             // 
  pinMode(LAUNCH_RPI,INPUT);                // 
  pinMode(VENT_LED,OUTPUT);             	// 
  pinMode(FILL_LED,OUTPUT);             	// 
  pinMode(LAUNCH_LED,OUTPUT);             	// 

  Serial.begin(9600); //This pipes to the serial monitor

  setFillState(STATE_FILL_START);
  setVentState(STATE_VENT_START);

  digitalWrite(LAUNCH_SERVO,  LOW);

//  launchServo.attach(LAUNCH_SERVO);
//  launchServo.write(servoStartPos);

}


void setFillState(int newState) {
  fill_state = newState;
 
  switch(fill_state){
    case STATE_FILL_START:
      digitalWrite(FILL_MOTOR_OPEN,  LOW);    // motor off
      digitalWrite(FILL_MOTOR_CLOSE, LOW);
    break;
    
    case STATE_FILL_CLOSED:
      digitalWrite(FILL_MOTOR_OPEN,  LOW);    // motor off
      digitalWrite(FILL_MOTOR_CLOSE, LOW);
	    fillLEDState 	= STATUS_LED_OFF;	
    break;
    
    case STATE_FILL_CLOSING:
      digitalWrite(FILL_MOTOR_OPEN,  LOW);    // motor moving to close valve
      digitalWrite(FILL_MOTOR_CLOSE, HIGH);
	    fillLEDState 	= STATUS_LED_FLASH;	
    break;
    
    case STATE_FILL_OPEN:
      digitalWrite(FILL_MOTOR_OPEN,  LOW);    // motor off
      digitalWrite(FILL_MOTOR_CLOSE, LOW);    
	    fillLEDState 	= STATUS_LED_ON;	
    break;
    
    case STATE_FILL_OPENING:
      digitalWrite(FILL_MOTOR_OPEN,  HIGH);   // motor moving to open valve
      digitalWrite(FILL_MOTOR_CLOSE, LOW);
	    fillLEDState 	= STATUS_LED_FLASH;	
    break;
  }

  if(fillLEDState == STATUS_LED_OFF) {
    digitalWrite(FILL_LED,  HIGH);
  } else if(fillLEDState == STATUS_LED_ON) {
    digitalWrite(FILL_LED,  LOW);
  }

}


void setVentState(int newState) {
  vent_state = newState;
 
  switch(vent_state){
    case STATE_VENT_START:
      digitalWrite(VENT_MOTOR_OPEN,  LOW);    // motor off
      digitalWrite(VENT_MOTOR_CLOSE, LOW);
    break;
    
    case STATE_VENT_CLOSED:
      digitalWrite(VENT_MOTOR_OPEN,  LOW);    // motor off
      digitalWrite(VENT_MOTOR_CLOSE, LOW);
	    ventLEDState 	= STATUS_LED_OFF;	
    break;
    
    case STATE_VENT_CLOSING:
      digitalWrite(VENT_MOTOR_OPEN,  LOW);    // motor moving to close valve
      digitalWrite(VENT_MOTOR_CLOSE, HIGH);
	    ventLEDState 	= STATUS_LED_FLASH;	
    break;
    
    case STATE_VENT_OPEN:
      digitalWrite(VENT_MOTOR_OPEN,  LOW);    // motor off
      digitalWrite(VENT_MOTOR_CLOSE, LOW);    
	    ventLEDState 	= STATUS_LED_ON;	
    break;
    
    case STATE_VENT_OPENING:
      digitalWrite(VENT_MOTOR_OPEN,  HIGH);   // motor moving to open valve
      digitalWrite(VENT_MOTOR_CLOSE, LOW);
	    ventLEDState 	= STATUS_LED_FLASH;	
    break;
  }

  if(ventLEDState == STATUS_LED_OFF) {
    digitalWrite(VENT_LED,  HIGH);
  } else if(ventLEDState == STATUS_LED_ON) {
    digitalWrite(VENT_LED,  LOW);
  }
}


void loop() {
  //read limit switches
  fillLimitOpen   = !digitalRead(FILL_LIMIT_OPEN);   // Fill motor in fully open position    - air flowing in
  fillLimitClosed = !digitalRead(FILL_LIMIT_CLOSED); // Fill motor in fully closed position  - no air flowing in
  ventLimitOpen   = !digitalRead(VENT_LIMIT_OPEN);
  ventLimitClosed = !digitalRead(VENT_LIMIT_CLOSED);

  // read manual override switches
  // We combine these with the requests coming in from the Raspberry Pi.
  fillBtn         = digitalRead(FILL_OPEN_BTN) && digitalRead(FILL_OPEN_RPI);
  ventBtn         = digitalRead(VENT_OPEN_BTN) && digitalRead(VENT_OPEN_RPI);
  launchBtn       = digitalRead(LAUNCH_BTN)    && digitalRead(LAUNCH_RPI);

  // ========== Fill State Machine =================
  switch(fill_state){
    case STATE_FILL_START:
      if(fillLimitClosed) {   // already at limnit
        setFillState(STATE_FILL_CLOSED);
      } else {
        setFillState(STATE_FILL_CLOSING);
      }
    break;
    
    case STATE_FILL_CLOSED:
      if(fillBtn) {
        setFillState(STATE_FILL_OPENING);
      }
    break;
    
    case STATE_FILL_CLOSING:
      if(fillLimitClosed) {   // already at limnit
        setFillState(STATE_FILL_CLOSED);
      }
      if(fillBtn && !fillLimitOpen) {
        setFillState(STATE_FILL_OPENING);
      }
    break;
    
    case STATE_FILL_OPEN:
      if(!fillBtn) {
        setFillState(STATE_FILL_CLOSING);
      }
    break;
    
    case STATE_FILL_OPENING:
      if(fillLimitOpen) {   // already at limnit
        setFillState(STATE_FILL_OPEN);
      }
      if(!fillBtn && !fillLimitClosed) {
        setFillState(STATE_FILL_CLOSING);
      }
    break;
  }

  // ========== Vent State Machine =================

  switch(vent_state){
    case STATE_VENT_START:
      if(ventLimitClosed) {   // already at limnit
        setVentState(STATE_VENT_CLOSED);
      } else {
        setVentState(STATE_VENT_CLOSING);
      }
    break;
    
    case STATE_VENT_CLOSED:
      if(ventBtn) {
        setVentState(STATE_VENT_OPENING);
      }
    break;
    
    case STATE_VENT_CLOSING:
      if(ventLimitClosed) {   // already at limnit
        setVentState(STATE_VENT_CLOSED);
      }
      if(ventBtn && !ventLimitOpen) {
        setVentState(STATE_VENT_OPENING);
      }
    break;
    
    case STATE_VENT_OPEN:
      if(!ventBtn) {
        setVentState(STATE_VENT_CLOSING);
      }
    break;
    
    case STATE_VENT_OPENING:
      if(ventLimitOpen) {   // already at limnit
        setVentState(STATE_VENT_OPEN);
      }
      if(!ventBtn && !ventLimitClosed) {
        setVentState(STATE_VENT_CLOSING);
      }
    break;
  }

  if(!launchBtn && !launchState) {
    launchState = 1;
//    launchServo.write(servoEndPos);
    digitalWrite(LAUNCH_SERVO,  HIGH);
    digitalWrite(LAUNCH_LED,  HIGH);
    previousMillis = millis();
  }

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval && launchState) {
    previousMillis = currentMillis;
//    launchServo.write(servoStartPos);
    digitalWrite(LAUNCH_SERVO,  LOW);
    digitalWrite(LAUNCH_LED,  LOW);
    launchState = 0;
  }

  //The following is used to flash the status LEDs when needed. 
  if (currentMillis - previousMillis2 >= flashPeriod) {
    previousMillis2 = currentMillis;
    flasher = !flasher;   //toggle
    if(fillLEDState == STATUS_LED_FLASH) {
      if(flasher) {
        digitalWrite(FILL_LED,  HIGH);
      } else {
        digitalWrite(FILL_LED,  LOW);    
      }
    }

    if(ventLEDState == STATUS_LED_FLASH) {
      if(flasher) {
        digitalWrite(VENT_LED,  HIGH);
      } else {
        digitalWrite(VENT_LED,  LOW);    
      }
    }

  }




}
