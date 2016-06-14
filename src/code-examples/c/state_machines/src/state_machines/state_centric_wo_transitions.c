/**
 * Name of file  : state_centric.c
 * Author        : Elias Frantar <efrantar@student.tgm.ac.at>
 * Version       : 20141001.3
 * Description   : This file contains the implementation of `runTrafficLight()` using a "state-centric without transitions" state-machine.
 */

#include "../headers/trafficlight.h"
#include "../headers/timer.h"


#ifdef STATE_CENTRIC_WO_TRANSITIONS


/**
 * \see trafficlight.h
 */
void runTrafficLight() 
{
	/* initial state */
	int blinkCounter;
	enum Event event = NO_EVENT;
	enum State state = RED;
	toggleLight(RED_LIGHT, ON);

	sleep(RED_TIME);

	/* it is not possible to implement the `YELLOW_BLINKING` state in this type of state-machine! */
	while (1) 
	{
		switch (state) 
		{
			case RED:
				state = RED_YELLOW;
				toggleLight(YELLOW_LIGHT, ON);

				sleep(RED_YELLOW_TIME);
				
				break;
			case RED_YELLOW:
				state = GREEN;
				toggleLight(RED_LIGHT, OFF);
				toggleLight(YELLOW_LIGHT, OFF);
				toggleLight(GREEN_LIGHT, ON);

				sleep(GREEN_TIME);

				break;
			case GREEN:
				state = GREEN_BLINKING;
				blinkCounter = 0;
				toggleLight(GREEN_LIGHT, OFF);

				sleep(BLINK_TIME);
				
				break;
			case GREEN_BLINKING:
				if (blinkCounter < NO_OF_BLINKS) 
				{ // increment will be performed after comparison
					toggleLight(GREEN_LIGHT, ON);
					sleep(BLINK_TIME);
					toggleLight(GREEN_LIGHT, OFF);
					blinkCounter++;
							
					sleep(BLINK_TIME);
				}
				else 
				{
					state = YELLOW;
					toggleLight(YELLOW_LIGHT, ON);

					sleep(YELLOW_TIME);
				}
							
				break;
			case YELLOW:
				state = RED;
				toggleLight(YELLOW_LIGHT, OFF);
				toggleLight(RED_LIGHT, ON);

				sleep(RED_TIME);

				break;
		}
	}
}


#endif
