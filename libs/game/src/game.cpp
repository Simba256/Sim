#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "game_object.h"
#include "ball_object.h"
#include "random.h"
#include "path_finder.h"
#include <vector>
#include <iostream>

// Game-related State data
SpriteRenderer    *Renderer;
std::vector<BallObject*> Balls;


Game::Game(unsigned int width, unsigned int height) 
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{ 

}

Game::~Game()
{
    delete Renderer;
    // Delete each BallObject in the vector
    for (BallObject* ball : Balls)
    {
        delete ball;
    }
    // Clear the vector to remove the pointers
    Balls.clear();

}

void Game::Init(int numBalls)
{
    // load shaders
    ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), 
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // load textures
    ResourceManager::LoadTexture("textures/background.jpg", false, "background");
    ResourceManager::LoadTexture("textures/awesomeface.png", true, "face");
    ResourceManager::LoadTexture("textures/block.png", false, "block");
    ResourceManager::LoadTexture("textures/block_solid.png", false, "block_solid");
    // set render-specific controls
    Shader spriteShader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(spriteShader);
    // load levels
    GameLevel one; one.Load("levels/one.lvl", this->Width, this->Height);
    GameLevel two; two.Load("levels/two.lvl", this->Width, this->Height);
    GameLevel three; three.Load("levels/three.lvl", this->Width, this->Height);
    GameLevel four; four.Load("levels/four.lvl", this->Width, this->Height);
    this->Levels.push_back(one);
    this->Levels.push_back(two);
    this->Levels.push_back(three);
    this->Levels.push_back(four);
    this->Level = 0;

    gridWidth = this->Levels[0].BricksWidth;
    gridHeight = this->Levels[0].BricksHeight;
    brickWidth = this->Levels[0].WidthOfBrick;
    brickHeight = this->Levels[0].HeightOfBrick;

    // this->MakeBall();
    this->MakeBalls(numBalls);

}

void Game::MakeBalls(int count) {
    
    // std::cout<<"Grid Width: "<<gridWidth<<" Grid Height: "<<gridHeight<<"\n";

    // generate random start points for balls
    RandomNumberGenerator rng;
    // Random grid coordinates
    int randomX; 
    int randomY; 

    std::vector<glm::ivec2> startPoints;
    std::vector<glm::ivec2> endPoints;
    // std::cout<<"Start Points: \n";
    for(int i=0;i<count;i++){
        randomX = rng.generateInt(0,gridWidth-1);
        randomY = rng.generateInt(0,gridHeight-1);
        startPoints.push_back(glm::ivec2(randomX, randomY));
        // std::cout<<randomX<<" "<<randomY<<std::endl;
    }//std::cout<<"End Points: \n";
    for(int i=0;i<count;i++){
        randomX = rng.generateInt(0,gridWidth-1);
        randomY = rng.generateInt(0,gridHeight-1);
        endPoints.push_back(glm::ivec2(randomX, randomY));
        // std::cout<<randomX<<" "<<randomY<<std::endl;
    }
 
    

    PathFinder pathFinder;
    // get Paths
    std::vector<Path> paths = pathFinder.findPaths(startPoints, endPoints, PathFinder::Algorithm::JOINT_A_STAR, gridWidth, gridHeight);
    
    // // print paths
    // for(int i=0;i<count;i++){
    //     std::cout<<"Path "<<i<<":\n";
    //     for (const auto& coordinate : paths[i]) {
    //         std::cout << "Screen Position: (" << coordinate.x << ", " << coordinate.y << ")\n";
    //     }
    // }

    for(int i=0;i<count;i++){
        glm::vec2 screenPos = GridToScreen(startPoints[i], brickWidth, brickHeight);
        Balls.push_back(new BallObject(screenPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("face"), paths[i], Levels[0]));
    }
}







void Game::MakeBall() {


    RandomNumberGenerator rng;
    // Random grid coordinates
    int randomX = rng.generateInt(0,gridWidth-1);
    int randomY = rng.generateInt(0,gridHeight-1);
    glm::ivec2 startPoint(randomX, randomY);


    randomX = rng.generateInt(0,gridWidth-1);
    randomY = rng.generateInt(0,gridHeight-1);
    glm::ivec2 endPoint(randomX, randomY);

    // Create a path (example: straight line for simplicity)
    Path path;
    int n = 10;
    for (int i = 0; i < n+1; ++i) {
        path.push_back(glm::ivec2(startPoint[0] + i*(1.0*endPoint[0]-1.0*startPoint[0])/n, startPoint[1] + i*(1.0*endPoint[1]-1.0*startPoint[1])/n));
    }
    

    // // Print the path coordinates
    // std::cout << "Path Coordinates:\n";
    // for (const auto& coordinate : path) {
    //     std::cout << "Screen Position: (" << coordinate.x << ", " << coordinate.y << ")\n";
    // }


    // // Print the path coordinates
    // std::cout << "Path Coordinates:\n";
    // for (const auto& coordinate : path) {
    //     glm::vec2 screenPos = GridToScreen(coordinate, brickWidth, brickHeight);
    //     std::cout << "Screen Position: (" << screenPos.x << ", " << screenPos.y << ")\n";
    // }

    glm::vec2 screenPos = GridToScreen(startPoint, brickWidth, brickHeight);

    Balls.push_back(new BallObject(screenPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("face"), path, Levels[0]));
}

glm::vec2 Game::GridToScreen(glm::ivec2 gridPos, float brickWidth, float brickHeight) {
    float screenX = gridPos.x * brickWidth;
    float screenY = gridPos.y * brickHeight;
    return glm::vec2(screenX, screenY);
}



void Game::Update(float dt)
{
    for(BallObject* Ball:Balls){
        // update objects
        Ball->Move(dt, this->Width, this->Height);
        // check for collisions
    }
}

void Game::ProcessInput(float dt)
{
    if (this->State == GAME_ACTIVE)
    {
        
        if (this->Keys[GLFW_KEY_SPACE])
        {
            
            this->MakeBall();
        }
    }
}


void Game::Render()
{
    if(this->State == GAME_ACTIVE)
    {
        // draw background
        Texture2D backgroundTexture = ResourceManager::GetTexture("background");
        Renderer->DrawSprite(backgroundTexture, glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);
        // draw level
        this->Levels[this->Level].Draw(*Renderer);
        for(BallObject* Ball:Balls){
            // draw ball
            Ball->Draw(*Renderer);
        }
    }
}









// calculates which direction a vector is facing (N,E,S or W)
Direction VectorDirection(glm::vec2 target)
{
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),	// up
        glm::vec2(1.0f, 0.0f),	// right
        glm::vec2(0.0f, -1.0f),	// down
        glm::vec2(-1.0f, 0.0f)	// left
    };
    float max = 0.0f;
    unsigned int best_match = -1;
    for (unsigned int i = 0; i < 4; i++)
    {
        float dot_product = glm::dot(glm::normalize(target), compass[i]);
        if (dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return (Direction)best_match;
};
