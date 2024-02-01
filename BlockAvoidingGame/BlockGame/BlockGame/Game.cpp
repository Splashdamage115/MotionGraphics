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
		setupSprite();
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	player.move();
	updateLevel();

	for (int i = 0; i < WALL_AMOUNT; i++)
		if (walls[i].getGlobalBounds().intersects(player.getBody()) &&	terrain[i] >= 1)
		{
			setupSprite();
			break;
		}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color(97,97,99,255));

	for (int i = 0; i < WALL_AMOUNT; i++)
	{
		m_window.draw(walls[i]);
	}

	player.render(m_window);

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

			for (int i = j; i < j + 10; i++)
			{


				walls[i].move(0, -1100);
				if (terrain[i] == 1)
				{
					walls[i].setFillColor(sf::Color(135, 246, 255, 255));
				}
				else
				{
					walls[i].setFillColor(sf::Color::Transparent);
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
			walls[i].setFillColor(sf::Color(135,246,255,255));
		}
		else
		{
			walls[i].setFillColor(sf::Color::Transparent);
		}
	}
}
