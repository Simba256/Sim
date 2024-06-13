#ifndef BALLOBJECT_H
#define BALLOBJECT_H

#include "game_object.h"
#include <vector>
#include <glm/glm.hpp>
#include <game_level.h>

// Type definition for the path
typedef std::vector<glm::ivec2> Path;

class BallObject : public GameObject
{
public:
    float Radius;
    bool Stuck;
    bool Sticky, PassThrough;
    static const float MoveDelay; // Fixed delay between moves
    float brickWidth, brickHeight;

    Path PathCoordinates;
    size_t CurrentIndex;
    float Timer;

    BallObject();
    BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite, Path path, GameLevel level);

    glm::vec2 Move(float dt, unsigned int window_width, unsigned int window_height);

private:
    glm::vec2 GridToScreen(glm::ivec2 gridPos);
};

#endif
