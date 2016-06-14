/**
 * Name of file  : event_centric.c
 * Author        : Elias Frantar <efrantar@student.tgm.ac.at>
 * Version       : 20140928.2
 * Description   : This class is used instead of an interrupt to test the state-machine implementations. (interrupts are not available in plain C AFAIK)
 */

#include "headers/timer.h"

int doneTime; // when the timer is finished
enum Event doneEvent = NO_EVENT; // event to return when finished

/**
 * Sets and starts the timer for `seconds`.
 *
 * \param seconds the number of seconds to run
 * \param event the event to return when finished
 */
void timer(int seconds, enum Event event) 
{
	doneTime = (clock() / CLOCKS_PER_SEC) + seconds;
	doneEvent = event;
}

/**
 * Returns the previoulsy configured event if the timer is finished.
 *
 * \return the previously configured event if the timer is finished; NO_EVENT otherwise
 */
enum Event checkEvent() 
{
	if (clock() / CLOCKS_PER_SEC >= doneTime) 
	{
		return doneEvent;
	}

	return NO_EVENT; // return NO_EVENT if not yet finished
}
