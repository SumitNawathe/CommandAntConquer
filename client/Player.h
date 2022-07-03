#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <map>
#include <optional>

#include "forward_declarations.h"
#include "Ant.h"
#include "Nest.h"

class Player {
public:
	Player(glm::vec2 pos);

	glm::vec2 getPos(void) { return pos; }
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

	class InputDirection {
	private:
		typedef typename std::optional<bool> tribool;
		tribool vert;
		tribool horiz;
	
	public:
		InputDirection() : vert(), horiz() {}
		InputDirection(std::optional<bool> v, std::optional<bool> h) : vert(v), horiz(h) {}
		operator bool() const { return vert || horiz; }
		bool operator==(InputDirection id) const { return (vert == id.vert) && (horiz == id.horiz); }
		bool operator!=(InputDirection id) const { return !operator==(id); }

		inline void setUp(void) { vert = tribool(true); }
		inline bool isUp(void) const { return vert == tribool(true); }
		inline void setDown(void) { vert = tribool(false); }
		inline bool isDown(void) const { return vert == tribool(false); }
		inline void setNeutVert(void) { vert = std::nullopt; }
		inline bool isNeutVert(void) const { return vert == std::nullopt; }

		inline void setRight(void) { horiz = tribool(true); }
		inline bool isRight(void) const { return horiz == tribool(true); }
		inline void setLeft(void) { horiz = tribool(false); }
		inline bool isLeft(void) const { return horiz == tribool(false); }
		inline void setNeutHoriz(void) { horiz = std::nullopt; }
		inline bool isNeutHoriz(void) const { return horiz == std::nullopt; }
	} inputDirection;

private:
	glm::vec2 queenPos;
	Nest* nest;
	glm::vec2 pos;
	glm::vec2 vel;
	float speed;
};

