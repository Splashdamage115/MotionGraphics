#ifndef PICKUPS_H
#define PICKUPS_H

#include<SFML/Graphics.hpp>
#include"Globals.h"

class PickUps
{
public:
	PickUps();
	~PickUps();

	void init(PickupType t_newType, sf::Vector2f t_pos);
private:
	PickupType m_type{ PickupType::None };

	std::shared_ptr<sf::CircleShape> m_body;
};

#endif // !PICKUPS_H
