#include "ball_object.h"
#include <iostream>

const float BallObject::MoveDelay = 1.1f;  // Set the fixed delay

BallObject::BallObject()
    : GameObject(), Radius(12.5f), Stuck(true), Sticky(false), PassThrough(false), CurrentIndex(0), Timer(0.0f) {
    this->Velocity = glm::vec2(100.0f, 100.0f);
}

BallObject::BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite, Path path, GameLevel level)
    : GameObject(pos, glm::vec2(radius * 2.0f, radius * 2.0f), sprite, glm::vec3(1.0f), velocity), Radius(radius), Stuck(true), Sticky(false), PassThrough(false), PathCoordinates(path), CurrentIndex(0), Timer(0.0f) {
        brickHeight = level.HeightOfBrick;
        brickWidth = level.WidthOfBrick;
}

glm::vec2 BallObject::GridToScreen(glm::ivec2 gridPos) {

    return glm::vec2(gridPos.x * brickWidth, gridPos.y * brickHeight);
}

glm::vec2 BallObject::Move(float dt, unsigned int window_width, unsigned int window_height)
{
    // Increment the timer by the delta time
    this->Timer += dt;

    // Move the ball only if the timer exceeds the move delay and there is a path to follow
    if (this->Timer >= this->MoveDelay && this->CurrentIndex < this->PathCoordinates.size()) {
        this->CurrentIndex++; // Move to the next grid position
        this->Timer = 0.0f; // Reset the timer
    }

    // Calculate the percentage of completion between the current and next grid positions
    float completion = this->Timer / this->MoveDelay;

    
    if (completion > 1.0f) {
        completion = 1.0f; // Ensure completion is capped at 1.0
    }

    // Interpolate the ball's position between the current and next grid positions
    glm::vec2 currentPos = GridToScreen(this->PathCoordinates[this->CurrentIndex - 1]);
    glm::vec2 nextPos = GridToScreen(this->PathCoordinates[this->CurrentIndex]);
    this->Position = currentPos + (nextPos - currentPos) * completion;

    return this->Position;
}
