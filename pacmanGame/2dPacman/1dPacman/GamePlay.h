#ifndef GAME_PLAY_H
#define GAME_PLAY_H

#include"GameMode.h"
#include"PickUps.h"
#include"Player.h"
#include"Enemy.h"
#include"Score.h"
#include<vector>

class GamePlay : public GameMode
{
public:
	GamePlay();  // standard constructor
	~GamePlay(); // standard deconstructor (shouldnt be used)

	void resetLevel()override;                         // used to reset the level for each session instead of reconstructing
	void events(sf::Event& t_event)override;           // used to handle all new events outside key presses
	void update(sf::Time t_deltaTime)override;         // all update events

private:
	void processKeys(sf::Event& t_event)override;

	void handlePickups(std::vector<PickUps>& t_pickup);

	//sf::Texture m_sfmlLogoT;
	//std::shared_ptr< sf::Sprite > m_sfmlLogoS;

	std::vector<PickUps>m_pickupsTop;
	std::vector<PickUps>m_pickupsRight;
	std::vector<PickUps>m_pickupsLeft;
	std::vector<PickUps>m_pickupsBottom;


	std::shared_ptr<sf::RectangleShape> m_backgroundTop;

	std::shared_ptr<sf::RectangleShape> m_backgroundTop1;
	std::shared_ptr<sf::RectangleShape> m_backgroundTop2;
	std::shared_ptr<sf::RectangleShape> m_backgroundBottom;
	std::shared_ptr<sf::RectangleShape> m_backgroundBottom2;
	std::shared_ptr<sf::RectangleShape> m_backgroundLeft1;
	std::shared_ptr<sf::RectangleShape> m_backgroundLeft2;
	std::shared_ptr<sf::RectangleShape> m_backgroundRight1;
	std::shared_ptr<sf::RectangleShape> m_backgroundRight2;
	std::shared_ptr<sf::RectangleShape> m_backgroundMidLeft;
	std::shared_ptr<sf::RectangleShape> m_backgroundMidRight;


	Player m_player;
	Enemy m_enemy;

	Score m_score;

	int m_ghostHuntTime{ 0 };

	bool m_canChangeDirection = true;

	std::shared_ptr< sf::RectangleShape> m_rightBox;
	std::shared_ptr< sf::RectangleShape> m_leftBox;
};

#endif // !GAME_PLAY_H

