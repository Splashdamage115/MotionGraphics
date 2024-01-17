#include "Player.h"
#include "RenderObject.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::init(float t_left, float t_right)
{
	m_body = std::make_shared<sf::RectangleShape>();
	m_body->setSize(sf::Vector2f(30.f, 50.f));
	m_body->setOrigin(m_body->getSize() / 2.f);
	m_body->setPosition(m_position);

	RenderObject::getInstance().add(m_body);

	m_leftSide = t_left;
	m_rightSide = t_right;

	m_moveSpeed = static_cast<float>(PLAYER_MOVE_SPEED);
}

void Player::update()
{
	if (m_body->getPosition().x > m_rightSide)
	{
		m_position = sf::Vector2f(m_leftSide, m_position.y);
		m_body->setPosition(m_position);
	}
	else if (m_body->getPosition().x < m_leftSide)
	{
		m_position = sf::Vector2f(m_rightSide, m_position.y);
		m_body->setPosition(m_position);
	}
	m_position += sf::Vector2f(m_moveSpeed, 0);
	m_body->move(sf::Vector2f(m_moveSpeed, 0));
}
