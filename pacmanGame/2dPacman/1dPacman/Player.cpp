#include "Player.h"
#include "RenderObject.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::init(float t_left, float t_right, float t_top, float t_bottom, sf::Vector2f t_startPos)
{

	rightSide = false;
	leftSide = false;
	topSide = false;
	bottomSide = true;

	m_position = t_startPos;

	m_body = std::make_shared<sf::RectangleShape>();
	m_body->setSize(sf::Vector2f(30.f, 50.f));
	m_body->setOrigin(m_body->getSize() / 2.f);
	m_body->setPosition(m_position);

	RenderObject::getInstance().add(m_body);

	m_leftSide = t_left;
	m_rightSide = t_right;
	m_topSide = t_top;
	m_bottomSide = t_bottom;

	m_moveSpeed = PLAYER_MOVE_SPEED;
}

void Player::update()
{
	if (m_body->getPosition().x > m_rightSide)
	{
		if (topSide)
		{
			m_body->setPosition(m_rightSide, topSide + 100);
			
		}
		else
		{
			m_body->setPosition(m_rightSide, m_bottomSide - 1);
			invertMove();
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
			invertMove();
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
			invertMove();
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
			invertMove();
		}

		rightSide = false;
		leftSide = false;
		topSide = true;
		bottomSide = false;
	}

	if (rightSide)
	{
		m_body->move(sf::Vector2f(0, m_moveSpeed));
	}
	if (leftSide)
	{
		m_body->move(sf::Vector2f(0, m_moveSpeed));
	}
	if (bottomSide)
	{
		m_body->move(sf::Vector2f(m_moveSpeed, 0));
	}
	if (topSide)
	{
		m_body->move(sf::Vector2f(m_moveSpeed, 0));
	}
	m_position = m_body->getPosition();
}

void Player::invertMove()
{ 
	m_moveSpeed = -m_moveSpeed;
}

bool Player::checkCollision(sf::FloatRect t_bound)
{
	if (t_bound.intersects(m_body->getGlobalBounds()))
	{
		return true;
	}
	return false;
}
