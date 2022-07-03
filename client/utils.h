#pragma once

#include <random>
#include <glm/glm.hpp>

constexpr static glm::vec3 iHat(1.0f, 0.0f, 0.0f);
constexpr static glm::vec3 jHat(0.0f, 1.0f, 0.0f);
constexpr static glm::vec3 kHat(0.0f, 0.0f, 1.0f);

inline glm::vec3 vec2to3(glm::vec2 v) noexcept {
	return glm::vec3(v.x, v.y, 0.0f);
}

inline glm::vec2 vec3to2(glm::vec2 v) noexcept {
	return glm::vec2(v.x, v.y);
}

inline long long int currTimeLL(void) {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

inline long long int genRandLL(void) {
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<long long int> distribution;
	return distribution(gen);
}

