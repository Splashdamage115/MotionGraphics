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
	m_canChangeDirection = true;

	m_score.init();

	if (m_pickupsBottom.size() != 0)
		m_pickupsBottom.clear();
	int cherryPos = (rand() % PICKUP_AMOUNT);

	for (int i = 0; i < PICKUP_AMOUNT; i++)
	{
		PickupType type = PickupType::Normal;
		if(i == cherryPos)
			type = PickupType::Cherry;
		PickUps newPickup;
		newPickup.init(type, sf::Vector2f(((SCREEN_WIDTH / 2.f ) - (100.f * (PICKUP_AMOUNT / 2.f))) + (100.f * i), SCREEN_HEIGHT / 2.f + 100.f));
		m_pickupsBottom.push_back(newPickup);
	}

	if (m_pickupsTop.size() != 0)
		m_pickupsTop.clear();
	cherryPos = (rand() % PICKUP_AMOUNT);

	for (int i = 0; i < PICKUP_AMOUNT; i++)
	{
		PickupType type = PickupType::Normal;
		if (i == cherryPos)
			type = PickupType::Cherry;
		PickUps newPickup;
		newPickup.init(type, sf::Vector2f(((SCREEN_WIDTH / 2.f) - (100.f * (PICKUP_AMOUNT / 2.f))) + (100.f * i), 100.f));
		m_pickupsTop.push_back(newPickup);
	}



	m_backgroundTop = std::make_shared<sf::RectangleShape>();

	m_backgroundTop->setFillColor(sf::Color::White);
	m_backgroundTop->setSize(sf::Vector2f(100.f * (PICKUP_AMOUNT + 1),1.f));
	m_backgroundTop->setOrigin(m_backgroundTop->getSize() / 2.f);
	m_backgroundTop->setPosition((SCREEN_WIDTH / 2.f ) - 60.f, 50);

	//RenderObject::getInstance().add(m_backgroundTop);

	m_backgroundTop1 = std::make_shared<sf::RectangleShape>();

	m_backgroundTop1->setFillColor(sf::Color::White);
	m_backgroundTop1->setSize(sf::Vector2f(110.f * (PICKUP_AMOUNT + 1), 1.f));
	m_backgroundTop1->setOrigin(m_backgroundTop1->getSize() / 2.f);
	m_backgroundTop1->setPosition((SCREEN_WIDTH / 2.f) - 60.f, 50);

	RenderObject::getInstance().add(m_backgroundTop1);

	m_backgroundTop2 = std::make_shared<sf::RectangleShape>();

	m_backgroundTop2->setFillColor(sf::Color::White);
	m_backgroundTop2->setSize(sf::Vector2f(90.f * (PICKUP_AMOUNT + 1), 1.f));
	m_backgroundTop2->setOrigin(m_backgroundTop2->getSize() / 2.f);
	m_backgroundTop2->setPosition((SCREEN_WIDTH / 2.f) - 60.f, 150);

	RenderObject::getInstance().add(m_backgroundTop2);


	m_backgroundLeft1 = std::make_shared<sf::RectangleShape>();

	m_backgroundLeft1->setFillColor(sf::Color::White);
	m_backgroundLeft1->setSize(sf::Vector2f(1.f,280.f));
	//m_backgroundLeft1->setOrigin(m_backgroundLeft1->getSize() / 2.f);
	m_backgroundLeft1->setPosition(m_backgroundTop1->getGlobalBounds().left, 50.f);

	RenderObject::getInstance().add(m_backgroundLeft1);

	m_backgroundRight2 = std::make_shared<sf::RectangleShape>();

	m_backgroundRight2->setFillColor(sf::Color::White);
	m_backgroundRight2->setSize(sf::Vector2f(1.f, 280.f));
	//m_backgroundRight2->setOrigin(m_backgroundRight2->getSize() / 2.f);
	m_backgroundRight2->setPosition(m_backgroundTop1->getGlobalBounds().left + m_backgroundTop1->getGlobalBounds().width, 50.f);

	RenderObject::getInstance().add(m_backgroundRight2);

	m_backgroundLeft2 = std::make_shared<sf::RectangleShape>();

	m_backgroundLeft2->setFillColor(sf::Color::White);
	m_backgroundLeft2->setSize(sf::Vector2f(1.f, 270.f));
	//m_backgroundLeft2->setOrigin(m_backgroundLeft2->getSize() / 2.f);
	m_backgroundLeft2->setPosition(m_backgroundTop1->getGlobalBounds().left, 420.f);

	RenderObject::getInstance().add(m_backgroundLeft2);

	
	m_backgroundRight1 = std::make_shared<sf::RectangleShape>();

	m_backgroundRight1->setFillColor(sf::Color::White);
	m_backgroundRight1->setSize(sf::Vector2f(1.f, 270.f));
	//m_backgroundRight1->setOrigin(m_backgroundLeft2->getSize() / 2.f);
	m_backgroundRight1->setPosition(m_backgroundTop1->getGlobalBounds().left + m_backgroundTop1->getGlobalBounds().width, 420.f);

	RenderObject::getInstance().add(m_backgroundRight1);


	m_backgroundMidLeft = std::make_shared<sf::RectangleShape>();

	m_backgroundMidLeft->setFillColor(sf::Color::White);
	m_backgroundMidLeft->setSize(sf::Vector2f(1.f, 440.f));
	//m_backgroundRight1->setOrigin(m_backgroundLeft2->getSize() / 2.f);
	m_backgroundMidLeft->setPosition(m_backgroundTop2->getGlobalBounds().left, 150.f);

	RenderObject::getInstance().add(m_backgroundMidLeft);

	m_backgroundMidRight = std::make_shared<sf::RectangleShape>();

	m_backgroundMidRight->setFillColor(sf::Color::White);
	m_backgroundMidRight->setSize(sf::Vector2f(1.f, 440.f));
	//m_backgroundRight1->setOrigin(m_backgroundLeft2->getSize() / 2.f);
	m_backgroundMidRight->setPosition(m_backgroundTop2->getGlobalBounds().left + m_backgroundTop2->getGlobalBounds().width, 150.f);

	RenderObject::getInstance().add(m_backgroundMidRight);


	m_backgroundBottom = std::make_shared<sf::RectangleShape>();

	m_backgroundBottom->setFillColor(sf::Color::White);
	m_backgroundBottom->setSize(sf::Vector2f(110.f * (PICKUP_AMOUNT + 1), 1.f));
	m_backgroundBottom->setOrigin(m_backgroundBottom->getSize() / 2.f);
	m_backgroundBottom->setPosition((SCREEN_WIDTH / 2.f) - 60.f, SCREEN_HEIGHT / 2.f + 150);

	RenderObject::getInstance().add(m_backgroundBottom);

	m_backgroundBottom2 = std::make_shared<sf::RectangleShape>();

	m_backgroundBottom2->setFillColor(sf::Color::White);
	m_backgroundBottom2->setSize(sf::Vector2f(90.f * (PICKUP_AMOUNT + 1), 1.f));
	m_backgroundBottom2->setOrigin(m_backgroundBottom2->getSize() / 2.f);
	m_backgroundBottom2->setPosition((SCREEN_WIDTH / 2.f) - 60.f, SCREEN_HEIGHT / 2.f + 50);

	RenderObject::getInstance().add(m_backgroundBottom2);

	m_rightBox = std::make_shared<sf::RectangleShape>();

	m_rightBox->setFillColor(sf::Color::Red);
	m_rightBox->setSize(sf::Vector2f(50.f,50.f));
	m_rightBox->setOrigin(m_rightBox->getSize() / 2.f);
	m_rightBox->setPosition(m_backgroundTop->getGlobalBounds().left, (SCREEN_HEIGHT / 2.f) - 180.f);

	//RenderObject::getInstance().add(m_rightBox);

	m_leftBox = std::make_shared<sf::RectangleShape>();

	m_leftBox->setFillColor(sf::Color::Red);
	m_leftBox->setSize(sf::Vector2f(50.f, 50.f));
	m_leftBox->setOrigin(m_leftBox->getSize() / 2.f);
	m_leftBox->setPosition(m_backgroundTop->getGlobalBounds().left + m_backgroundTop->getGlobalBounds().width, (SCREEN_HEIGHT / 2.f) - 180.f);

	//RenderObject::getInstance().add(m_leftBox);

	m_player.init(m_backgroundTop->getGlobalBounds().left, m_backgroundTop->getGlobalBounds().left + m_backgroundTop->getGlobalBounds().width, 100.f,SCREEN_HEIGHT / 2.f + 100.f, sf::Vector2f(m_backgroundTop->getGlobalBounds().left + 20, SCREEN_HEIGHT / 2.f + 100.f));

	m_enemy.init(sf::Vector2f(m_backgroundTop->getGlobalBounds().left + m_backgroundTop->getGlobalBounds().width - 20, 100.f ), m_backgroundTop->getGlobalBounds().left, m_backgroundTop->getGlobalBounds().left + m_backgroundTop->getGlobalBounds().width, 100.f, SCREEN_HEIGHT / 2.f + 100.f);

	if (m_pickupsLeft.size() != 0)
		m_pickupsLeft.clear();
	cherryPos = (rand() % PICKUP_AMOUNT_SIDE);

	for (int i = 0; i < PICKUP_AMOUNT_SIDE; i++)
	{
		PickupType type = PickupType::Normal;
		if (i == cherryPos)
			type = PickupType::Cherry;
		PickUps newPickup;
		newPickup.init(type, sf::Vector2f(m_backgroundTop->getGlobalBounds().left + 1, ((SCREEN_HEIGHT / 2.f - 100.f) - (100.f * (PICKUP_AMOUNT_SIDE / 2.f))) + (100.f * i)));
		m_pickupsLeft.push_back(newPickup);
	}

	

	if (m_pickupsRight.size() != 0)
		m_pickupsRight.clear();
	cherryPos = (rand() % PICKUP_AMOUNT_SIDE);

	for (int i = 0; i < PICKUP_AMOUNT_SIDE; i++)
	{
		PickupType type = PickupType::Normal;
		if (i == cherryPos)
			type = PickupType::Cherry;
		PickUps newPickup;
		newPickup.init(type, sf::Vector2f(m_backgroundTop->getGlobalBounds().left + m_backgroundTop->getGlobalBounds().width + 1, ((SCREEN_HEIGHT / 2.f - 100.f) - (100.f * (PICKUP_AMOUNT_SIDE / 2.f))) + (100.f * i)));
		m_pickupsRight.push_back(newPickup);
	}
}

