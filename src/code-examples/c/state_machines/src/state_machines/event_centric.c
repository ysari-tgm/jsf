/**
 * Name of file  : event_centric.c
 * Author        : Elias Frantar <efrantar@student.tgm.ac.at>
 * Version       : 20141001.3
 * Description   : This file contains the implementation of `runTrafficLight()` using an "event-centric" state-machine.
 */

#include "../headers/trafficlight.h"
#include "../headers/timer.h"


#ifdef EVENT_CENTRIC


/**
 * \see trafficlight.h
 */
void runTrafficLight() 
{
	/* initial state */
	enum Event event = NO_EVENT;
	enum State state = RED;
	toggleLight(RED_LIGHT, ON);

	timer(RED_TIME, STANDBY);
	
	/* state machine loop */
	while (1) 
	{
		event = checkEvent(); // check if an event has been triggered

		switch (event) 
		{
			case STANDBY:
				if (state == RED) 
				{
					state = RED_YELLOW;
					handleStandby();			
				}
				break;
			case GO:
				if (state == RED_YELLOW) 
				{
					state = GREEN;
					handleGo();						            
				}
				break;
			case PREPARE_TO_STOP:
				if (state == GREEN) 
				{
					state = GREEN_BLINKING;
					handlePrepareToStop();
				}
				break;
			case REPEAT:
				if (state == GREEN_BLINKING) 
				{
					handleRepeatGreen();
				}
				else if (state == YELLOW_BLINKING) 
				{
					handleRepeatYellow();
				}
				break;
			case STOP:
				if (state == GREEN_BLINKING) 
				{
					state = YELLOW;
					handleStop();
				}
				break;
			case WAIT:
				if (state == YELLOW) 
				{
					state = RED;
					handleWait();
				}
				break;
			case IDLE:
				if (state == RED) 
				{
					state = YELLOW_BLINKING;
					handleIdle();
				}
			case RESET:
				if (state == YELLOW_BLINKING) 
				{
					state = RED;
					handleReset();
				}
				break;
		}
	}
}


#endif
