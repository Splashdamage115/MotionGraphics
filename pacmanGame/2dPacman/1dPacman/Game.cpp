/// <summary>
/// @author David Strikaitis
/// @date 08/05/2023
///
/// </summary>

#include "Game.h"
#include <iostream>
#include<ctime>
#include<cstdlib>


// setup of static variables
GameModeClass Game::s_currentGameMode = GameModeClass::GamePlay;
bool Game::s_changeGameMode = true;
bool Game::s_gameActive = true;

/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game()
{
	srand( static_cast<unsigned int>(time(nullptr)));

	m_renderer = &RenderObject::getInstance();

	changeGameMode();
}

/// <summary>
/// default destructor 
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
	while (m_renderer->getWindow().isOpen())
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
	while (m_renderer->getWindow().pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // The game is closed!
		{
			Game::s_gameActive = false;
		}
		if (sf::Event::KeyPressed == newEvent.type) // this is currently used to check if the user pressed esc
		{
			processKeys(newEvent);
		}

		m_gameMode->events(newEvent);
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
		Game::s_gameActive = false;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (!s_gameActive)
	{
		m_renderer->closeWindow();
	}

	m_gameMode->update(t_deltaTime);

	changeGameMode();
}

/// <summary>
/// pass the render porperties to the singleton renderer
/// </summary>
void Game::render()
{
	m_renderer->render();
}

/// <summary>
/// this just initialises a new game mode
/// </summary>
void Game::changeGameMode()
{
	if (s_changeGameMode)
	{
		RenderObject::getInstance().clear();

		if (s_currentGameMode == GameModeClass::GamePlay)
			m_gameMode = std::make_unique<GamePlay>();

		s_changeGameMode = false;
	}
}