/// <summary>
/// process all different events made by the user
/// </summary>
/// <param name="t_event">passed from game loop to speed up code</param>
void GamePlay::events(sf::Event& t_event)
{
	if (t_event.type == sf::Event::KeyPressed)
	{
		if (t_event.key.code == sf::Keyboard::Left)
		{
			if (m_rightBox->getGlobalBounds().contains(m_player.getPosition()))
			{
				m_player.setRight();
				m_player.setPosition(m_leftBox->getPosition());
				m_enemy.checkDistanceToPlayer(sf::Vector2f(0, 0));
			}
		}
		else if (t_event.key.code == sf::Keyboard::Right)
		{
			if (m_leftBox->getGlobalBounds().contains(m_player.getPosition()))
			{
				m_player.setLeft();
				m_player.setPosition(m_rightBox->getPosition());
				m_enemy.checkDistanceToPlayer(sf::Vector2f(0, 0));
			}
		}

		if (m_canChangeDirection)
		{
			m_player.invertMove();
			m_canChangeDirection = false;
		}
	}
	if (t_event.type == sf::Event::KeyReleased)
	{
		m_canChangeDirection = true;
	}
}

/// !!!---Private function---!!!
/// <summary>
/// process any input from the user
/// </summary>
/// <param name="t_event">use this for the key press</param>
void GamePlay::processKeys(sf::Event& t_event)
{
}

