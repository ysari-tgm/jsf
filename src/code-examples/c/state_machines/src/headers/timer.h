/**
 * Name of file  : trafficlight.h
 * Author        : Elias Frantar <efrantar@student.tgm.ac.at>
 * Version       : 25140929.1
 * Description   : The timer header-file defining the method prototypes of a pseudo-interrupt-timer.
 */

#ifndef TIMER_H_DEFINED // prevent double including
#define TIMER_H_DEFINED


/* include necessary methods */
#include <time.h>
#include "trafficlight.h"

/* method headers */
void timer(int seconds, enum Event event);
enum Event checkEvent();


#endif

