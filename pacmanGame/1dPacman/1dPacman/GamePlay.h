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

	void handlePickups();

	//sf::Texture m_sfmlLogoT;
	//std::shared_ptr< sf::Sprite > m_sfmlLogoS;

	std::vector<PickUps>m_pickups;

	std::shared_ptr<sf::RectangleShape> m_backgroundTop;
	std::shared_ptr<sf::RectangleShape> m_backgroundBottom;

	Player m_player;
	Enemy m_enemy;

	Score m_score;

	int m_ghostHuntTime{ 0 };
};

#endif // !GAME_PLAY_H

