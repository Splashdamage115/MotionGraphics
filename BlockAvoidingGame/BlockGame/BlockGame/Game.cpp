/// <summary>
/// @author David Strikaitis
/// @date 31/01/2024
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>
#include <cstdlib>
#include<time.h>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 1000U, 1000U, 32U }, "BlockGame" },
	m_exitGame{false} //when true game will exit
{
	srand(time(nullptr));

	if (!m_logoTexture.loadFromFile("ASSETS\\IMAGES\\SFML-LOGO.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}

	setupFontAndText(); // load font 
	setupSprite(); // load texture
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::Space == t_event.key.code)
	{
		// shoot weapon here
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (fireCooldown > 0)
		fireCooldown--;
	else
	{
		for (int i = 0; i < WALL_AMOUNT; i++)
		{
			if (terrain[i] == 2 || terrain[i] == 3)
			{
				for (Bullet& b : wallBullets)
				{
					if (!b.active)
					{
						b.active = true;
						b.m_body.setPosition(walls[i].getPosition() + sf::Vector2f(50.f, 50.f));
						if (terrain[i] == 2)
							b.moveDirection = sf::Vector2f(4.0f, 3.0f);
						else if(terrain[i] == 3)
							b.moveDirection = sf::Vector2f(-4.0f, 3.0f);
						fireCooldown = 30;
						break;
					}
				}
				continue;
			}
					
		}
	}
	for (Bullet& b : wallBullets)
	{
		if (b.active)
		{
			b.m_body.move(b.moveDirection);
		}
	}

	if (m_exitGame)
	{
		m_window.close();
	}
	player.move();
	player.update();
	updateLevel();

	for (int i = 0; i < WALL_AMOUNT; i++)
	{
		if (walls[i].getGlobalBounds().intersects(player.getBody()) && (terrain[i] >= 1))
		{
			if(terrain[i] == 1 || terrain[i] == 2 || terrain[i] == 3)
				setupSprite();
			else if (terrain[i] == 5)
			{
				for (int j = 0; j < WALL_AMOUNT; j++)
				{
					terrain[j] = 0;
					walls[j].setFillColor(sf::Color::Transparent);
				}
			}
			else if (terrain[i] == 4)
			{
				terrain[i] = 0;
				walls[i].setFillColor(sf::Color::Transparent);
				score += 100;
			}
			break;
		}
	}

	for (int i = 0; i < WALL_AMOUNT; i++)
	{
		for (Bullet& b : wallBullets)
		{
			if (!b.active)
				continue;
			if (terrain[i] == 2 || terrain[i] == 3 || terrain[i] == 0)
				continue;
			if (walls[i].getGlobalBounds().intersects(b.m_body.getGlobalBounds())
				|| b.m_body.getPosition().x < 50.f || b.m_body.getPosition().x > 1050.f)
			{
				b.active = false;
				b.m_body.setPosition(0.0f, -100.0f);
			}
			if (b.m_body.getGlobalBounds().intersects(player.getBody()))
				setupSprite();
		}

		for (int w = 0; w < 5; w++)
		{
			if (!player.m_bullets[w].active)
				continue;
			if (walls[i].getGlobalBounds().intersects(player.m_bullets[w].m_body.getGlobalBounds()) && terrain[i] >= 1)
			{
				if (terrain[i] == 2 || terrain[i] == 3 || terrain[i] == 4)
				{
					terrain[i] = 0;
					walls[i].setFillColor(sf::Color::Transparent);
				if (terrain[i] == 4)
					score += 100;
				}
				
				else if (terrain[i] == 5)
				{
					for (int j = 0; j < WALL_AMOUNT; j++)
					{
						terrain[j] = 0;
						walls[j].setFillColor(sf::Color::Transparent);
					}
					break;
				}
				player.m_bullets[w].active = false;
				player.m_bullets[w].m_body.setPosition(0.0f,-100.0f);
			}
		}
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color(97,97,99,255));

	player.render(m_window);

	for (Bullet& b : wallBullets)
		m_window.draw(b.m_body);

	for (int i = 0; i < WALL_AMOUNT; i++)
	{
		m_window.draw(walls[i]);
	}
	

	//m_window.draw(m_welcomeMessage);
	//m_window.draw(m_logoSprite);
	m_window.display();
}

void Game::updateLevel()
{
	for (int j = 0; j < WALL_AMOUNT; j += 10)
	{
		if (walls[j].getPosition().y > 1000)
		{
			int len = 0;
			int gap = 0;
			if (j + 11 >= 110)
			{
				bool impassable = true;
				while (impassable)
				{
					len = rand() % 9;
					gap = rand() % 9;

					for (int i = 0; i < 11; i++)
					{
						if ((i % 10) < len)
						{
							continue;
						}
						else if ((i % 10) < len + gap)
						{
							if (terrain[i] == 0)
							{
								impassable = false;
								break;
							}
						}
						else
						{
							break;
						}
					}
				}
			}
			else
			{
				bool impassable = true;
				while (impassable)
				{
					len = rand() % 9;
					gap = rand() % 9;

					for (int i = j + 10; i < j + 21; i++)
					{
						if ((i % 10) < len)
						{
							continue;
						}
						else if ((i % 10) < len + gap)
						{
							if (terrain[i] == 0)
							{
								impassable = false;
								break;
							}
						}
						else
						{
							break;
						}
					}
				}
			}

			for (int i = j; i < j + 10; i++)
			{
				if (i < len + j)
				{
					terrain[i] = 1;
				}
				else if (i < len + gap + j)
				{
					terrain[i] = 0;
				}
				else
				{
					terrain[i] = 1;
				}
			}

			if (gap > 1)
			{
				int spawnEnemy = rand() % 4;
				int spawnPowerUp = rand() % 15;
				if (spawnEnemy == 0)
				{
					if (rand() % 2 == 0)
					{
						terrain[len + j] = 2; // shoot right
					}
					else
					{
						terrain[len + j + gap - 1] = 3; // shoot left
					}
				}
				else
				{
					if (spawnPowerUp == 0)
					{
						spawnPowerUp = rand() % 2;
						int spawnPos = rand() % gap;
						terrain[len + spawnPos + j] = spawnPowerUp + 4;
					}
				}
			}

			for (int i = j; i < j + 10; i++)
			{


				walls[i].move(0, -1100);
				if (terrain[i] == 1)
				{
					walls[i].setFillColor(sf::Color(135, 246, 255, 255));
				}
				else if (terrain[i] == 0)
				{
					walls[i].setFillColor(sf::Color::Transparent);
				}
				else if (terrain[i] == 2 || terrain[i] == 3)
				{
					walls[i].setFillColor(sf::Color(240, 93, 35, 255));
				}
				else if (terrain[i] == 4)
				{
					walls[i].setFillColor(sf::Color::Green);
				}
				else if (terrain[i] == 5)
				{
					walls[i].setFillColor(sf::Color::Magenta);
				}
			}

			//currentCounterPos++;
		}
	}
	for (int i = 0; i < WALL_AMOUNT; i++)
	{
		walls[i].move(sf::Vector2f(0, 3.f));
	}
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("SFML Game");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80U);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	player.init();
	for (int w = 0; w < player.BULLET_AMOUNT; w++)
	{
		player.m_bullets[w].active = false;
		player.m_bullets[w].m_body.setPosition(0.0f, -100.0f);
	}

	for (Bullet& b : wallBullets)
		b.active = false;
	
	m_logoSprite.setTexture(m_logoTexture);
	m_logoSprite.setPosition(300.0f, 180.0f);
	int yPosCounter = -1;

	for (int i = 0; i < WALL_AMOUNT; i++)
		terrain[i] = resetterrain[i];

	for (int i = 0;i<WALL_AMOUNT; i++)
	{
		if ((i % 10) == 0)
			yPosCounter++;

		float xPos = (i % 10) * BLOCK_SIZE;
		float yPos = yPosCounter * BLOCK_SIZE;

		

		walls[i].setPosition(xPos,yPos);
		walls[i].setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));

		if (terrain[i] == 1)
		{
			walls[i].setFillColor(sf::Color(135, 246, 255, 255));
		}
		else if (terrain[i] == 0)
		{
			walls[i].setFillColor(sf::Color::Transparent);
		}
		else if (terrain[i] == 2 || terrain[i] == 3)
		{
			walls[i].setFillColor(sf::Color(240, 93, 35, 255));
		}
		else if (terrain[i] == 4)
		{
			walls[i].setFillColor(sf::Color::Green);
		}
		else if (terrain[i] == 5)
		{
			walls[i].setFillColor(sf::Color::Magenta);
		}
	}
}
