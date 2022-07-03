#include "Player.h"

#include <iostream>
#include <algorithm>
#include <numbers>

#include "globals.h"

Player::Player(glm::vec2 pos)
{
	nest = new Nest(pos, *this);
}

void Player::SentryPosts::remove(Ant::ID_T antID) {
	// find where ant is located
	auto pos = std::find(sentries.begin(), sentries.end(), antID);
	if (pos == sentries.end()) {
		if (DEBUG) std::cout << "[Player::SentryPosts] Attempting to remove ant that is not a sentry" << std::endl;
		return;
	}

	// swap this ant with the last (outermost) one, then remove
	std::iter_swap(pos, sentries.end() - 1);
	sentries.pop_back();

	// clear cache
	// TODO: only need to clear elements after where pos was (iterator
	//		now invalid), can optimize
	relPosCache.clear();
}

glm::vec2 Player::SentryPosts::getRelPos(Ant::ID_T antID, bool cache) {
	// if desired, get from cache
	if (cache)
		if (auto entry = relPosCache.find(antID); entry != relPosCache.end())
			return entry->second;
	if (DEBUG) std::cout << "[Player::SentryPosts] Rel pos for ant id=" << antID << " not cached, calculating\n";

	// find ant in list
	auto pos = std::find(sentries.begin(), sentries.end(), antID);
	if (pos == sentries.end()) {
		if (DEBUG) std::cout << "[Player::SentryPosts] Attempting to get relative pos of ant that is not a sentry" << std::endl;
		return glm::vec2(0.0f, 0.0f);
	}
	int n = pos - sentries.begin();
	if (DEBUG) std::cout << "n = " << n << "\n";

	/* Layer/Ring System:
	* Each layer consists of 2 rings, a normal and alternate, which are offset of each other
	* Layers are indexed from 0. In layer i, the rings have: min 6(i+1), max 10(i+1)
	*/

	int layerIndex = 0, ringIndex = 0, ringSize = 0;
	bool alternate = false;
	while (true) {
		if (n <= 10 * (layerIndex + 1)) {
			// found it
			ringIndex = n;
			ringSize = std::max(6 * (layerIndex + 1), std::min(10 * (layerIndex + 1), static_cast<int>(sentries.end() - pos)));
			break;
		}

		// next ring/layer
		n -= 10 * (layerIndex + 1);
		if (alternate) {
			alternate = false;
			layerIndex += 1;
			ringIndex = 0;
		}
		else alternate = true;
	}
	if (DEBUG) {
		std::cout << "layerIndex = " << layerIndex << "\n";
		std::cout << "ringIndex = " << ringIndex << "\n";
		std::cout << "ringSize = " << ringSize << "\n";
		std::cout << "alternate = " << alternate << "\n";
	}

	// calculate relative coordinates
	float radius = 0.15 * (layerIndex + 1) + 0.06 * alternate;
	double angle = (double)ringIndex / (double)ringSize * 2.0f * std::numbers::pi;
	if (alternate) angle += std::numbers::pi / (double)ringSize;
	float dx = radius * glm::cos(angle);
	float dy = radius * glm::sin(angle);
	if (DEBUG) {
		std::cout << "radius = " << radius << "\n";
		std::cout << "angle = " << angle << "\n";
	}

	// possibly cache
	glm::vec2 result(dx, dy);
	if (cache) relPosCache[antID] = result;
	if (DEBUG) std::cout << "result = (" << result.x << ", " << result.y << ")" << std::endl;
	return result;
}

std::tuple<glm::vec2, int, int> Player::drawSettings() const {
	return std::make_tuple(pos, 0, 0);
}

void Player::update(float dt) {
	if (!inputDirection) return;
	glm::vec2 d(
		inputDirection.isRight() ? 1.0f : inputDirection.isLeft() ? -1.0f : 0.0f,
		inputDirection.isUp() ? 1.0f : inputDirection.isDown() ? -1.0f : 0.0f
	);
	pos += glm::normalize(d) * dt * 0.20f;
}

