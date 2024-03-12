// platform game.....
// Author :David Strikaitis

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

bool levelEditorActive = false;
bool mainMenu = true;
bool resetLevel = false;
bool closeGame = false;

bool textureMode = false;

static const int numRows = 20;
static const int numCols = 45;
int levelData[numRows][numCols] = {
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
	{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 2 , 1 , 1 , 1 , 0 , 0 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 1 , 0 , 0 , 0 } };

class Menu
{
public:
	void init()
	{
		if (!m_font.loadFromFile("PixelSans.ttf"))
		{
			std::cout << "DIDNT LOAD TEXT\n";
		}
		for (int i = 0; i < BUTTON_AMOUNT; i++)
		{
			m_buttons[i].setSize(sf::Vector2f(200.f, 100.f));
			m_buttons[i].setPosition(sf::Vector2f(300.f, 100.f + (120.f * i)));
			m_buttonNames[i].setPosition(sf::Vector2f(350.f, 130.f + (120.f * i)));
			m_buttonNames[i].setFont(m_font);
			m_buttonNames[i].setCharacterSize(42u);
			m_buttonNames[i].setOutlineColor(sf::Color::Black);
			m_buttonNames[i].setOutlineThickness(2u);
		}
		m_buttonNames[0].setString("Play");
		m_buttonNames[1].setString("Edit");
		m_buttonNames[2].setString("Quit");


	}
	void events(sf::Event t_event)
	{
		if (t_event.type == sf::Event::MouseMoved)
		{
			m_mousePos = { static_cast<float>(t_event.mouseMove.x),static_cast<float>(t_event.mouseMove.y) };
		}
	}
	void update()
	{
		for (int i = 0; i < BUTTON_AMOUNT; i++)
		{
			if (m_buttons[i].getGlobalBounds().contains(m_mousePos))
			{
				m_buttons[i].setFillColor(sf::Color(255, 255, 255, 180));
			}
			else
			{
				m_buttons[i].setFillColor(sf::Color(255, 255, 255, 255));
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			for (int i = 0; i < BUTTON_AMOUNT; i++)
			{
				if (m_buttons[i].getGlobalBounds().contains(m_mousePos))
				{
					if (i == 0)
					{
						mainMenu = false;
						levelEditorActive = false;
					}
					if (i == 1)
					{
						mainMenu = false;
						levelEditorActive = true;
					}
					if (i == 2)
					{
						closeGame = true;
					}
				}
			}
		}
	}
	void render(sf::RenderWindow& t_window)
	{
		for (int i = 0; i < BUTTON_AMOUNT; i++)
		{
			t_window.draw(m_buttons[i]);
			t_window.draw(m_buttonNames[i]);
		}
	}
private:
	static const int BUTTON_AMOUNT{ 3 };
	sf::RectangleShape m_buttons[BUTTON_AMOUNT];
	sf::Text m_buttonNames[BUTTON_AMOUNT];
	sf::Font m_font;

	sf::Vector2f m_mousePos{ 0.f,0.f };
};

class LevelEditor
{
public:
	void init() 
	{
		if (!m_font.loadFromFile("PixelSans.ttf"))
		{
			std::cout << "DIDNT LOAD TEXT\n";
		}
		m_dispString.setFont(m_font);
		m_dispString.setPosition(0.f, 0.f);
		m_dispString.setCharacterSize(12u);
		m_dispString.setString("Right Click - clears tiles\n\nLeft click -  places tiles\n\nA -              moves left\n\nD -              moves right");


		m_leftMenu.setSize(sf::Vector2f(200.f, 600.f));
		m_leftMenu.setFillColor(sf::Color(0,0,0,255));
		m_leftMenu.setOutlineColor(sf::Color::White);
		m_leftMenu.setOutlineThickness(1u);

		for (int i = 0; i < BUTTON_AMOUNT; i++)
		{
			m_button[i].setSize(sf::Vector2f(100.f, 30.f));
			m_button[i].setPosition(sf::Vector2f(50.f, 150.f + (i * 100.f)));
			m_buttonOverlay[i].setSize(sf::Vector2f(100.f, 30.f));
			m_buttonOverlay[i].setPosition(sf::Vector2f(50.f, 150.f + (i * 100.f)));

			if(i == 0)
				m_button[i].setFillColor(sf::Color::Red);
			else if (i == 1)
				m_button[i].setFillColor(sf::Color::Blue);
			else if (i == 2)
				m_button[i].setFillColor(sf::Color::Green);
			else if (i == 3)
				m_button[i].setFillColor(sf::Color::Magenta);
			else if (i == 4)
				m_button[i].setFillColor(sf::Color::Yellow);

			m_button[i].setOutlineColor(sf::Color::White);
			m_button[i].setOutlineThickness(1u);

		}




		for (int col = 0; col < numCols; col++)
		{
			for (int row = 0; row < numRows; row++)
			{
				levelMoveOffset[row][col] = sf::Vector2f(0.f, 0.f);
			}
		}
	}
	void events(sf::Event t_event)
	{
		if (t_event.type == sf::Event::MouseMoved)
		{
			m_mousePos = { static_cast<float>(t_event.mouseMove.x),static_cast<float>(t_event.mouseMove.y) };
		}
	}
	void update() 
	{

		for (int i = 0; i < BUTTON_AMOUNT; i++)
		{
			if (m_button[i].getGlobalBounds().contains(m_mousePos))
			{
				m_buttonOverlay[i].setFillColor(sf::Color(255, 255, 255, 180));
			}
			else
			{
				m_buttonOverlay[i].setFillColor(sf::Color(0, 0, 0, 0));
			}
			if (i + 1 == lastButtonPressed)
			{
				m_buttonOverlay[i].setFillColor(sf::Color(0, 0, 0, 185));
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		{
			for (int col = 0; col < numCols; col++)
			{
				for (int row = 0; row < numRows; row++)
				{
					if (level[row][col].getGlobalBounds().contains(m_mousePos))
					{
						levelData[row][col] = 0;
						break;
					}
				}
			}
		}

		bool clickInMenu{ false };

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			if (m_leftMenu.getGlobalBounds().contains(m_mousePos))
			{
				clickInMenu = true;

				for (int i = 0; i < BUTTON_AMOUNT; i++)
				{
					if (m_button[i].getGlobalBounds().contains(m_mousePos))
					{
						lastButtonPressed = i + 1;
					}
				}
			}
			if (!clickInMenu)
			{
				for (int col = 0; col < numCols; col++)
				{
					for (int row = 0; row < numRows; row++)
					{
						if (level[row][col].getGlobalBounds().contains(m_mousePos))
						{
							levelData[row][col] = lastButtonPressed;
							break;
						}
					}
				}
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			for (int col = 0; col < numCols; col++)
			{
				for (int row = 0; row < numRows; row++)
				{
					levelMoveOffset[row][col].x -= 2.f;
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			for (int col = 0; col < numCols; col++)
			{
				for (int row = 0; row < numRows; row++)
				{
					levelMoveOffset[row][col].x += 2.f;
				}
			}
		}
	}
	void draw(sf::RenderWindow& t_window)
	{
		for (int col = 0; col < numCols; col++)
		{
			for (int row = 0; row < numRows; row++)
			{
				level[row][col].setOutlineColor(sf::Color::White);
				level[row][col].setOutlineThickness(1u);
				if (levelData[row][col] == 1)
				{

					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(col * 70, row * 30);
					level[row][col].setFillColor(sf::Color::Red);
				}
				if (levelData[row][col] == 0)
				{

					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(col * 70, row * 30);
					level[row][col].setFillColor(sf::Color::Black);
				}
				if (levelData[row][col] == 2)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(col * 70, row * 30);

					level[row][col].setFillColor(sf::Color::Blue);

				}
				if (levelData[row][col] == 3)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(col * 70, row * 30);

					level[row][col].setFillColor(sf::Color::Green);
				}

				if (levelData[row][col] == 4)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(col * 70, row * 30);

					level[row][col].setFillColor(sf::Color::Magenta);

				}
				if (levelData[row][col] == 5)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(col * 70, row * 30);

					level[row][col].setFillColor(sf::Color::Yellow);

				}
				level[row][col].move(levelMoveOffset[row][col]);

				if (level[row][col].getGlobalBounds().contains(m_mousePos))
				{
					level[row][col].setFillColor(sf::Color(255,255,255,80));
				}

				t_window.draw(level[row][col]);
			}
		}
		t_window.draw(m_leftMenu);

		for (int i = 0; i < BUTTON_AMOUNT; i++)
		{
			t_window.draw(m_button[i]);
			t_window.draw(m_buttonOverlay[i]);
		}
		t_window.draw(m_dispString);
	}
private:
	sf::RectangleShape level[numRows][numCols];
	sf::Vector2f levelMoveOffset[numRows][numCols];

