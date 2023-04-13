#include "mbed.h"
#include "TCPSocket.h"
#include "ESP8266Interface.h"

DigitalOut led1(LED1);
DigitalIn button(USER_BUTTON);

ESP8266Interface wifi(PC_6, PC_7);

enum control_mode {automatic, manual} mode;

bool buttonDown = false;

void autoClean()
{
    //TODO: handle automatic cleaning algorithm
}

void handleControls()
{
    //TODO: handle control commands sent from GUI
}

void handleButton()
{
    //TODO: handle wifi communication here
    if (button) {  // button is pressed
        if  (!buttonDown) {  // a new button press
            if (mode == automatic){
                mode = manual;
            }
            else{
                mode = automatic;
            }
            buttonDown = true;     // record that the button is now down so we don't count one press lots of times
            thread_sleep_for(10);  // ignore anything for 10ms, a very basic way to de-bounce the button. 
        } 
    } else { // button isn't pressed
        buttonDown = false;
    }

}

int main()
{
    printf("This is the vacuum cleaner core running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    
    // TODO: Connect to WI-FI
    mode = manual;
    
    TCPSocket socket;

    while (true){
        // If not connected to WI-FI -> retry (blocking)
        // else, listne for commands and run state machine
        switch(mode){
            case manual:
                led1 = true;
                handleButton();
                handleControls();
                break;
            case automatic:
                led1 = false;
                handleButton();
                autoClean();
                break;
        }
    }
}