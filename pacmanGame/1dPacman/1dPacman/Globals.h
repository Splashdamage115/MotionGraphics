// global variables for the game
#ifndef GLOBALS_H
#define GLOBALS_H

const unsigned int SCREEN_WIDTH = 1920; // width of the screen for maths
const unsigned int SCREEN_HEIGHT = 1080; // height of the screen for maths

const int PICKUP_AMOUNT = 10;
const int PLAYER_MOVE_SPEED = 3;

const int GHOST_HUNT_LENGTH = 120; // store the reset rate, 60 fps = 1 seconds

enum class GameModeClass
{
	None,
	GamePlay
};

enum class PickupType
{
	None,
	Normal,
	Cherry
};
#endif // !GLOBALS_H