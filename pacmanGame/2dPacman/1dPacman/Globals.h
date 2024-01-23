// global variables for the game
#ifndef GLOBALS_H
#define GLOBALS_H

const unsigned int SCREEN_WIDTH = 1920; // width of the screen for maths
const unsigned int SCREEN_HEIGHT = 1080; // height of the screen for maths

const int PICKUP_AMOUNT = 10;
const int PICKUP_AMOUNT_SIDE = 6;
const float PLAYER_MOVE_SPEED = 3.f;

const int GHOST_HUNT_LENGTH = 120; // store the reset rate, 60 fps = 1 seconds
const float GHOST_MOVE_SPEED = 3.2f;
const float GHOST_SPEED_DECREASE = 2.f;

const int CHERRY_SCORE = 5;
const int BIT_SCORE = 1;
const int GHOST_SCORE = 20;

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