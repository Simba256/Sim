#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <vector>
#include <glm/glm.hpp>

typedef std::vector<glm::ivec2> Path;

class PathFinder {
public:
    enum Algorithm {
        A_STAR,
        JOINT_A_STAR,
        CBS_,
        OD_
        // Add more algorithms as needed
    };

    PathFinder();
    std::vector<Path> findPaths(const std::vector<glm::ivec2>& startPoints, 
                                const std::vector<glm::ivec2>& endPoints, 
                                Algorithm algo, int gridWidth, int gridHeight);

private:

    std::vector<Path> AStar(const std::vector<glm::ivec2>& start, const std::vector<glm::ivec2>& end, int gridWidth, int gridHeight);
    std::vector<Path> JointAStar(const std::vector<glm::ivec2>& start, const std::vector<glm::ivec2>& end, int gridWidth, int gridHeight);
    std::vector<Path> CBS(const std::vector<glm::ivec2>& start, const std::vector<glm::ivec2>& end);
    std::vector<Path> OD(const std::vector<glm::ivec2>& start, const std::vector<glm::ivec2>& end);
    // std::vector<std::vector<glm::ivec2>> getNextStates(std::vector<std::vector<bool>> &combs, std::vector<glm::ivec2> &current,std::vector<glm::ivec2> &goal, int gridWidth, int gridHeight);
std::vector<std::vector<glm::ivec2>> getNextStates(
    std::vector<std::vector<bool>> &combs, 
    std::vector<glm::ivec2> &current, 
    const std::vector<glm::ivec2> &goal, // Change here
    int gridWidth, 
    int gridHeight);
    // Function implementation remains the same

    
    int heuristic(const glm::ivec2& start, const glm::ivec2& end);
    int heuristic(const std::vector<glm::ivec2>& start, const std::vector<glm::ivec2>& end);
    // Add more algorithm functions as needed
};

#endif // PATHFINDER_H
