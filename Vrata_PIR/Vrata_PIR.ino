#define PIN_PIR_HALLWAY   11
#define PIN_PIR_STAIRS    10
#define PIN_LED_PWM       3
#define PIN_LED_PWM_DEBUG 13

#define EXECUTE_TIME 30 // every 30ms

int lightsOn(bool); // accepts 1 or 0 to turn lights on or off.

void setup() {
  pinMode(PIN_PIR_HALLWAY, INPUT);
  pinMode(PIN_PIR_STAIRS, INPUT);
  Serial.begin(9600);
}

void loop() {
  bool pirHallway = digitalRead(PIN_PIR_HALLWAY);
  bool pirStairs = digitalRead(PIN_PIR_STAIRS);


  bool lightOnSignal = (pirHallway || pirStairs);
  
  Serial.println(lightOnSignal);
  lightsOn(lightOnSignal);
}

int lightsOn(bool inputPIR)
{
  static unsigned long lastExecuteTime = 0;
  unsigned long currentTime = millis();
  static int valuePWM = 0;

  if (currentTime - lastExecuteTime > EXECUTE_TIME)
  {
    valuePWM += 4*inputPIR - 2*(!inputPIR); // if PIR 1 then add 2, else subtract 1
    if (valuePWM > 255) valuePWM = 255;
    if (valuePWM < 0) valuePWM = 0;
    lastExecuteTime = currentTime;
  }
  if (inputPIR)
  {
    if (valuePWM < 50)
    {
      valuePWM = 50;
    }
  }
  
  Serial.print(valuePWM);
  analogWrite(PIN_LED_PWM, valuePWM);
  analogWrite(PIN_LED_PWM_DEBUG, valuePWM);
}
