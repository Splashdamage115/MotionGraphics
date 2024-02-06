/// <summary>
/// @author David Strikaitis
/// @date 31/01/2024
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

class Bullet
{
public:
	Bullet() { m_body.setFillColor(sf::Color(252, 255, 108)); m_body.setRadius(5.0f); m_body.setOrigin(5.0f, 5.0f); }
	sf::CircleShape m_body;
	bool active = false;
	sf::Vector2f moveDirection{0.0f, 0.0f};
};

class Player
{
public:
	Player() {
		m_body.setFillColor(sf::Color(68,255,210,255));
		m_body.setSize(sf::Vector2f(30.f, 30.f));
	}
	void init()
	{
		m_body.setPosition(sf::Vector2f(450, 850));
	}

	void move()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			m_body.move(0, -MAX_SPEED);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			m_body.move(0, MAX_SPEED);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			m_body.move(-MAX_SPEED, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			m_body.move(MAX_SPEED, 0);
		}
	}

	void render(sf::RenderWindow& t_window) {
		for(int i = 0;i<BULLET_AMOUNT;i++)
			if(m_bullets[i].active)
				t_window.draw(m_bullets[i].m_body);

		t_window.draw(m_body);
	}

	void update()
	{
		if (shotCooldown > 0)
			shotCooldown--;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (shotCooldown <= 0)
			{
				for (int i = 0; i < BULLET_AMOUNT; i++)
					if (!m_bullets[i].active)
					{
						m_bullets[i].active = true;
						m_bullets[i].m_body.setPosition(m_body.getPosition() + sf::Vector2f(15.f, 15.f));
						shotCooldown = MAX_COOLDOWN;
						break;
					}
			}
		}

		for (int i = 0; i < BULLET_AMOUNT; i++)
			if (m_bullets[i].active)
				m_bullets[i].m_body.move(0.0f, -5.f);
	}

	sf::FloatRect getBody() { return m_body.getGlobalBounds(); }

	static const int BULLET_AMOUNT = 5;
	Bullet m_bullets[BULLET_AMOUNT];

private:
	sf::RectangleShape m_body;

	float MAX_SPEED = 3.5f;

	int shotCooldown = 0;
	const int MAX_COOLDOWN = 15;
};

// enemy color : 
// sf::Color(240,93,35,255)

// bullet colour:
// sf::Color(252,255,108)

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	void updateLevel();
	
	void setupFontAndText();
	void setupSprite();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game

	static const int WALL_AMOUNT = 110;
	static const int BLOCK_SIZE = 100;
	sf::RectangleShape walls[WALL_AMOUNT];

	int terrain[WALL_AMOUNT];

	int resetterrain[WALL_AMOUNT] = {
		1,1,1,1,1,0,1,1,1,1,
		1,1,1,1,0,0,0,1,1,1,
		1,1,1,0,0,5,0,0,1,1,
		1,1,0,0,0,0,0,0,1,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1
	};

	int currentCounterPos = 0;

	Player player;

	Bullet wallBullets[5];
	int fireCooldown = 30;

	int score = 0;
};

#endif // !GAME_HPP

