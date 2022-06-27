#pragma once

#include <glm/glm.hpp>

constexpr static glm::vec3 iHat(1.0f, 0.0f, 0.0f);
constexpr static glm::vec3 jHat(0.0f, 1.0f, 0.0f);
constexpr static glm::vec3 kHat(0.0f, 0.0f, 1.0f);

glm::vec3 vec2to3(glm::vec2 v) noexcept {
	return glm::vec3(v.x, v.y, 0.0f);
}

glm::vec2 vec3to2(glm::vec2 v) noexcept {
	return glm::vec2(v.x, v.y);
}
