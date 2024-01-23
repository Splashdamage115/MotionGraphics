#ifndef PLAYER_H
#define PLAYER_H

#include<SFML/Graphics.hpp>
#include"Globals.h"

class Player
{
public:
	Player();
	~Player();

	void init(float t_left, float t_right,float t_top, float t_bottom, sf::Vector2f t_startPos);
	void update();
	void invertMove();
	sf::Vector2f getPosition() { return m_position; }
	bool checkCollision(sf::FloatRect t_bound);
private:
	sf::Vector2f m_position{ 0,0 };
	float m_rightSide = 0;
	float m_leftSide = 0;
	float m_topSide = 0;
	float m_bottomSide = 0;
	float m_moveSpeed = 0;

	bool rightSide = false;
	bool leftSide = false;
	bool bottomSide = true;
	bool topSide = false;
	std::shared_ptr< sf::RectangleShape > m_body;

	bool m_moveVertical = false;
};

#endif // !PLAYER_H
