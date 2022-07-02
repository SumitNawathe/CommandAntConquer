#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <map>

#include "forward_declarations.h"
#include "Ant.h"
#include "Nest.h"

class Player {
public:
	Player(glm::vec2 pos);

	Nest* getNest() const { return nest; }
	std::vector<Ant> ants;
	void update(float dt);

	class SentryPosts {
	public:
		void add(Ant::ID_T antID) { sentries.push_back(antID); }
		void remove(Ant::ID_T antID);
		glm::vec2 getRelPos(Ant::ID_T antID, bool cache = true);

	private:
		std::vector<Ant::ID_T> sentries;
		std::map<Ant::ID_T, glm::vec2> relPosCache;
	} sentryPosts;

	std::tuple<glm::vec2, int, int> drawSettings() const;

private:
	glm::vec2 queenPos;
	Nest* nest;
	glm::vec2 pos;
	glm::vec2 vel;
	float speed;
};

