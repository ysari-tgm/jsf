/**
 * Name of file  : state_centric.c
 * Author        : Elias Frantar <efrantar@student.tgm.ac.at>
 * Version       : 201401001.3
 * Description   : This file contains the implementation of `runTrafficLight()` using a "state-centric" state-machine.
 */

#include "../headers/trafficlight.h"
#include "../headers/timer.h"


#ifdef STATE_CENTRIC


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

		switch (state) 
		{
			case RED:
				if (event == STANDBY) 
				{
					state = RED_YELLOW;
					handleStandby();
				}
				else if (event == IDLE) 
				{
					state = YELLOW_BLINKING;
					handleIdle();			
				}
				break;
			case RED_YELLOW:
				if (event == GO) 
				{
					state = GREEN;
					handleGo();
				}
				break;
			case GREEN:
				if (event == PREPARE_TO_STOP) 
				{
					state = GREEN_BLINKING;
					handlePrepareToStop();
				}
				break;
			case GREEN_BLINKING:
				if (event == REPEAT) 
				{
					handleRepeatGreen();
				}
				else if (event == STOP) 
				{
					state = YELLOW;
					handleStop();
				}				
				break;
			case YELLOW:
				if (event == WAIT) 
				{
					state = RED;
					handleWait();
				}
				break;
			case YELLOW_BLINKING:
				if (event == REPEAT) 
				{
					handleRepeatYellow();
				}
				else if (event == RESET) 
				{
					state = RED;
					handleReset();
				}
				break;
		}
	}
}


#endif
