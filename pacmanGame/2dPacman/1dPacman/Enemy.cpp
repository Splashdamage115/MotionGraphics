#include "Enemy.h"
#include "Globals.h"
#include "RenderObject.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::init(sf::Vector2f t_startPos, float t_left, float t_right, float t_top, float t_bottom)
{
	rightSide = false;
	leftSide = false;
	topSide = true;
	bottomSide = false;

	m_moveSpeed = GHOST_MOVE_SPEED;

	m_body = std::make_shared<sf::RectangleShape>();
	m_body->setSize(sf::Vector2f(30.f, 50.f));
	m_body->setOrigin(m_body->getSize() / 2.f);
	m_body->setPosition(t_startPos);
	m_body->setFillColor(sf::Color(200, 185, 0, 255));

	RenderObject::getInstance().add(m_body);

	m_leftSide = t_left;
	m_rightSide = t_right;
	m_topSide = t_top;
	m_bottomSide = t_bottom;
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

	if (m_body->getPosition().x > m_rightSide)
	{
		if (topSide)
		{
			m_body->setPosition(m_rightSide, topSide + 100);

		}
		else
		{
			m_body->setPosition(m_rightSide, m_bottomSide - 1);
			m_moveSpeed = -m_moveSpeed;
		}

		rightSide = true;
		leftSide = false;
		topSide = false;
		bottomSide = false;
	}
	else if (m_body->getPosition().x < m_leftSide)
	{
		if (topSide)
		{
			m_body->setPosition(m_leftSide, topSide + 100);
			m_moveSpeed = -m_moveSpeed;
		}
		else
		{
			m_body->setPosition(m_leftSide, m_bottomSide - 1);
		}
		rightSide = false;
		leftSide = true;
		topSide = false;
		bottomSide = false;
	}

	else if (m_body->getPosition().y > m_bottomSide)
	{
		if (rightSide)
		{
			m_body->setPosition(m_rightSide - 1, m_bottomSide);
			m_moveSpeed = -m_moveSpeed;
		}
		else
		{
			m_body->setPosition(m_leftSide + 1, m_bottomSide);
		}

		rightSide = false;
		leftSide = false;
		topSide = false;
		bottomSide = true;
	}
	else if (m_body->getPosition().y < m_topSide)
	{
		if (rightSide)
		{
			m_body->setPosition(m_rightSide - 1, m_topSide);
		}
		else
		{
			m_body->setPosition(m_leftSide + 1, m_topSide);
			m_moveSpeed = -m_moveSpeed;
		}

		rightSide = false;
		leftSide = false;
		topSide = true;
		bottomSide = false;
	}

	moveVector = m_moveSpeed;

	if (m_remainingHuntLength != -1)
		moveVector = -moveVector;

	if (rightSide)
	{
		m_body->move(sf::Vector2f(0, moveVector));
	}
	if (leftSide)
	{
		m_body->move(sf::Vector2f(0, moveVector));
	}
	if (bottomSide)
	{
		m_body->move(sf::Vector2f(moveVector, 0));
	}
	if (topSide)
	{
		m_body->move(sf::Vector2f(moveVector, 0));
	}
	//m_position = m_body->getPosition();
}

void Enemy::checkDistanceToPlayer(sf::Vector2f t_playerPos)
{
	m_moveSpeed = -m_moveSpeed;
}

void Enemy::enterHuntedMode()
{
	m_moveSpeed = GHOST_SPEED_DECREASE;
	m_remainingHuntLength = GHOST_HUNT_LENGTH;
	m_body->setFillColor(sf::Color::Red);
}

bool Enemy::getHuntActive()
{
	if (m_remainingHuntLength != -1)
		return true;
	return false;
}