	sf::Vector2f m_mousePos{ 0.f, 0.f };

	sf::RectangleShape m_leftMenu;

	int lastButtonPressed{ 1 };

	static const int BUTTON_AMOUNT{ 5 };
	sf::RectangleShape m_button[BUTTON_AMOUNT];
	sf::RectangleShape m_buttonOverlay[BUTTON_AMOUNT];

	sf::Text m_dispString;
	sf::Font m_font;
};

class Game
{
public:
	int slowMoTimeLeft = 0;
	int ExtraJumpTimeLeft = 0;
	sf::Font Font;
	sf::Text winText;
	//create Window
	sf::RenderWindow window;
	sf::View view;
	float randomNum;


	sf::Sprite m_playerS;
	sf::Texture m_playerT;
	float delay{ 0.125f };
	float frameTimer{ 0.f };
	int currentFrame{ 0 };
	int frameHeight{ 0 };


	sf::RectangleShape playerShape;

	float velocityX = 0, velocityY = 0, gravity = 0.3;


	static const int tileNum = numRows * numCols;

	sf::RectangleShape level[numRows][numCols];

	//sf::Sprite bodies[numRows][numCols];
	sf::Texture tile; sf::Texture jump; sf::Texture timeTile; sf::Texture death; sf::Texture win;