void GamePlay::handlePickups(std::vector<PickUps>& t_pickup)
{
	sf::Vector2f playerPos = m_player.getPosition();
	for (unsigned int i = 0; i < t_pickup.size(); i++)
	{
		if (t_pickup.at(i).getBounds().contains(playerPos))
		{
			t_pickup.at(i).itemPickedUp();
			if (t_pickup.at(i).checkCherry())
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

	for (unsigned int i = 0; i < m_pickupsBottom.size(); i++)
	{
		if (!m_pickupsBottom.at(i).getPickedUp())
		{
			reset = false;
		}
	}
	for (unsigned int i = 0; i < m_pickupsLeft.size(); i++)
	{
		if (!m_pickupsLeft.at(i).getPickedUp())
		{
			reset = false;
		}
	}
	for (unsigned int i = 0; i < m_pickupsRight.size(); i++)
	{
		if (!m_pickupsRight.at(i).getPickedUp())
		{
			reset = false;
		}
	}
	for (unsigned int i = 0; i < m_pickupsTop.size(); i++)
	{
		if (!m_pickupsTop.at(i).getPickedUp())
		{
			reset = false;
		}
	}
	if (reset)
	{
		int cherryPos = (rand() % PICKUP_AMOUNT);
		for (unsigned int i = 0; i < m_pickupsBottom.size(); i++)
		{
			PickupType type = PickupType::Normal;
			if (i == cherryPos)
				type = PickupType::Cherry;

			m_pickupsBottom.at(i).init(type, sf::Vector2f(((SCREEN_WIDTH / 2.f) - (100.f * (PICKUP_AMOUNT / 2.f))) + (100.f * i), SCREEN_HEIGHT / 2.f + 100.f) );
		}
		cherryPos = (rand() % PICKUP_AMOUNT);
		for (unsigned int i = 0; i < m_pickupsLeft.size(); i++)
		{
			PickupType type = PickupType::Normal;
			if (i == cherryPos)
				type = PickupType::Cherry;

			m_pickupsLeft.at(i).init(type, sf::Vector2f(m_backgroundTop->getGlobalBounds().left + 1, ((SCREEN_HEIGHT / 2.f - 100.f) - (100.f * (PICKUP_AMOUNT_SIDE / 2.f))) + (100.f * i)));
		}
		cherryPos = (rand() % PICKUP_AMOUNT);
		for (unsigned int i = 0; i < m_pickupsRight.size(); i++)
		{
			PickupType type = PickupType::Normal;
			if (i == cherryPos)
				type = PickupType::Cherry;

			m_pickupsRight.at(i).init(type, sf::Vector2f(m_backgroundTop->getGlobalBounds().left + m_backgroundTop->getGlobalBounds().width + 1, ((SCREEN_HEIGHT / 2.f - 100.f) - (100.f * (PICKUP_AMOUNT_SIDE / 2.f))) + (100.f * i)));
		}
		cherryPos = (rand() % PICKUP_AMOUNT);
		for (unsigned int i = 0; i < m_pickupsTop.size(); i++)
		{
			PickupType type = PickupType::Normal;
			if (i == cherryPos)
				type = PickupType::Cherry;

			m_pickupsTop.at(i).init(type, sf::Vector2f(((SCREEN_WIDTH / 2.f) - (100.f * (PICKUP_AMOUNT / 2.f))) + (100.f * i), 100.f));
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
	
	handlePickups(m_pickupsBottom);
	handlePickups(m_pickupsLeft);
	handlePickups(m_pickupsRight);
	handlePickups(m_pickupsTop);

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
