#include "GamePlay.h"
#include"Globals.h"

/// <summary>
/// default constructor
/// </summary>
GamePlay::GamePlay()
{
	resetLevel();
}

/// <summary>
/// default deconstructor
/// </summary>
GamePlay::~GamePlay()
{
}
/// <summary>
/// resets all values to default as needed
/// </summary>
void GamePlay::resetLevel()
{
	m_player.init();

	int cherryPos = (rand() % PICKUP_AMOUNT);

	for (int i = 0; i < PICKUP_AMOUNT; i++)
	{
		PickupType type = PickupType::Normal;
		if(i == cherryPos)
			type = PickupType::Cherry;
		PickUps newPickup;
		newPickup.init(type, sf::Vector2f(((SCREEN_WIDTH / 2.f ) - (100.f * (PICKUP_AMOUNT / 2.f))) + (100.f * i), SCREEN_HEIGHT / 2.f));
		m_pickups.push_back(newPickup);
	}

	m_backgroundTop = std::make_shared<sf::RectangleShape>();

	m_backgroundTop->setFillColor(sf::Color::White);
	m_backgroundTop->setSize(sf::Vector2f(100.f * (PICKUP_AMOUNT + 1),1.f));
	m_backgroundTop->setOrigin(m_backgroundTop->getSize() / 2.f);
	m_backgroundTop->setPosition((SCREEN_WIDTH / 2.f ) - 60.f, SCREEN_HEIGHT / 2.f - 50);

	RenderObject::getInstance().add(m_backgroundTop);

	m_backgroundBottom = std::make_shared<sf::RectangleShape>();

	m_backgroundBottom->setFillColor(sf::Color::White);
	m_backgroundBottom->setSize(sf::Vector2f(100.f * (PICKUP_AMOUNT + 1), 1.f));
	m_backgroundBottom->setOrigin(m_backgroundTop->getSize() / 2.f);
	m_backgroundBottom->setPosition((SCREEN_WIDTH / 2.f) - 60.f, SCREEN_HEIGHT / 2.f + 50);

	RenderObject::getInstance().add(m_backgroundBottom);

	//m_sfmlLogoS = std::make_shared<sf::Sprite>();

	//if (!m_sfmlLogoT.loadFromFile("ASSETS\\IMAGES\\SFML-LOGO.png"))
	//{
	//	DEBUG_MSG("COULDNT FIND SFML LOGO");
	//}
	//else
	//{
	//	m_sfmlLogoS->setTexture(m_sfmlLogoT);
	//	m_sfmlLogoS->setPosition(200.f, 200.f);

	//	//RenderObject::getInstance().add(m_sfmlLogoS);
	//}
}

/// <summary>
/// process all different events made by the user
/// </summary>
/// <param name="t_event">passed from game loop to speed up code</param>
void GamePlay::events(sf::Event& t_event)
{
	
}

/// !!!---Private function---!!!
/// <summary>
/// process any input from the user
/// </summary>
/// <param name="t_event">use this for the key press</param>
void GamePlay::processKeys(sf::Event& t_event)
{

}

/// <summary>
/// all update functions will be in here
/// </summary>
/// <param name="t_deltaTime">delta time passed from game</param>
void GamePlay::update(sf::Time t_deltaTime)
{
}
