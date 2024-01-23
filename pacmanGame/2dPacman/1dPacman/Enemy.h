#ifndef ENEMY_H
#define ENEMY_H
#include<SFML/Graphics.hpp>

class Enemy
{
public:
	Enemy();
	~Enemy();

	void init(sf::Vector2f t_startPos, float t_left, float t_right, float t_top, float t_bottom);
	void respawn(float t_startPos);

	void update();

	void followPlayer(float t_xPos);
	void checkDistanceToPlayer(sf::Vector2f t_playerPos);

	void enterHuntedMode();

	sf::FloatRect getBounds() { return m_body->getGlobalBounds(); }

	bool getHuntActive();
private:
	std::shared_ptr<sf::RectangleShape> m_body;

	int m_remainingHuntLength{ -1 };

	float m_moveSpeed{ 0 };

	float m_rightSide = 0;
	float m_leftSide = 0;
	float m_topSide = 0;
	float m_bottomSide = 0;

	bool leftSide = false;
	bool rightSide = false;
	bool topSide = false;
	bool bottomSide = false;
};

#endif // !ENEMY_H
