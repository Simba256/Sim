#ifndef DIRECTIONS_H
#define DIRECTIONS_H

#include <glm/glm.hpp>

constexpr glm::ivec2 DIRECTION_UP(0, 1);
constexpr glm::ivec2 DIRECTION_DOWN(0, -1);
constexpr glm::ivec2 DIRECTION_RIGHT(1, 0);
constexpr glm::ivec2 DIRECTION_LEFT(-1, 0);

constexpr glm::ivec2 DIRECTIONS[] = { DIRECTION_UP, DIRECTION_DOWN, DIRECTION_RIGHT, DIRECTION_LEFT };

#endif // DIRECTIONS_H
