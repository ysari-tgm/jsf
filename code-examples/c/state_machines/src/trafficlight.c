/**
 * Name of file  : trafficlight.c
 * Author        : Elias Frantar <efrantar@student.tgm.ac.at>
 * Version       : 20141001.3
 * Description   : Runs a traffic-light state-machine implementation.
 *				   The used implementation has to be specified at compile time by defining on of the following constants:
 *				   STATE_CENTRIC, STATE_CENTRIC_WO_TRANSISTIONS, EVENT_CENTRIC, STATE_PATTERN, TABLE_DRIVEN				
 */

/* include system libraries */
#include <stdio.h>
#include <stdlib.h>

/* include header file for method prototypes and constant definitions */
#include "headers/trafficlight.h"
#include "headers/timer.h"

int main(int argc, char* argv[]) 
{
	printf("Running the traffic-light infinitely. Press `CTRL + C` to terminate! \n");
	runTrafficLight(); // this will never end, so no `return EXIT_SUCCESS` necessary
}

int blinkCounter; // counts the number of times a light has already blinked

void toggleLight(enum Light light, int on) 
{
	switch(light) 
	{
		case RED_LIGHT:		printf("RED \t");	break;
		case YELLOW_LIGHT:	printf("YELLOW \t");	break;
		case GREEN_LIGHT:	printf("GREEN \t");	break;
	}

	if (on) printf("ON \n");
	else	printf("OFF \n");
}

void sleep(int seconds) 
{
	int over = clock() / CLOCKS_PER_SEC + seconds;
	while (clock() / CLOCKS_PER_SEC < over);
}

/* implementation of all event-handlers; they are self explanatory, so no documentation needed */

void handleStandby() 
{
	toggleLight(YELLOW_LIGHT, ON);

	timer(RED_YELLOW_TIME, GO);
}

void handleGo() 
{
	toggleLight(RED_LIGHT, OFF);
	toggleLight(YELLOW_LIGHT, OFF);
	toggleLight(GREEN_LIGHT, ON);
	
	timer(GREEN_TIME, PREPARE_TO_STOP);	
}

void handlePrepareToStop() 
{
	toggleLight(GREEN_LIGHT, OFF);
	blinkCounter = 0;
	
	timer(BLINK_TIME, REPEAT);
}

void handleRepeatGreen() 
{
	if (blinkCounter < NO_OF_BLINKS) { // increment will be performed after comparison
		blinkCounter++;

		toggleLight(GREEN_LIGHT, ON);
		sleep(BLINK_TIME);
		toggleLight(GREEN_LIGHT, OFF);
							
		timer(BLINK_TIME, REPEAT);
	}
	else 
	{
		timer(0, STOP); // we should immediately go to next state
	}
}

void handleRepeatYellow() 
{
	toggleLight(YELLOW_LIGHT, ON);
	sleep(BLINK_TIME);
	toggleLight(YELLOW_LIGHT, OFF);

	
	timer(BLINK_TIME, REPEAT);
}

void handleStop() 
{
	toggleLight(YELLOW_LIGHT, ON);

	timer(YELLOW_TIME, WAIT);
}

void handleWait() 
{
	toggleLight(YELLOW_LIGHT, OFF);
	toggleLight(RED_LIGHT, ON);

	
	timer(RED_TIME, STANDBY);
}

void handleIdle() 
{
	toggleLight(RED_LIGHT, OFF);
	
	timer(BLINK_TIME, REPEAT);	
}

void handleReset() 
{
	toggleLight(RED_LIGHT, ON);

	timer(RED_TIME, STANDBY);
}

void handleNone()
{
}


