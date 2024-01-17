#ifndef ENEMY_H
#define ENEMY_H
#include<SFML/Graphics.hpp>

class Enemy
{
public:
	Enemy();
	~Enemy();

	void init(sf::Vector2f t_startPos);
	void respawn(float t_startPos);

	void update();

	void followPlayer(float t_xPos);

	void enterHuntedMode();

	sf::FloatRect getBounds() { return m_body->getGlobalBounds(); }

	bool getHuntActive();
private:
	std::shared_ptr<sf::RectangleShape> m_body;

	int m_remainingHuntLength{ -1 };

	float m_moveSpeed{ 0 };
};

#endif // !ENEMY_H
