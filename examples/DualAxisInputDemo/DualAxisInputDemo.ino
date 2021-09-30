/**
 * DualAxisInput.ino
 * 
 * 
 * 
 * A simple example of the DualAxisInput class usage
 * 
 * This sketch will read the input every 200 ms
 * to get the current position of our DualAxisInput.
 * In case input is changed, we will be noticed through the serial monitor
 * 
 *  This example code is in the public domain.
 */

#include <DualAxisInput.h>

/**
 * Rotation can be defined in range [0,3]
 * defined in DualAxisInput class constants as
 * ROTATON_0, ROTATION_90, ROTATION_180, ROTATION_270
 * depending on how the device is installed.
 * 0 rotation is pins left
 * 90 rotation is pins up
 * 180 rotation is pins right
 * 270 rotation is pins down
 * Modify untill you get the desired output
 */

const byte rotation = DualAxisInput::ROTATION_0;
/**
 * 
 * Create DualAxisInput Object using 
 * A0 as input for the x axis
 * A1 as input for the y axis
 * rotation as defined
 * no need to include rotation if it's 0
 * default is 0
 */
DualAxisInput input(A0, A1, rotation);

void setup()
{
    Serial.begin(115200);

   // Serial.println(__FILE__);
    Serial.println("Start");
}

void loop()
{

    // read current position, use always before any other action
    input.read();

    // check if position has changed
    if (input.changed())
    {
        Serial.print("Position changed to : ");

        // to know the position you can use class methods
        if (input.isUp())
        {
            Serial.println("UP");
        }
        else if (input.isDown())
        {
            Serial.println("DOWN");
        }
        else if (input.isLeft())
        {
            Serial.println("LEFT");
        }
        // or compare position with class defined position constant
        else
        {
            switch (input.position())
            {
            case DualAxisInput::RIGHT:
                Serial.println("RIGHT");
                break;
            case DualAxisInput::NONE:
                Serial.println("NONE");
            default:
                break;
            }
        }
    }


    delay(200);
}