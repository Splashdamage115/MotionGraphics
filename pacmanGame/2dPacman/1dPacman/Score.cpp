#include "Score.h"
#include "RenderObject.h"
#include "Globals.h"


void Score::init()
{
	m_scoreVal = 0;

	m_score = std::make_shared<sf::Text>();
	if (!m_font.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
	}
	else
	{
		m_score->setString("SCORE : " + std::to_string(m_scoreVal));
		m_score->setFont(m_font);
		m_score->setCharacterSize(10u);
		m_score->setOrigin(m_score->getGlobalBounds().height / 2.f, m_score->getGlobalBounds().width / 2.f);
		m_score->setPosition(sf::Vector2f(SCREEN_WIDTH / 2.f - 80, SCREEN_HEIGHT / 2.f + 300));
		m_score->setFillColor(sf::Color::White);
		m_score->setOutlineColor(sf::Color::Black);
		m_score->setOutlineThickness(1);
		

		RenderObject::getInstance().add(m_score);
	}
}

void Score::increaseScore(int t_increase)
{
	m_scoreVal += t_increase;

	m_score->setString("SCORE : " + std::to_string(m_scoreVal));
	//m_score->setOrigin(m_score->getGlobalBounds().height / 2.f, m_score->getGlobalBounds().width / 2.f);
	//m_score->setPosition(sf::Vector2f(SCREEN_WIDTH / 2.f - 80, SCREEN_HEIGHT / 2.f - 40));
}
