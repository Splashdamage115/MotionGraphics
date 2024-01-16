#include "Player.h"
#include "RenderObject.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::init()
{
	m_body = std::make_shared<sf::RectangleShape>();
	m_body->setSize(sf::Vector2f(30.f, 50.f));
	m_body->setOrigin(m_body->getSize() / 2.f);
	m_body->setPosition(m_position);

	RenderObject::getInstance().add(m_body);
}
