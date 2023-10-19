// Code by Joeri Ridder and some other fine folks.
// Code source for button pressing: https://www.arduino.cc/en/Tutorial/StateChangeDetection
// Code source for timer: https://www.arduino.cc/en/tutorial/BlinkWithoutDelay and https://forum.arduino.cc/index.php?topic=384760.0

/*#define DIPS1 16
#define B5 15
#define B6 2
#define BUZZER 23

const int b1 = 14;
const int b2 = 12;
const int b3 = 32;
const int b4 = 35;

const int led_azul = 26;
const int led_amarelo = 27;
const int led_verde = 25;
const int led_vermelho = 33;*/

const int but1Pin = 14;
const int but2Pin = 12;
const int but3Pin = 32;
const int but4Pin = 35;

const int led1Pin = 26;
const int led2Pin = 27;
const int led3Pin = 25;
const int led4Pin = 33;


int b1State = 0;
int b1LastState = 0;
int b2State = 0;
int b2LastState = 0;
int b3State = 0;
int b3LastState = 0;
int b4State = 0;
int b4LastState = 0;

int p1State = 1;                         // Player states: 0=out, 1=in, 2=win;
int p2State = 1;
int p3State = 1;
int p4State = 1;
int p1Points = 0;
int p2Points = 0;
int p3Points = 0;
int p4Points = 0;
const int pointsToWin = 5;              // Points needed to win the game.

bool deadZone = false;
unsigned long dZTimerStart = 0;
const long dZTimerDuration = 5000;     // Duration of the timer in milliseconds

bool gameWin = false;
unsigned long winTimerStart = 0;
const long winTimerDuration = 250;     // Duration of the timer in milliseconds
int winLedState = LOW;                 // State of the led of the winning player

unsigned long resetTimerStart = 0;
const long resetTimerDuration = 10000;   // Duration in milliseconds

void setup() {
  Serial.begin(9600);
  pinMode(but1Pin, INPUT);
  pinMode(but2Pin, INPUT);
  pinMode(but3Pin, INPUT);
  pinMode(but4Pin, INPUT);
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  pinMode(led4Pin, OUTPUT);
}

void loop() {
  // Button press testing
  b1LastState = ButtonTest(but1Pin, b1State, b1LastState, p1State, 1);
  b2LastState = ButtonTest(but2Pin, b2State, b2LastState, p2State, 2);
  b3LastState = ButtonTest(but3Pin, b3State, b3LastState, p3State, 3);
  b4LastState = ButtonTest(but4Pin, b4State, b4LastState, p4State, 4);

  // deadzone timer
  if (deadZone == true) {
    DeadZoneTimer();
  }

  // win timer
  if (gameWin == true) {
    WinTimer();
    ResetTimer();
  }

  // Player states
  PlayerLed(p1State, led1Pin);
  PlayerLed(p2State, led2Pin);
  PlayerLed(p3State, led3Pin);
  PlayerLed(p4State, led4Pin);

  // Debug to the console
  Debug();
}

int ButtonTest(int buttonPin, int state, int lastState, int playerState, int buttonNumber) {
  // Test if the state of the button is different from the last recorded state. If so, and the digitalRead is now HIGH, the button has been pressed.
  state = digitalRead(buttonPin);
  if (state != lastState) {
    if (state == HIGH) {
      Serial.print("Button ");
      Serial.print(buttonNumber);
      Serial.println(" was pushed");
      if (playerState == 1 and !gameWin) {
        ButtonPressed(buttonNumber);
      }
    }
    delay(50); // delay a little bit to avoid bouncing
  }
  return state;
}

void ButtonPressed(int playerNumber) {
  if (deadZone == true) {
    // If a player hit the button during the deadzone, they loose.
    if (playerNumber == 1) { p1State = 0; }
    if (playerNumber == 2) { p2State = 0; }
    if (playerNumber == 3) { p3State = 0; }
    if (playerNumber == 4) { p4State = 0; }
  }
  else {
    // If a player hit the button after the deadzone they get a point.
    // They win if they have enough points.
    if (playerNumber == 1) {
      p1Points++;
      if (p1Points >= pointsToWin) { PlayerWin(2, 0, 0, 0); }
    }
    if (playerNumber == 2) {
      p2Points++;
      if (p2Points >= pointsToWin) { PlayerWin(0, 2, 0, 0); }
    }
    if (playerNumber == 3) {
      p3Points++;
      if (p3Points >= pointsToWin) { PlayerWin(0, 0, 2, 0); }
    }
    if (playerNumber == 4) {
      p4Points++;
      if (p4Points >= pointsToWin) { PlayerWin(0, 0, 0, 2); }
    }
    // Start the deadzone!
    dZTimerStart = millis();
    deadZone = true;
  }
  
  // When only one player is left, that player wins. (The sum of the player states is 1 when only one player is in the game)
  if (p1State + p2State + p3State + p4State == 1) {
    if (p1State == 1) { PlayerWin(2, 0, 0, 0); }
    if (p2State == 1) { PlayerWin(0, 2, 0, 0); }
    if (p3State == 1) { PlayerWin(0, 0, 2, 0); }
    if (p4State == 1) { PlayerWin(0, 0, 0, 2); }
  }
}

void PlayerLed(int playerState, int ledPin) {
  int ledState;
  if (playerState == 0) { ledState = LOW; }
  if (playerState == 1) { ledState = HIGH; }
  if (playerState == 2) { ledState = winLedState; }
  digitalWrite(ledPin, ledState);
}

void PlayerWin(int p1NewState, int p2NewState, int p3NewState, int p4NewState) {
  winTimerStart = millis();
  resetTimerStart = millis();
  gameWin = true;
  // Set the state of the player to the given states. Winning player gets 2 (win), everone else gets 0 (loose).
  p1State = p1NewState;
  p2State = p2NewState;
  p3State = p3NewState;
  p4State = p4NewState;
}

void WinTimer() {
  if (millis() - winTimerStart >= winTimerDuration) {
    winTimerStart = millis();
    if (winLedState == LOW) {
      winLedState = HIGH;
    } else {
      winLedState = LOW;
    }
  }
}

void ResetTimer() {
  if (millis() - resetTimerStart >= resetTimerDuration) {
    // Reset all important variables so the game can be player again.
    p1State = 1;
    p2State = 1;
    p3State = 1;
    p4State = 1;
    p1Points = 0;
    p2Points = 0;
    p3Points = 0;
    p4Points = 0;
    deadZone = false;
    gameWin = false;
    dZTimerStart = 0;
    winTimerStart = 0;
    resetTimerStart = 0;
  }
}

void DeadZoneTimer() {
  if (millis() - dZTimerStart >= dZTimerDuration) {
    deadZone = false;
  }
}

void Debug() {
  /*
  Serial.print("b1State = ");
  Serial.print(b1State);
  Serial.print(" | b2State = ");
  Serial.print(b2State);
  Serial.print(" | b3State = ");
  Serial.print(b3State);
  Serial.print(" | b4State = ");
  Serial.println(b4State);
  delay(10);
  */

  Serial.print("p1State = ");
  Serial.print(p1State);
  Serial.print(" | p2State = ");
  Serial.print(p2State);
  Serial.print(" | p3State = ");
  Serial.print(p3State);
  Serial.print(" | p4State = ");
  Serial.print(p4State);
  Serial.print(" | timer = ");
  Serial.print(millis() - dZTimerStart);
  Serial.print(" | deadZone = ");
  Serial.println(deadZone);
}
