#include "PickUps.h"
#include "RenderObject.h"

PickUps::PickUps()
{
}

PickUps::~PickUps()
{
}

void PickUps::init(PickupType t_newType, sf::Vector2f t_pos)
{
	m_pickedUp = false;

	m_type = t_newType;

	if (m_type == PickupType::None)
		exit(2);

	m_body = std::make_shared<sf::CircleShape>();

	if (m_type == PickupType::Normal)
	{
		m_body->setFillColor(sf::Color::White);

		m_body->setRadius(5.0f);
		m_body->setOrigin(10.0f, 5.0f);
	}
	else
	{
		m_body->setFillColor(sf::Color::Magenta);

		m_body->setRadius(10.0f);
		m_body->setOrigin(10.0f, 10.0f);
	}

	m_body->setPosition(t_pos);

	RenderObject::getInstance().add(m_body);
}

void PickUps::itemPickedUp()
{
	m_body->setPosition(-100.f, -100.f);

	m_pickedUp = true;
}

bool PickUps::checkCherry()
{
	if (m_type == PickupType::Cherry)
		return true;
	return false;
}
