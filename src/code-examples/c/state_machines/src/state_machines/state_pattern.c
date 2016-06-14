/**
 * Name of file  : event_centric.c
 * Author        : Elias Frantar <efrantar@student.tgm.ac.at>
 * Version       : 20141001.2
 * Description   : This file contains the implementation of `runTrafficLight()` using an "state pattern" state-machine.
 */

#include "trafficlight.h"
#include "timer.h"


#ifdef STATE_PATTERN


#include "trafficlight.h"
#include "timer.h"

/* method prototypes */
struct StateClass handleRed(enum Event);
struct StateClass handleRedYellow(enum Event);
struct StateClass handleGreen(enum Event);
struct StateClass handleGreenBlinking(enum Event);
struct StateClass handleYellow(enum Event);
struct StateClass handleYellowBlinking(enum Event);

/*
 * This struct represents the State-class.
 * It contains all necessary "attributes" and "methods" for a single state.
 */
struct StateClass 
{
	struct StateClass (*gotoNextState) (enum Event);
};

/* table containing references to all state-"Objects" */
struct StateClass states[6] = 
{
	{handleRed},
	{handleRedYellow},
	{handleGreen},
	{handleGreenBlinking},
	{handleYellow},
	{handleYellowBlinking}
};

/**
 * \see trafficlight.h
 */
void runTrafficLight() 
{
	/* initial state */
	enum Event event = NO_EVENT;
	struct StateClass state = states[RED];
	toggleLight(RED_LIGHT, ON);

	timer(RED_TIME, STANDBY);

	/* state-machine loop */
	while (1)
	{
		event = checkEvent();

		if (event != NO_EVENT) // do only if something happend
		{
			state = state.gotoNextState(event); // handle next state
		}
	}
}

/* state handlers for all 6 different state-classes; self explantory -> no documentation necessary */

struct StateClass handleRed(enum Event event)
{
	if (event == STANDBY)
	{
		handleStandby();
		return states[RED_YELLOW];
	}
	else if (event == IDLE)
	{
		handleIdle();
		return states[YELLOW_BLINKING];
	}
}

struct StateClass handleRedYellow(enum Event event)
{
	if (event == GO) 
	{
		handleGo();
		return states[GREEN];
	}
}

struct StateClass handleGreen(enum Event event)
{
	if (event == PREPARE_TO_STOP)
	{
		handlePrepareToStop();
		return states[GREEN_BLINKING];
	}
}

struct StateClass handleGreenBlinking(enum Event event)
{
	if (event == REPEAT)
	{
		handleRepeatGreen();
		return states[GREEN_BLINKING];
	}
	else if (event == STOP)
	{
		handleStop();
		return states[YELLOW];
	}
}

struct StateClass handleYellow(enum Event event)
{
	if (event == WAIT)
	{
		handleWait();
		return states[RED];
	}
}

struct StateClass handleYellowBlinking(enum Event event)
{
	if (event == REPEAT)
	{
		handleRepeatYellow();
		return states[YELLOW_BLINKING];
	}
	else if (event == RESET)
	{
		handleReset();
		return states[RED];
	}
}


#endif

