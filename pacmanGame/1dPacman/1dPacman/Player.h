#ifndef PLAYER_H
#define PLAYER_H

#include<SFML/Graphics.hpp>
#include"Globals.h"

class Player
{
public:
	Player();
	~Player();

	void init();

private:
	sf::Vector2f m_position{ ((((PICKUP_AMOUNT * 100.f) + SCREEN_WIDTH / 2.f) / 100.f) * 20.f), SCREEN_HEIGHT / 2.f };

	std::shared_ptr< sf::RectangleShape > m_body;
};

#endif // !PLAYER_H
