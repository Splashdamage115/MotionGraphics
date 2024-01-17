#include "Enemy.h"
#include "Globals.h"
#include "RenderObject.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::init(sf::Vector2f t_startPos)
{
	m_moveSpeed = GHOST_MOVE_SPEED;

	m_body = std::make_shared<sf::RectangleShape>();
	m_body->setSize(sf::Vector2f(30.f, 50.f));
	m_body->setOrigin(m_body->getSize() / 2.f);
	m_body->setPosition(t_startPos);
	m_body->setFillColor(sf::Color(200, 185, 0, 255));

	RenderObject::getInstance().add(m_body);
}

void Enemy::respawn(float t_startPos)
{
	m_remainingHuntLength = -1;

	m_moveSpeed = GHOST_MOVE_SPEED;

	m_body->setFillColor(sf::Color(200, 185, 0, 255));
	m_body->setPosition(t_startPos, m_body->getPosition().y);
}

void Enemy::update()
{
	if (m_remainingHuntLength > 0)
	{
		m_remainingHuntLength--;
	}
	else if(m_remainingHuntLength == 0)
	{
		m_moveSpeed = GHOST_MOVE_SPEED;
		m_body->setFillColor(sf::Color(200, 185, 0, 255));
		m_remainingHuntLength--;
	}
}

void Enemy::followPlayer(float t_xPos)
{
	float moveVector;
	if (t_xPos < m_body->getPosition().x)
	{
		moveVector = -m_moveSpeed;
	}
	else
	{
		moveVector = m_moveSpeed;
	}

	if (m_remainingHuntLength != -1)
		moveVector = -moveVector;

	m_body->move(sf::Vector2f(moveVector, 0));
}

void Enemy::enterHuntedMode()
{
	m_moveSpeed -= GHOST_SPEED_DECREASE;
	m_remainingHuntLength = GHOST_HUNT_LENGTH;
	m_body->setFillColor(sf::Color::Red);
}

bool Enemy::getHuntActive()
{
	if (m_remainingHuntLength != -1)
		return true;
	return false;
}
