/**
 * Name of file  : trafficlight.h
 * Author        : Elias Frantar <efrantar@student.tgm.ac.at>
 * Version       : 25140930.5
 * Description   : The traffic-light header file with enum and function definitions and global variables.
 */

#ifndef TRAFFICLIGHT_H_INCLUDED // prevent double including
#define TRAFFICLIGHT_H_INCLUDED


/* definitions of constants */

#define ON 					1
#define OFF 				0

#define NO_OF_BLINKS		4

/* times in seconds */
#define RED_TIME 			5
#define GREEN_TIME 			5
#define YELLOW_TIME 		3
#define RED_YELLOW_TIME		3
#define BLINK_TIME			1

/* type definitions */

/**
 * This enum contains all states of a traffic-light.
 */
enum State 
{
    RED = 0,
    RED_YELLOW = 1,
    GREEN = 2,
    GREEN_BLINKING = 3,
    YELLOW = 4,
    YELLOW_BLINKING = 5,
	NO_STATE = -1 // -1 is treated as invalid
};

/**
 * This enum contains all commands for state-transistions of a traffic-light.
 */
enum Event 
{
    STANDBY = 0,
    IDLE = 1,
    GO = 2,
    PREPARE_TO_STOP = 3,
	REPEAT = 4,
    STOP = 5,
    WAIT = 6,
    RESET = 7,
	NO_EVENT = 8 // we don't want any array underflows in `table_driven`
};

/**
 * This enum contains all different lights.
 */
enum Light 
{
	RED_LIGHT,
	YELLOW_LIGHT,
	GREEN_LIGHT
};

/* method prototypes */

/**
 * Runs a traffic light infinitely.
 * NOTE: "run" means: red -> yellow -> green -> yellow -> red
 */
void runTrafficLight();

/**
 * Toggles the light with the given name to either on or off.
 *
 * \param the reference to the light to toggle
 * \param if to switch the light on or off; best only use ON and OFF
 */
void toggleLight(enum Light, int);

/**
 * Wait for the given amount of seconds.
 * This is a >>blocking<< call!
 *
 * \param the number of seconds to sleep
 */
void sleep(int);

/* individual method handlers for all events of a traffic-light */
void handleStandby();
void handleGo();
void handlePrepareToStop();
void handleRepeatGreen();
void handleRepeatYellow();
void handleStop();
void handleWait();
void handleIdle();
void handleReset();
void handleNone();


#endif

