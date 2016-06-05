/**
 * Name of file  : state_centric.c
 * Author        : Elias Frantar <efrantar@student.tgm.ac.at>
 * Version       : 20141001.3
 * Description   : This file contains the implementation of `runTrafficLight()` using a "table-driven" state-machine.
 */

#include "../headers/trafficlight.h"
#include "../headers/timer.h"

#ifdef TABLE_DRIVEN

/* the state table containing a new state entry in [state][event] */
enum State stateTable[6][8] = 
{
  /* STANDBY	 IDLE,				GO,			PREPARE_TO_STOP, REPEAT,			STOP,		WAIT,		RESET,	 */		
	{RED_YELLOW, YELLOW_BLINKING,	NO_STATE,	NO_STATE,		 NO_STATE,			NO_STATE,	NO_STATE,	NO_STATE},	// RED
	{NO_STATE,	 NO_STATE,			GREEN,		NO_STATE,		 NO_STATE,			NO_STATE,	NO_STATE,	NO_STATE},	// RED_YELLOW
	{NO_STATE,	 NO_STATE,			NO_STATE,	GREEN_BLINKING,	 NO_STATE,			NO_STATE,	NO_STATE,	NO_STATE},	// GREEN
	{NO_STATE,	 NO_STATE,			NO_STATE,	NO_STATE,		 GREEN_BLINKING,	YELLOW,		NO_STATE,	NO_STATE},	// GREEN_BLINKING
	{NO_STATE,	 NO_STATE,			NO_STATE,	NO_STATE,		 NO_STATE,			NO_STATE,	RED,		NO_STATE},	// YELLOW
	{NO_STATE,	 NO_STATE,			NO_STATE,	NO_STATE,		 YELLOW_BLINKING,	NO_STATE,	NO_STATE,	RED 	}	// YELLOW_BLINKING
};

void (*actionTable[6][8]) () = 
{
  /* STANDBY		IDLE,		GO,			PREPARE_TO_STOP,	 REPEAT,				STOP,		WAIT,		RESET	    */
	{handleStandby,	handleIdle,	handleNone,	handleNone,			 handleNone,			handleNone,	handleNone,	handleNone },	// RED
	{handleNone,	handleNone,	handleGo,	handleNone,			 handleNone,			handleNone,	handleNone,	handleNone },	// RED_YELLOW
	{handleNone,	handleNone,	handleNone,	handlePrepareToStop, handleNone,			handleNone,	handleNone,	handleNone },	// GREEN
	{handleNone,	handleNone,	handleNone,	handleNone,			 handleRepeatGreen,		handleStop,	handleNone,	handleNone },	// GREEN_BLINKING
	{handleNone,	handleNone,	handleNone,	handleNone,			 handleNone,			handleStop, handleWait, handleNone },	// YELLOW
	{handleNone,	handleNone,	handleNone,	handleNone,			 handleRepeatYellow,	handleNone,	handleNone,	handleReset}	// YELLOW_BLINKING
};

/**
 * Sets `state` to the next state by reading the appropriate entry from `stateTable`.
 *
 * \param state the current state; will be incremented
 * \param event the occurred event (will have an effect on the selection of the next state)
 */
void nextState(enum State* state, enum Event event) // call by reference
{
	if (event != NO_EVENT)
	{
		*state = stateTable[*state][event];
	}
}

/**
 * Performs the next action by reading the appropriate entry form `actionTable`.
 *
 * \param state the current state
 * \param the occurred event (will have an effect on the selection of the action to execute)
 */
void nextAction(enum State state, enum Event event) 
{
	if (event != NO_EVENT) 
	{
		actionTable[state][event]();
	}
}

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

		nextAction(state, event);
		nextState(&state, event);
	}
}


#endif
