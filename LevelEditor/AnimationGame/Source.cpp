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
#include <fstream>

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

static class FileEditing
{
public:
	static void readOutLevel(int t_selectedLevel)
	{
		std::ifstream levels;

		std::string s = "levelData" + std::to_string(t_selectedLevel) + ".txt";


		levels.open(s);

		if (levels.good())
		{
			for (int col = 0; col < numCols; col++)
			{
				for (int row = 0; row < numRows; row++)
				{
					std::string input;
					std::getline(levels, input, ',');

					levelData[row][col] = std::stoi(input);
				}
			}

			levels.close();
		}
		else
		{
			levels.close();
			exit(3);
		}
	}
	static void writeOutLevel(int t_levelNum)
	{
		std::ofstream levels;

		std::string s = "levelData" + std::to_string(t_levelNum) + ".txt";

		levels.open(s);

		if (levels.good())
		{
			for (int col = 0; col < numCols; col++)
			{
				for (int row = 0; row < numRows; row++)
				{
					levels << levelData[row][col] << ",";
				}
				levels << "\n";
			}

			levels.close();

			//writeNewNumToFile(t_levelNum);
		}
		else
		{
			levels.close();
			exit(3);
		}
	}
	static int getLevelAmount()
	{
		std::fstream levels;

		std::string s;

		levels.open("levelData.txt");
		if (levels.good())
		{
			std::getline(levels, s, ';');
			return std::stoi(s);
		}
		else
		{
			levels.close();
			exit(3);
		}
	}
	static void writeNewNumToFile(int t_newNum)
	{
		std::ofstream levels;

		levels.open("levelData.txt");


		if (levels.good())
		{
			levels << std::to_string(t_newNum + 1) << ";";

			levels.close();
		}
		else
		{
			levels.close();
			exit(3);
		}
	}
};


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
			m_buttons[i].setPosition(sf::Vector2f(300.f, 60.f + (160.f * i)));
			m_buttonNames[i].setPosition(sf::Vector2f(350.f, 90.f + (160.f * i)));
			m_buttonNames[i].setFont(m_font);
			m_buttonNames[i].setCharacterSize(42u);
			m_buttonNames[i].setOutlineColor(sf::Color::Black);
			m_buttonNames[i].setOutlineThickness(2u);
		}
		m_buttonNames[0].setString("Play");
		m_buttonNames[1].setString("Edit");
		//m_buttonNames[2].setString("Load");
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
						levelWritten = false;
						resetLevel = true;
					}
					if (i == 1)
					{
						mainMenu = false;
						levelEditorActive = true;
						levelWritten = false;
						resetLevel = true;
					}
					if (i == 3)
					{
						if (!levelWritten)
						{
							levelNum++;
						}
						levelWritten = true;

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
	bool levelWritten = false;
	int levelNum = 0;

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
		tile.loadFromFile("tileNormal.png");
		jump.loadFromFile("jumpTile.png");
		timeTile.loadFromFile("time.png");
		death.loadFromFile("death.png");
		win.loadFromFile("win.png");

		m_maxLevel = FileEditing::getLevelAmount() - 1;

		if (!m_font.loadFromFile("PixelSans.ttf"))
		{
			std::cout << "DIDNT LOAD TEXT\n";
		}
		m_dispString.setFont(m_font);
		m_dispString.setPosition(0.f, 0.f);
		m_dispString.setCharacterSize(12u);
		m_dispString.setString("Right Click - clears tiles\n\nLeft click -  places tiles\n\nA -              moves left\n\nD -              moves right");


		for (int i = 0; i < SAVE_BUTTON_AMT; i++)
		{
			m_saveButtons[i].setSize(sf::Vector2f(100.f, 30.f));
			m_saveButtons[i].setPosition(sf::Vector2f(10.f, 140.f + (i * 60.f)));
			m_saveButtons[i].setFillColor(sf::Color(255,0,0,255));

			m_saveButtonText[i].setFont(m_font);
			m_saveButtonText[i].setPosition(20.f, 150.f + (i * 60.f));
			m_saveButtonText[i].setCharacterSize(12u);
			m_saveButtonText[i].setOutlineColor(sf::Color::Black);
			m_saveButtonText[i].setOutlineThickness(1u);

			m_selectorText[i].setFont(m_font);
			m_selectorText[i].setPosition(150.f, 140.f + (i * 60.f));
			m_selectorText[i].setCharacterSize(22u);
			m_selectorText[i].setOutlineColor(sf::Color::Black);
			m_selectorText[i].setOutlineThickness(1u);
		}

		m_saveButtonText[0].setString("SAVE NEW");
		m_saveButtonText[1].setString("SAVE AS");
		m_saveButtonText[2].setString("LOAD");

		m_selectorText[0].setString("+");
		m_selectorText[1].setString(std::to_string(m_currentLevel));
		m_selectorText[2].setString("-");

		for (int i = 0; i < 2; i++)
		{
			m_selector[i].setSize(sf::Vector2f(30.f, 30.f));
			m_selector[i].setPosition(sf::Vector2f(140.f, 140.f + (i * 120.f)));
			m_selector[i].setFillColor(sf::Color(255, 0, 0, 255));
		}


		m_leftMenu.setSize(sf::Vector2f(200.f, 600.f));
		m_leftMenu.setFillColor(sf::Color(0,0,0,255));
		m_leftMenu.setOutlineColor(sf::Color::White);
		m_leftMenu.setOutlineThickness(1u);

		for (int i = 0; i < BUTTON_AMOUNT; i++)
		{
			m_button[i].setSize(sf::Vector2f(100.f, 30.f));
			m_button[i].setPosition(sf::Vector2f(50.f, 400.f + (i * 40.f)));
			m_buttonOverlay[i].setSize(sf::Vector2f(100.f, 30.f));
			m_buttonOverlay[i].setPosition(sf::Vector2f(50.f, 400.f + (i * 40.f)));

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
		if (t_event.type == sf::Event::MouseButtonPressed)
		{
			pressedAgain = true;
		}
		if (t_event.type == sf::Event::MouseButtonReleased)
		{
			if (pressedAgain)
			{
				pressedAgain = false;

				for (int i = 0; i < 2; i++)
				{
					if (m_selector[i].getGlobalBounds().contains(m_mousePos))
					{
						if (i == 1)
						{
							if (m_currentLevel > 0)
							{
								m_currentLevel--;
							}
						}
						else
						{
							if (m_currentLevel < m_maxLevel)
							{
								m_currentLevel++;
							}
						}
						m_selectorText[1].setString(std::to_string(m_currentLevel));

					}
				}
				for (int i = 0; i < SAVE_BUTTON_AMT; i++)
				{
					if (m_saveButtons[i].getGlobalBounds().contains(m_mousePos))
					{
						if (i == 0)
						{
							FileEditing::writeOutLevel(m_maxLevel + 1);
							FileEditing::writeNewNumToFile(m_maxLevel + 1);

							m_maxLevel = FileEditing::getLevelAmount() - 1;
						}
						else if (i == 1)
						{
							FileEditing::writeOutLevel(m_currentLevel);
						}
						else if (i == 2)
						{
							if(m_maxLevel != -1)
								FileEditing::readOutLevel(m_currentLevel);
						}
					}
				}
			}
		}
	}
	void update() 
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
		{
			textureMode = !textureMode;
		}

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
		for (int i = 0; i < SAVE_BUTTON_AMT; i++)
		{
			if (m_saveButtons[i].getGlobalBounds().contains(m_mousePos))
			{
				m_saveButtons[i].setFillColor(sf::Color(255, 180, 0, 255));
			}
			else
			{
				m_saveButtons[i].setFillColor(sf::Color(255, 0, 0, 255));
			}
		}

		for (int i = 0; i < 2; i++)
		{
			if (m_selector[i].getGlobalBounds().contains(m_mousePos))
			{
				m_selector[i].setFillColor(sf::Color(255, 180, 0, 255));
			}
			else
			{
				m_selector[i].setFillColor(sf::Color(255, 0, 0, 255));
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

				for (int i = 0; i < SAVE_BUTTON_AMT; i++)
				{

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

		float speed = 2.f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			speed = 8.f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			for (int col = 0; col < numCols; col++)
			{
				for (int row = 0; row < numRows; row++)
				{
					levelMoveOffset[row][col].x -= speed;
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			for (int col = 0; col < numCols; col++)
			{
				for (int row = 0; row < numRows; row++)
				{
					levelMoveOffset[row][col].x += speed;
				}
			}
		}
	}
	void draw(sf::RenderWindow& t_window)
	{
		sf::Sprite drawableOverLay;
		for (int col = 0; col < numCols; col++)
		{
			for (int row = 0; row < numRows; row++)
			{
				level[row][col].setOutlineColor(sf::Color::White);
				level[row][col].setOutlineThickness(1u);
				if (levelData[row][col] == 1)
				{
					drawableOverLay.setColor(sf::Color(255, 255, 255, 255));
					drawableOverLay.setTexture(tile);

					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(col * 70, row * 30);
					level[row][col].setFillColor(sf::Color::Red);
				}
				if (levelData[row][col] == 0)
				{
					drawableOverLay.setColor(sf::Color(0,0,0,0));

					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(col * 70, row * 30);
					level[row][col].setFillColor(sf::Color::Black);
				}
				if (levelData[row][col] == 2)
				{
					drawableOverLay.setColor(sf::Color(255, 255, 255, 255));
					drawableOverLay.setTexture(death);

					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(col * 70, row * 30);

					level[row][col].setFillColor(sf::Color::Blue);

				}
				if (levelData[row][col] == 3)
				{
					drawableOverLay.setColor(sf::Color(255, 255, 255, 255));
					drawableOverLay.setTexture(win);
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(col * 70, row * 30);

					level[row][col].setFillColor(sf::Color::Green);
				}

				if (levelData[row][col] == 4)
				{
					drawableOverLay.setColor(sf::Color(255, 255, 255, 255));
					drawableOverLay.setTexture(timeTile);
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(col * 70, row * 30);

					level[row][col].setFillColor(sf::Color::Magenta);

				}
				if (levelData[row][col] == 5)
				{
					drawableOverLay.setColor(sf::Color(255, 255, 255, 255));
					drawableOverLay.setTexture(jump);
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(col * 70, row * 30);

					level[row][col].setFillColor(sf::Color::Yellow);

				}
				level[row][col].move(levelMoveOffset[row][col]);

				if (level[row][col].getGlobalBounds().contains(m_mousePos))
				{
					level[row][col].setFillColor(sf::Color(255,255,255,80));
				}

				drawableOverLay.setPosition(level[row][col].getPosition());

				if (textureMode)
					level[row][col].setFillColor(sf::Color::Black);

				t_window.draw(level[row][col]);
				if(textureMode)
					t_window.draw(drawableOverLay);
			}
		}
		t_window.draw(m_leftMenu);

		for (int i = 0; i < BUTTON_AMOUNT; i++)
		{
			t_window.draw(m_button[i]);
			t_window.draw(m_buttonOverlay[i]);
			if (textureMode)
			{
				sf::Sprite newSprite;
				if(i == 0)
					newSprite.setTexture(tile);
				else if (i == 1)
					newSprite.setTexture(death);
				else if (i == 2)
					newSprite.setTexture(win);
				else if (i == 3)
					newSprite.setTexture(timeTile);
				else if (i == 4)
					newSprite.setTexture(jump);
				newSprite.setPosition(m_button[i].getPosition() + sf::Vector2f(20.f,0.f));

				t_window.draw(newSprite);
			}
		}
		t_window.draw(m_dispString);

		for (auto& i : m_selector)
		{
			t_window.draw(i);
		}

		for (int i = 0; i < SAVE_BUTTON_AMT; i++)
		{
			t_window.draw(m_saveButtons[i]);
			t_window.draw(m_saveButtonText[i]);
			t_window.draw(m_selectorText[i]);
		}
	}
private:
	sf::Texture tile; sf::Texture jump; sf::Texture timeTile; sf::Texture death; sf::Texture win;
	bool textureMode{ false };


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

	static const int SAVE_BUTTON_AMT{ 3 };
	sf::RectangleShape m_saveButtons[SAVE_BUTTON_AMT];
	sf::RectangleShape m_selector[2];
	sf::Text m_saveButtonText[SAVE_BUTTON_AMT];
	sf::Text m_selectorText[SAVE_BUTTON_AMT];

	int m_maxLevel{ 0 };
	int m_currentLevel{ 0 };
	bool pressedAgain{ false };
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

	sf::Sprite bodies[numRows][numCols];
	sf::Texture tile; sf::Texture jump; sf::Texture timeTile; sf::Texture death; sf::Texture win;

	Menu menu;
	LevelEditor editor;

	Game()
	{
		menu.init();
		window.create(sf::VideoMode(800, 600), "Endless Runner Game");

		window.setKeyRepeatEnabled(false);

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

		for (int col = 0; col < numCols; col++)
		{
			for (int row = 0; row < numRows; row++)
			{
				//bodies[row][col].setPosition(col * 70, row * 30);

				if (levelData[row][col] == 0)
				{
					continue;
				}
				else if (levelData[row][col] == 1)
				{
					bodies[row][col].setTexture(tile);
				}
				else if (levelData[row][col] == 2)
				{
					bodies[row][col].setTexture(death);
				}
				else if (levelData[row][col] == 3)
				{
					bodies[row][col].setTexture(win);
				}
				else if (levelData[row][col] == 4)
				{
					bodies[row][col].setTexture(timeTile);
				}
				else if (levelData[row][col] == 5)
				{
					bodies[row][col].setTexture(jump);
				}
			}
		}
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
							if (textureMode)
							{
								bodies[row][col].setPosition(level[row][col].getPosition());
								window.draw(bodies[row][col]);
							}
							else
							{
								window.draw(level[row][col]);
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