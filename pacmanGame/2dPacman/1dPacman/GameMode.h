// THIS IS THE ABSTRACT CLASS FOR A STANDARD GAMEMODE
#ifndef GAMEMODE_H
#define GAMEMODE_H

#include<SFML/Graphics.hpp>
#include"Globals.h"
#include"RenderObject.h"

#include"DEBUG.h" // this is used for DEBUG_MSG

class GameMode
{
public:
	GameMode();  // standard constructor
	~GameMode(); // standard deconstructor (shouldnt be used)

	virtual void resetLevel() = 0;                         // used to reset the level for each session instead of reconstructing
	virtual void events(sf::Event& t_event) = 0;           // used to handle all new events outside key presses
	virtual void update(sf::Time t_deltaTime) = 0;         // all update events

private:
	virtual void processKeys(sf::Event& t_event) = 0;
};

#endif // !GAMEMODE_H