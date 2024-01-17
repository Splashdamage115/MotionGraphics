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
	m_score.init();

	if (m_pickups.size() != 0)
		m_pickups.clear();
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

	m_player.init(m_backgroundTop->getGlobalBounds().left, m_backgroundTop->getGlobalBounds().left + m_backgroundTop->getGlobalBounds().width, sf::Vector2f(m_backgroundTop->getGlobalBounds().left + 20, SCREEN_HEIGHT / 2.f));

	m_enemy.init(sf::Vector2f(m_backgroundTop->getGlobalBounds().left + m_backgroundTop->getGlobalBounds().width - 20, SCREEN_HEIGHT / 2.f ));
}

/// <summary>
/// process all different events made by the user
/// </summary>
/// <param name="t_event">passed from game loop to speed up code</param>
void GamePlay::events(sf::Event& t_event)
{
	processKeys(t_event);
}

/// !!!---Private function---!!!
/// <summary>
/// process any input from the user
/// </summary>
/// <param name="t_event">use this for the key press</param>
void GamePlay::processKeys(sf::Event& t_event)
{
	m_player.invertMove();
}

void GamePlay::handlePickups()
{
	sf::Vector2f playerPos = m_player.getPosition();
	for (unsigned int i = 0; i < m_pickups.size(); i++)
	{
		if (m_pickups.at(i).getBounds().contains(playerPos))
		{
			m_pickups.at(i).itemPickedUp();
			if (m_pickups.at(i).checkCherry())
			{
				m_score.increaseScore(CHERRY_SCORE);
				m_enemy.enterHuntedMode();
			}
			else
			{
				m_score.increaseScore(BIT_SCORE);
			}
		}
	}
	bool reset = true;

	for (unsigned int i = 0; i < m_pickups.size(); i++)
	{
		if (!m_pickups.at(i).getPickedUp())
		{
			reset = false;
		}
	}
	if (reset)
	{
		int cherryPos = (rand() % PICKUP_AMOUNT);
		for (unsigned int i = 0; i < m_pickups.size(); i++)
		{
			PickupType type = PickupType::Normal;
			if (i == cherryPos)
				type = PickupType::Cherry;

			m_pickups.at(i).init(type, sf::Vector2f(((SCREEN_WIDTH / 2.f) - (100.f * (PICKUP_AMOUNT / 2.f))) + (100.f * i), SCREEN_HEIGHT / 2.f));
		}
	}
}

/// <summary>
/// all update functions will be in here
/// </summary>
/// <param name="t_deltaTime">delta time passed from game</param>
void GamePlay::update(sf::Time t_deltaTime)
{
	m_player.update();
	
	handlePickups();

	m_enemy.update();
	m_enemy.followPlayer(m_player.getPosition().x);

	if (m_player.checkCollision(m_enemy.getBounds()))
	{
		if (m_enemy.getHuntActive()) 
		{
			float respawnCoords{ 0 };
			if (rand() % 2 == 0)
			{
				respawnCoords = m_backgroundTop->getGlobalBounds().left;
			}
			else
			{
				respawnCoords = m_backgroundTop->getGlobalBounds().left + m_backgroundTop->getGlobalBounds().width;
			}
			m_enemy.respawn(respawnCoords);

			m_score.increaseScore(GHOST_SCORE);
		}
		else
		{
			resetLevel();
		}
	}
}
