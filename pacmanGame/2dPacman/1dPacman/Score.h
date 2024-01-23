#ifndef SCORE_H
#define SCORE_H

#include<SFML/Graphics.hpp>

class Score
{
public:
	void init();

	void increaseScore(int t_increase);
private:
	sf::Font m_font;
	std::shared_ptr< sf::Text > m_score;

	int m_scoreVal{ 0 };
};

#endif // !SCORE_H
