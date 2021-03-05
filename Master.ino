/* Include the Pixy2 + HCPCA9685 library */
#include <Pixy2.h> 
#include "HCPCA9685.h"

/* Include Arduino Wire library for I2C */
#include <Wire.h>

/* I2C slave address for the device/module. For the HCMODU0097 the default I2C address is 0x40 */
#define  I2CAdd 0x40
 
/* Define Slave I2C Address */
#define SLAVE_ADDR 0x09

/* Create an instance of the library */
HCPCA9685 HCPCA9685(I2CAdd);

/* Variables */
int pos = 0;

Pixy2 pixy;

void setup()
{
    /* Initialise the library and set it to 'servo mode' */ 
    HCPCA9685.Init(SERVO_MODE);

    /* Wake the device up */
    HCPCA9685.Sleep(false);

    /* Initialize I2C communications as Master */
    Wire.begin();

    /* Setup serial monitor */
    Serial.begin(9600);

    /* Pixy2 */
    pixy.init();
    pixy.setLamp(1, 1);
    /* change pixy to linemode */
    Serial.println(pixy.changeProg("line"));
}


void loop()
{
    /* Get line features */
    pixy.line.getAllFeatures();

    /* Detected road sign */
    if (pixy.line.barcodes)
    {
        int code = pixy.line.barcodes[0].m_code;

        /* Write a charatre to the Slave */
        Wire.beginTransmission(SLAVE_ADDR);
        Wire.write(code);
        Wire.endTransmission();

        switch (code)
        {
        case 0:
            //positie
            for(Pos = 10; Pos < 90; Pos++)
            {
                //welke servo
                HCPCA9685.Servo(0, Pos);
                delay(10);
            }
            //positie
            for(Pos = 90; Pos >= 10; Pos--)
            {
                HCPCA9685.Servo(0, Pos);
                delay(10);
            }
            break;
        case 1:
            // Positie
            for(Pos = 10; Pos < 90; Pos++)
            {
            // Welke servo
                HCPCA9685.Servo(0, Pos);
                delay(10);
            }
            // Positie
            for(Pos = 90; Pos >= 10; Pos--)
            {
                HCPCA9685.Servo(0, Pos);
                delay(10);
            }
            break;
        case 2:
            // Positie
            for(Pos = 10; Pos < 90; Pos++)
            {
            // Welke servo
                HCPCA9685.Servo(1, Pos);
                delay(10);
            }
            // Positie
            for(Pos = 90; Pos >= 10; Pos--)
            {
                HCPCA9685.Servo(1, Pos);
                delay(10);
            }
            break;
        case 3:
            // Positie
            for(Pos = 10; Pos < 90; Pos++)
            {
            // Welke servo
                HCPCA9685.Servo(1, Pos);
                delay(10);
            }
            // Positie
            for(Pos = 90; Pos >= 10; Pos--)
            {
                HCPCA9685.Servo(1, Pos);
                delay(10);
            } 
            break;
        case 4:
            // Positie
            for(Pos = 10; Pos < 90; Pos++)
            {
            // Welke servo
                HCPCA9685.Servo(2, Pos);
                delay(10);
            }
            // Positie
            for(Pos = 90; Pos >= 10; Pos--)
            {
                HCPCA9685.Servo(2, Pos);
                delay(10);
            }
            break;
        case 5:
            // Positie
            for(Pos = 10; Pos < 90; Pos++)
            {
            // Welke servo
                HCPCA9685.Servo(2, Pos);
                delay(10);
            }
            // Positie
            for(Pos = 90; Pos >= 10; Pos--)
            {
                HCPCA9685.Servo(2, Pos);
                delay(10);
            } 
            break;
        case 6:
            // Positie
            for(Pos = 10; Pos < 90; Pos++)
            {
            // Welke servo
                HCPCA9685.Servo(3, Pos);
                delay(10);
            }
            // Positie
            for(Pos = 90; Pos >= 10; Pos--)
            {
                HCPCA9685.Servo(3, Pos);
                delay(10);
            }
            break;
        case 7:
            // Positie
            for(Pos = 10; Pos < 90; Pos++)
            {
            // Welke servo
                HCPCA9685.Servo(3, Pos);
                delay(10);
            }
            // Positie
            for(Pos = 90; Pos >= 10; Pos--)
            {
                HCPCA9685.Servo(3, Pos);
                delay(10);
            } 
            break;
        case 8:
            // Positie
            for(Pos = 10; Pos < 90; Pos++)
            {
            // Welke servo
                HCPCA9685.Servo(4, Pos);
                delay(10);
            }
            // Positie
            for(Pos = 90; Pos >= 10; Pos--)
            {
                HCPCA9685.Servo(4, Pos);
                delay(10);
            }
            break;
        case 9:
            // Positie
            for(Pos = 10; Pos < 90; Pos++)
            {
            // Welke servo
                HCPCA9685.Servo(4, Pos);
                delay(10);
            }
            // Positie
            for(Pos = 90; Pos >= 10; Pos--)
            {
                HCPCA9685.Servo(4, Pos);
                delay(10);
            } 
            break;
        default:
            break;
        }
    }
}