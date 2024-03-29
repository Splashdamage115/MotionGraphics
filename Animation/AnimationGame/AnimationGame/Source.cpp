// platform game.....
// Author :Noel O' Hara

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <time.h> 

class Game
{
public:
	int slowMoTimeLeft = 0;
	int ExtraJumpTimeLeft = 0;
	sf::Font Font;
	sf::Text winText;
	sf::Sprite m_playerS;
	sf::Texture m_playerT;
	//create Window
	sf::RenderWindow window;
	sf::View view;
	float randomNum;
	float delay{ 0.125f };
	float frameTimer{ 0.f };
	int currentFrame{ 0 };
	int frameHeight{ 0 };
	bool playNextLevel{ false };

	sf::RectangleShape playerShape;

	float velocityX = 0, velocityY = 0, gravity = 0.3;

	static const int numRows = 20;
	static const int numCols = 45;
	static const int tileNum = numRows * numCols;

	int levelData[2][numRows][numCols] = { {
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 2 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 1 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 1 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 4 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 4 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 5 , 0 , 0 , 2 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 5 , 0 , 5 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 3 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 1 , 1 },
	{ 0 , 0 , 0 , 0 , 0 , 1 , 0 , 2 , 0 , 2 , 0 , 0 , 0 , 0 , 5 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 5 , 0 , 0 , 0 },
	{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 2 , 1 , 1 , 1 , 0 , 0 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 0 , 0 , 0 } },
	
