#ifndef PLAYER_H
#define PLAYER_H

#include<SFML/Graphics.hpp>
#include"Globals.h"

class Player
{
public:
	Player();
	~Player();

	void init(float t_left, float t_right);
	void update();
	void invertMove() { m_moveSpeed = -m_moveSpeed; }
	sf::Vector2f getPosition() { return m_position; }
private:
	sf::Vector2f m_position{ ((((PICKUP_AMOUNT * 100.f) + SCREEN_WIDTH / 2.f) / 100.f) * 20.f), SCREEN_HEIGHT / 2.f };
	float m_rightSide = 0;
	float m_leftSide = 0;
	float m_moveSpeed = 0;
	std::shared_ptr< sf::RectangleShape > m_body;
};

#endif // !PLAYER_H
