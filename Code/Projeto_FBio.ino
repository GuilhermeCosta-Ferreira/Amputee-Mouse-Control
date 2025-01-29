//Defining Variables
int samplingFrequence = 10, samplingPeriod = 0;
unsigned long currentTime = 0, previousTime4Sampling = 0;
int xPin = A0, yPin = A1, zPin = A2, buttonPin = 2, rbuttonPin = 4, ledPin = 3;
int xValue = 0, yValue = 0, zValue = 0;
int buttonState = 0, rbuttonState = 0, blinking = 0;
bool alreadyClicked = false, alreadyClickedR;

void setup() 
{
  Serial.begin(9600);
  //pinMode(sensorPin, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(rbuttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  samplingPeriod = int(1000*1 / (float)samplingFrequence);
}

void loop() 
{
  currentTime = millis();
  if (currentTime - previousTime4Sampling >= samplingPeriod) {
        readAndStreamSensorValue(xPin, yPin, zPin, currentTime);
        previousTime4Sampling = currentTime;
        leftButton(buttonPin);
        rightButton(rbuttonPin);
  }

  while (Serial.available() > 0) {
    // update blinking period
    blinking = Serial.parseInt();
  }
  ledState(ledPin, blinking);
}

//|----------FUNCTIONS----------|

//Function tho get the signal values (and plot them)
void readAndStreamSensorValue(int xPin, int yPin, int zPin, long currentTime) 
{
    xValue = analogRead(xPin);
    yValue = analogRead(yPin);
    zValue = analogRead(zPin);
  
    Serial.print(currentTime);
    Serial.print(",");
    Serial.print(xValue);
    Serial.print(",");
    Serial.print(yValue);
    Serial.print(",");
    Serial.println(zValue);
}

void leftButton(int buttonPin)
{
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH && !alreadyClicked) {
    alreadyClicked = true;

    Serial.println("Click");
  }
  else if (buttonState == LOW && alreadyClicked){
    alreadyClicked = false;
  }
}

void rightButton(int rbuttonPin)
{
  rbuttonState = digitalRead(rbuttonPin);

  if (rbuttonState == HIGH && !alreadyClickedR) {
    alreadyClickedR = true;

    Serial.println("RClick");
  }
  else if (rbuttonState == LOW && alreadyClickedR){
    alreadyClickedR = false;
  }
}

void ledState(int ledPin, int blinking)
{
  if(blinking == 1)
  {
    digitalWrite(ledPin, LOW); 
    delay(250);
    digitalWrite(ledPin, HIGH);   
    delay(250);     
  }
  else digitalWrite(ledPin, HIGH);
}