		{
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 4 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 5 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 4 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 5 , 1 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 2 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 1 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 5 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 2 , 0 , 0 , 0 , 0 , 0 , 0 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 5 , 0 , 5 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 3 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 },
	{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 2 , 0 , 2 , 0 , 0 , 5 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 5 , 0 , 0 , 0 , 0 },
	{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 0 , 0 , 0 },
	} };

	sf::Sprite bodies[numRows][numCols];

	sf::Texture tile; sf::Texture jump; sf::Texture timeTile; sf::Texture death; sf::Texture win;

	sf::RectangleShape level[numRows][numCols];

	sf::SoundBuffer jumpSoundBuffer;
	sf::SoundBuffer deathSoundBuffer;

	sf::Sound m_sounddeath;
	sf::Sound m_soundJump;

	Game()
	{
		jumpSoundBuffer.loadFromFile("Jump.wav");
		deathSoundBuffer.loadFromFile("Pain.wav");

		m_sounddeath.setBuffer(deathSoundBuffer);
		m_soundJump.setBuffer(jumpSoundBuffer);


		window.create(sf::VideoMode(800, 600), "Endless Runner Game");
		if(!Font.loadFromFile("PixelSans.ttf"))
		{
			std::cout << "DIDNT LOAD TEXT\n";
		}
		winText.setFont(Font);
		winText.setPosition(200.f, 300.f);
		winText.setCharacterSize(32u);
		winText.setString("you win");
		winText.setFillColor(sf::Color::Transparent);
		if (!m_playerT.loadFromFile("player.png"))
		{
			std::cout << "DIDNT LOAD Player\n";
		}
		m_playerS.setTexture(m_playerT);
		m_playerS.setTextureRect(sf::IntRect(0,0,375,666));
		m_playerS.setScale(0.08f, 0.08f);
		m_playerS.setOrigin(115.f, 235.f);

		tile.loadFromFile("tileNormal.png");
		jump.loadFromFile("jumpTile.png");
		timeTile.loadFromFile("time.png");
		death.loadFromFile("death.png");
		win.loadFromFile("win.png");
		
		
	}
	void init()
	{


		slowMoTimeLeft = 0;
		ExtraJumpTimeLeft = 0;
		winText.setFillColor(sf::Color::Transparent);

		view = window.getDefaultView();
		playerShape.setSize(sf::Vector2f(20, 20));
		playerShape.setPosition(160, 500);
		m_playerS.setPosition(160, 500);
		m_playerS.setPosition(playerShape.getPosition());

		if (!playNextLevel) {
			for (int col = 0; col < numCols; col++)
			{
				for (int row = 0; row < numRows; row++)
				{
					if (levelData[0][row][col] == 0)
					{
						continue;
					}
					else if (levelData[0][row][col] == 1)
					{
						bodies[row][col].setTexture(tile);
					}
					else if (levelData[0][row][col] == 2)
					{
						bodies[row][col].setTexture(death);
					}
					else if (levelData[0][row][col] == 3)
					{
						bodies[row][col].setTexture(win);
					}
					else if (levelData[0][row][col] == 4)
					{
						bodies[row][col].setTexture(timeTile);
					}
					else if (levelData[0][row][col] == 5)
					{
						bodies[row][col].setTexture(jump);
					}
				}
			}
			for (int col = 0; col < numCols; col++)
			{
				for (int row = 0; row < numRows; row++)
				{

					if (levelData[0][row][col] == 1)
					{

						level[row][col].setSize(sf::Vector2f(70, 30));
						level[row][col].setPosition(col * 70, row * 30);
						level[row][col].setFillColor(sf::Color::Red);
					}
					if (levelData[0][row][col] == 0)
					{

						level[row][col].setSize(sf::Vector2f(70, 30));
						level[row][col].setPosition(col * 70, row * 30);
						level[row][col].setFillColor(sf::Color::Black);
					}
					if (levelData[0][row][col] == 2)
					{
						level[row][col].setSize(sf::Vector2f(70, 30));
						level[row][col].setPosition(col * 70, row * 30);

						level[row][col].setFillColor(sf::Color::Blue);

					}
					if (levelData[0][row][col] == 3)
					{
						level[row][col].setSize(sf::Vector2f(70, 30));
						level[row][col].setPosition(col * 70, row * 30);

						level[row][col].setFillColor(sf::Color::Green);
					}

					if (levelData[0][row][col] == 4)
					{
						level[row][col].setSize(sf::Vector2f(70, 30));
						level[row][col].setPosition(col * 70, row * 30);

						level[row][col].setFillColor(sf::Color::Magenta);

					}
					if (levelData[0][row][col] == 5)
					{
						level[row][col].setSize(sf::Vector2f(70, 30));
						level[row][col].setPosition(col * 70, row * 30);

						level[row][col].setFillColor(sf::Color::Yellow);

					}
				}
				std::cout << std::endl;
			}

		}

		else
		{
			for (int col = 0; col < numCols; col++)
			{
				for (int row = 0; row < numRows; row++)
				{
					if (levelData[1][row][col] == 0)
					{
						continue;
					}
					else if (levelData[1][row][col] == 1)
					{
						bodies[row][col].setTexture(tile);
					}
					else if (levelData[1][row][col] == 2)
					{
						bodies[row][col].setTexture(death);
					}
					else if (levelData[1][row][col] == 3)
					{
						bodies[row][col].setTexture(win);
					}
					else if (levelData[1][row][col] == 4)
					{
						bodies[row][col].setTexture(timeTile);
					}
					else if (levelData[1][row][col] == 5)
					{
						bodies[row][col].setTexture(jump);
					}
				}
			}
			for (int col = 0; col < numCols; col++)
			{
				for (int row = 0; row < numRows; row++)
				{

					if (levelData[1][row][col] == 1)
					{

						level[row][col].setSize(sf::Vector2f(70, 30));
						level[row][col].setPosition(col * 70, row * 30);
						level[row][col].setFillColor(sf::Color::Red);
					}
					if (levelData[1][row][col] == 0)
					{

						level[row][col].setSize(sf::Vector2f(70, 30));
						level[row][col].setPosition(col * 70, row * 30);
						level[row][col].setFillColor(sf::Color::Black);
					}
					if (levelData[1][row][col] == 2)
					{
						level[row][col].setSize(sf::Vector2f(70, 30));
						level[row][col].setPosition(col * 70, row * 30);

						level[row][col].setFillColor(sf::Color::Blue);

					}
					if (levelData[1][row][col] == 3)
					{
						level[row][col].setSize(sf::Vector2f(70, 30));
						level[row][col].setPosition(col * 70, row * 30);

						level[row][col].setFillColor(sf::Color::Green);
					}

					if (levelData[1][row][col] == 4)
					{
						level[row][col].setSize(sf::Vector2f(70, 30));
						level[row][col].setPosition(col * 70, row * 30);

						level[row][col].setFillColor(sf::Color::Magenta);

					}
					if (levelData[1][row][col] == 5)
					{
						level[row][col].setSize(sf::Vector2f(70, 30));
						level[row][col].setPosition(col * 70, row * 30);

						level[row][col].setFillColor(sf::Color::Yellow);

					}

				}
				std::cout << std::endl;
			}
		}
	}
	void run()
	{


		sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);


		sf::Time timeSinceLastUpdate = sf::Time::Zero;


		sf::Clock clock;

		clock.restart();

		while (window.isOpen())
		{
			// events =======================================================================
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			timeSinceLastUpdate += clock.restart();

			if (timeSinceLastUpdate > timePerFrame)
			{ // update =====================================================================
				if (slowMoTimeLeft > 0)
					slowMoTimeLeft--;
				if (ExtraJumpTimeLeft > 0)
					ExtraJumpTimeLeft--;

				frameTimer += delay;
				if (static_cast<int>(frameTimer) >= 1)
				{
					frameTimer = 0;
					currentFrame++;
					if (currentFrame > 7)
						currentFrame = 0;
					m_playerS.setTextureRect(sf::IntRect((375 * currentFrame), frameHeight * 666, 375, 666));

				}

				for (int row = 0; row < numRows; row++)
				{
					for (int col = 0; col < numCols; col++)
					{
						if (slowMoTimeLeft <= 0)
						{
							level[row][col].move(-3.7, 0);
							//bodies[row * col].move(- 3.7, 0);

						}
						else
						{
							level[row][col].move(-2.4, 0);
							//bodies[row * col].move(-2.4, 0);

						}
					}

				}



				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (velocityY == 0 || ExtraJumpTimeLeft > 0))
				{
					if (velocityY != 0 && ExtraJumpTimeLeft > 0)
					{
						velocityY = -23;
						ExtraJumpTimeLeft = 0;
					}
					else
						velocityY = -11.8;
					m_soundJump.play();

				}

				velocityY = velocityY + gravity;
				playerShape.move(0, velocityY);

				m_playerS.setPosition(playerShape.getPosition());

				gravity = 0.6;
				if (!playNextLevel)
				{
					for (int row = 0; row < numRows; row++)
					{
						for (int col = 0; col < numCols; col++)
						{
							if (velocityY >= 0)
							{
								if (levelData[0][row][col] == 1)
								{

									if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
									{
										if (playerShape.getPosition().y < level[row][col].getPosition().y)
										{
											frameHeight = 0;
											gravity = 0;
											velocityY = 0;
											playerShape.setPosition(playerShape.getPosition().x, level[row][col].getPosition().y);
											playerShape.move(0, -playerShape.getGlobalBounds().height);
											break;
										}
										else
										{
											init();
											m_sounddeath.play();

										}
									}


								}

							}
							if (velocityY < 0)
							{
								if (levelData[0][row][col] == 1)
								{
									if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
									{
										init();
										m_sounddeath.play();

									}

								}

							}
							if (levelData[0][row][col] == 2)
							{
								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									init();
									m_sounddeath.play();

								}
							}
							if (levelData[0][row][col] == 3)
							{
								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									if (playNextLevel)
										winText.setFillColor(sf::Color::White);
									playNextLevel = true;
								}
							}
							if (levelData[0][row][col] == 4)
							{
								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									slowMoTimeLeft = 360;
								}
							}
							if (levelData[0][row][col] == 5)
							{
								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									ExtraJumpTimeLeft = 100;
								}
							}
						}
					}
				}
				else
				{
					for (int row = 0; row < numRows; row++)
					{
						for (int col = 0; col < numCols; col++)
						{
							if (velocityY >= 0)
							{
								if (levelData[1][row][col] == 1)
								{

									if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
									{
										if (playerShape.getPosition().y < level[row][col].getPosition().y)
										{
											frameHeight = 0;
											gravity = 0;
											velocityY = 0;
											playerShape.setPosition(playerShape.getPosition().x, level[row][col].getPosition().y);
											playerShape.move(0, -playerShape.getGlobalBounds().height);
											break;
										}
										else
										{
											init();

											m_sounddeath.play();

										}
									}


								}

							}
							if (velocityY < 0)
							{
								if (levelData[1][row][col] == 1)
								{
									if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
									{
										init();
										m_sounddeath.play();

									}

								}

							}
							if (levelData[1][row][col] == 2)
							{
								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									init();
									m_sounddeath.play();

								}
							}
							if (levelData[1][row][col] == 3)
							{
								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									if (playNextLevel)
										winText.setFillColor(sf::Color::White);
									playNextLevel = true;
								}
							}
							if (levelData[1][row][col] == 4)
							{
								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									slowMoTimeLeft = 360;
								}
							}
							if (levelData[1][row][col] == 5)
							{
								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									ExtraJumpTimeLeft = 100;
								}
							}
						}
					}
				}
				if (velocityY > 0.7)
					frameHeight = 1;

				if (playerShape.getPosition().y > 600)
				{
					init();
					m_sounddeath.play();

				}

				window.clear();

				for (int row = 0; row < numRows; row++)
				{
					for (int col = 0; col < numCols; col++)
					{
						window.draw(level[row][col]);
						bodies[row][col].setPosition(level[row][col].getPosition());
						window.draw(bodies[row][col]);
					}
				}
				window.draw(playerShape);
				window.draw(m_playerS);

				window.draw(winText);

				window.display();

				timeSinceLastUpdate = sf::Time::Zero;
			}
		}
	}
};


int main()
{
	Game game;
	game.init();
	game.run();

	return 0;
}