	Menu menu;
	LevelEditor editor;

	Game()
	{
		menu.init();
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
		m_playerS.setTextureRect(sf::IntRect(0, 0, 375, 666));
		m_playerS.setScale(0.08f, 0.08f);
		m_playerS.setOrigin(115.f, 235.f);

		tile.loadFromFile("tileNormal.png");
		jump.loadFromFile("jumpTile.png");
		timeTile.loadFromFile("time.png");
		death.loadFromFile("death.png");
		win.loadFromFile("win.png");


		editor.init();
	}
	void init()
	{
		resetLevel = false;
		slowMoTimeLeft = 0;
		ExtraJumpTimeLeft = 0;
		winText.setFillColor(sf::Color::Transparent);

		view = window.getDefaultView();
		playerShape.setSize(sf::Vector2f(20, 20));
		playerShape.setPosition(160, 500);

		//for (int col = 0; col < numCols; col++)
		//{
		//	for (int row = 0; row < numRows; row++)
		//	{
		//		//bodies[row][col].setPosition(col * 70, row * 30);

		//		if (levelData[row][col] == 0)
		//		{
		//			continue;
		//		}
		//		else if (levelData[row][col] == 1)
		//		{
		//			bodies[row][col].setTexture(tile);
		//		}
		//		else if (levelData[row][col] == 2)
		//		{
		//			bodies[row][col].setTexture(death);
		//		}
		//		else if (levelData[row][col] == 3)
		//		{
		//			bodies[row][col].setTexture(win);
		//		}
		//		else if (levelData[row][col] == 4)
		//		{
		//			bodies[row][col].setTexture(timeTile);
		//		}
		//		else if (levelData[row][col] == 5)
		//		{
		//			bodies[row][col].setTexture(jump);
		//		}
		//	}
		//}
			for (int col = 0; col < numCols; col++)
			{
				for (int row = 0; row < numRows; row++)
				{

					if (levelData[row][col] == 1)
					{

						level[row][col].setSize(sf::Vector2f(70, 30));
						level[row][col].setPosition(col * 70, row * 30);
						level[row][col].setFillColor(sf::Color::Red);
					}
					if (levelData[row][col] == 0)
					{

						level[row][col].setSize(sf::Vector2f(70, 30));
						level[row][col].setPosition(col * 70, row * 30);
						level[row][col].setFillColor(sf::Color::Black);
					}
					if (levelData[row][col] == 2)
					{
						level[row][col].setSize(sf::Vector2f(70, 30));
						level[row][col].setPosition(col * 70, row * 30);

						level[row][col].setFillColor(sf::Color::Blue);

					}
					if (levelData[row][col] == 3)
					{
						level[row][col].setSize(sf::Vector2f(70, 30));
						level[row][col].setPosition(col * 70, row * 30);

						level[row][col].setFillColor(sf::Color::Green);
					}

					if (levelData[row][col] == 4)
					{
						level[row][col].setSize(sf::Vector2f(70, 30));
						level[row][col].setPosition(col * 70, row * 30);

						level[row][col].setFillColor(sf::Color::Magenta);

					}
					if (levelData[row][col] == 5)
					{
						level[row][col].setSize(sf::Vector2f(70, 30));
						level[row][col].setPosition(col * 70, row * 30);

						level[row][col].setFillColor(sf::Color::Yellow);

					}
				}
				std::cout << std::endl;
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
			
			if (mainMenu)
			{
				menu.events(event);
			}
			else if (levelEditorActive)
			{
				editor.events(event);
			}

			timeSinceLastUpdate += clock.restart();

			if (timeSinceLastUpdate > timePerFrame)
			{ // update =====================================================================
				if (closeGame)
					window.close();
				if (resetLevel)
					init();
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
				{
					textureMode = !textureMode;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					levelEditorActive = false;
					mainMenu = true;
					menu.init();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{
					levelEditorActive = false;
					mainMenu = false;
					init();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
				{
					levelEditorActive = true;
					mainMenu = false;
					init();
				}
				if (mainMenu)
				{
					menu.update();
				}
				else if (levelEditorActive)
				{
					editor.update();
				}
				else
				{
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
					}

					velocityY = velocityY + gravity;
					playerShape.move(0, velocityY);

					m_playerS.setPosition(playerShape.getPosition());

					gravity = 0.6;
					for (int row = 0; row < numRows; row++)
					{
						for (int col = 0; col < numCols; col++)
						{
							if (velocityY >= 0)
							{
								if (levelData[row][col] == 1)
								{

									if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
									{
										if (playerShape.getPosition().y < level[row][col].getPosition().y)
										{
											gravity = 0;
											velocityY = 0;
											playerShape.setPosition(playerShape.getPosition().x, level[row][col].getPosition().y);
											playerShape.move(0, -playerShape.getGlobalBounds().height);
											break;
										}
										else
										{
											init();

										}
									}


								}


								if (velocityY < 0)
								{
									if (levelData[row][col] == 1)
									{
										if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
										{
											init();
										}

									}

								}
								if (levelData[row][col] == 2)
								{
									if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
									{
										init();
									}
								}
								if (levelData[row][col] == 3)
								{
									if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
									{
										winText.setFillColor(sf::Color::White);
									}
								}
								if (levelData[row][col] == 4)
								{
									if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
									{
										slowMoTimeLeft = 360;
									}
								}
								if (levelData[row][col] == 5)
								{
									if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
									{
										ExtraJumpTimeLeft = 100;
									}
								}
							}
						}
					}

					if (playerShape.getPosition().y > 600)
					{
						init();
					}
				}

				
				window.clear();
				if (mainMenu)
				{
					menu.render(window);
				}
				else if (levelEditorActive)
				{
					editor.draw(window);
				}
				else
				{
					for (int row = 0; row < numRows; row++)
					{
						for (int col = 0; col < numCols; col++)
						{
							window.draw(level[row][col]);

							if (textureMode)
							{
								//bodies[row][col].setPosition(level[row][col].getPosition());
								//window.draw(bodies[row][col]);
							}
						}
					}
					if (textureMode)
					{
						window.draw(m_playerS);
					}
					else
					{
						window.draw(playerShape);

					}

					window.draw(winText);
				}
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