#include"RenderObject.h"

RenderObject::RenderObject() :
	m_window{ sf::VideoMode{ SCREEN_WIDTH, SCREEN_HEIGHT, 32U }, "1.5D Pacman" }
{
	sf::Image icon;
	icon.loadFromFile(".\\ASSETS\\IMAGES\\R.png");

	m_window.setIcon(150, 180, icon.getPixelsPtr());
}

void RenderObject::add(std::shared_ptr<sf::Drawable> t_new)
{
	for (unsigned int i = 0; i < m_assets.size(); i++)
	{
		if (m_assets.at(i).lock() == nullptr)
		{
			m_assets.at(i) = t_new;
			return;
		}
	}

	m_assets.push_back(t_new);
}

void RenderObject::clear()
{
	m_assets.clear();
}

void RenderObject::render()
{
	m_window.clear();
	for (unsigned int i = 0; i < m_assets.size(); i++)
		if (m_assets.at(i).lock() != nullptr)
			m_window.draw(*m_assets.at(i).lock());
	m_window.display();
}