#include <Pixy2.h>
Pixy2 pixy;

/* PIN DECLARATION */
const int gateOpen = 30;  //pinnen kunnen gedraaid worden // contactor om poort open te doen
const int gateClose = 31; //idem              // contactor om poort te sluiten

const int buttonOpen = 4;  // drukknop om poort te open
const int buttonClose = 3; // drukknop om poort te sluiten (ingedrukt houden)

const int limitswitchOpen = 5;  // eindeloops wanneer de poort open tegen de eindeloop staat (ingedrukt = LOW)
const int limitswitchClose = 6; // eindeloops wanneer de poort dicht tegen de eindeloop staat (ingedrukt = LOW)

const int infraRedSensor_A = 43; // infraRedSensor
const int infraRedSensor_B = 42; // infroRedSensor
const int inductiveSensor = 45;  // inductiveSensor

/* PIN VARS DECLARATION */
int buttonOpenVar = 0;  // drukknop om poort te open
int buttonCloseVar = 0; // drukknop om poort te sluiten (ingedrukt houden)

int limitswitchOpenVar = 0;  // eindeloops wanneer de poort open tegen de eindeloop staat (ingedrukt = LOW)
int limitswitchCloseVar = 0; // eindeloops wanneer de poort dicht tegen de eindeloop staat (ingedrukt = LOW)

int infraRedSensor_A_Var = 0; // infraRedSensor
int infraRedSensor_B_Var = 0; // infroRedSensor
int inductiveSensorVar = 0;   // inductiveSensor

/* PIXY BARCODE METHODE */
int currentBarcode;
int checkerBarcode;

/* PORT OPTIONS */
int gateTimer = 20;
int stateCheck = 0;

/* CLOCK VARS*/
unsigned long tmr = 0;
unsigned int ctr = 0;
int timerStart = 0;

void setup()
{
  Serial.begin(115200);
  pixy.init();
  pixy.changeProg("barcode");

  // Contactors
  pinMode(gateOpen, OUTPUT);
  pinMode(gateClose, OUTPUT);

  // Buttons
  pinMode(buttonOpen, INPUT);
  pinMode(buttonClose, INPUT);

  // Sensors
  pinMode(limitswitchOpen, INPUT);
  pinMode(limitswitchClose, INPUT);
  pinMode(infraRedSensor_A, INPUT);
  pinMode(infraRedSensor_B, INPUT);
  pinMode(inductiveSensor, INPUT);
}

void readInputs()
{
  buttonOpenVar = digitalRead(buttonOpen);
  buttonCloseVar = digitalRead(buttonClose);
  limitswitchOpenVar = digitalRead(limitswitchOpen);
  limitswitchCloseVar = digitalRead(limitswitchClose);
  infraRedSensor_A_Var = digitalRead(infraRedSensor_A);
  infraRedSensor_B_Var = digitalRead(infraRedSensor_B);
  inductiveSensorVar = digitalRead(inductiveSensor);
}

void buttonOpenAndClose()
{
  if (buttonOpenVar && limitswitchOpenVar)
  {
    digitalWrite(gateOpen, HIGH);
  }
  else
  {
    digitalWrite(gateOpen, LOW);
  }

  if (buttonCloseVar && limitswitchCloseVar)
  {
    digitalWrite(gateClose, HIGH);
  }
  else
  {
    digitalWrite(gateClose, LOW);
  }
}

void pixyFunction()
{
  pixy.line.getAllFeatures();
  checkerBarcode = pixy.line.barcodes;
  if (checkerBarcode)
  {
    currentBarcode = pixy.line.barcodes[0].m_code;
    Serial.println(currentBarcode);
  }
}

void clockFunction()
{
  if (millis() >= tmr + 1000)
  {
    tmr += 1000;
    if (timerStart)
      ctr++;
  }
}

void gateFunction()
{
  if (checkerBarcode || inductiveSensorVar)
  {
    if (infraRedSensor_A_Var || infraRedSensor_B_Var)
    {
      stateCheck = 0;
    }
    else
    {
      stateCheck = 1;
    }
  }

  if (ctr == gateTimer)
  {
    stateCheck = 2;
    timerStart = 0;
    ctr = 0;
  };

  switch (stateCheck)
  {
  case 0:
    digitalWrite(gateOpen, LOW);
    digitalWrite(gateClose, LOW);
    break;
  case 1:
    if (limitswitchOpenVar)
    {
      digitalWrite(gateOpen, HIGH);
    }
    else
    {
      digitalWrite(gateOpen, LOW);
      timerStart = 1;
    }
    break;
  case 2:
    if (limitswitchCloseVar)
    {
      digitalWrite(gateClose, HIGH);
    }
    else
    {
      digitalWrite(gateClose, LOW);
      stateCheck = 0;
    }
    break;
  default:
    break;
  }
}

void loop()
{
  readInputs();
  buttonOpenAndClose();
  pixyFunction();
  clockFunction();
  gateFunction();
}