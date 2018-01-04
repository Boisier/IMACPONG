#ifndef PACMAN_HPP
#define PACMAN_HPP

#include "DynamicItem.hpp"

class Pacman: public DynamicItem {
private:
	int m_lives;
	bool m_isSuper;

public:
	//CONSTRUCTOR
	Pacman(glm::vec2 position, std::string name = "player", uint score = 0, enum ITEM_SYNTAX type = PACMAN, int lives = 3, bool isSuper = false):
		DynamicItem(position, name, score, type),
		m_lives(lives),
		m_isSuper(isSuper)
	{};
	//DESTRUCTOR
	~Pacman() = default;
	
	//GETTERS
	int getLives() const;
	bool getIsSuper() const;

	//SETTERS
	void updateLives(const int live);
	void setIsSuper(const bool isSuper);

	//METHODS
};

#endif /* PACMAN_HPP */
