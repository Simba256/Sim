#include "path_finder.h"
#include "directions.h"
// #include "ball_object.h"
#include <iostream>
#include <map>
#include <queue>
#include <set>
// Include necessary headers for your pathfinding algorithms
// For example, you might include headers for A* or Dijkstra's algorithm

PathFinder::PathFinder() {
    // Constructor implementation (if needed)
}
typedef std::vector<glm::ivec2> Path;


std::vector<Path> PathFinder::findPaths(const std::vector<glm::ivec2>& startPoints, 
                                        const std::vector<glm::ivec2>& endPoints, 
                                        Algorithm algo, int gridWidth, int gridHeight) {
    std::vector<Path> result;
    switch (algo) {
        case A_STAR:
            std::cout<<"here";
            result = AStar(startPoints, endPoints, gridWidth, gridHeight);
            break;
        case JOINT_A_STAR:
            result = JointAStar(startPoints, endPoints, gridWidth, gridHeight);
            break;
        case CBS_:
            result = CBS(startPoints, endPoints);
            break;
        // Add more cases for other algorithms as needed
        case OD_:
            result  = OD(startPoints, endPoints);
        default:
            std::cerr << "Unknown algorithm selected!" << std::endl;
            break;
    }

    return result;
}

struct ComparePair {
    bool operator()(const std::pair<int, glm::ivec2>& a, const std::pair<int, glm::ivec2>& b) const {
        return a.first > b.first; // Change to suit your comparison needs
    }
};

struct ComparePairVec {
    bool operator()(const std::pair<int, std::vector<glm::ivec2>>& a, const std::pair<int, std::vector<glm::ivec2>>& b) const {
        return a.first > b.first; // Change to suit your comparison needs
    }
};


struct CompareIvec2 {
    bool operator()(const glm::ivec2& a, const glm::ivec2& b) const {
        if (a.x != b.x) {
            return a.x < b.x;
        } else {
            return a.y < b.y;
        }
    }
};


struct CompareVecIvec2 {
    bool operator()(const std::vector<glm::ivec2>& a, const std::vector<glm::ivec2>& b) const {
        for(int i=0;i<a.size();i++){
            if(a[i].x != b[i].x){
                return a[i].x < b[i].x;
            }else{
                if(a[i].y != b[i].y){
                    return a[i].y < b[i].y;
                }
            }
        }
        return false;
    }
};

std::vector<Path> PathFinder::AStar(const std::vector<glm::ivec2>& start, const std::vector<glm::ivec2>& end, int gridWidth, int gridHeight) {
    int n = start.size();
    std::vector<Path> Paths(n);
    for(int i=0;i<n;i++){
        Path path;
        glm::ivec2 startPoint = start[i];
        glm::ivec2 endPoint = end[i];
        
        std::map<glm::ivec2, glm::ivec2, CompareIvec2> cameFrom;
        std::map<glm::ivec2, int, CompareIvec2> costSoFar;

        // create a priority queue
        std::priority_queue<std::pair<int, glm::ivec2>, std::vector<std::pair<int, glm::ivec2>>, ComparePair> frontier;
        
        // push the start node into the queue
        frontier.push(std::make_pair(0, startPoint));
        std::cout<<"1";
        cameFrom[startPoint] = startPoint;
        costSoFar[startPoint] = 0;
        std::cout<<"2";
        while (!frontier.empty()) {
            glm::ivec2 current = frontier.top().second;
            frontier.pop();
            std::cout<<"3";
            if (current == endPoint) {
                break;
            }std::cout<<"4";

            for (int i = 0; i < 4; ++i) {
                glm::ivec2 next = current + DIRECTIONS[i];
                if (next.x < 0 || next.x >= gridWidth || next.y < 0 || next.y >= gridHeight) {
                    continue;
                }
                int newCost = costSoFar[current] + 1;
                if (costSoFar.find(next) == costSoFar.end() || newCost < costSoFar[next]) {
                    costSoFar[next] = newCost;
                    int priority = newCost + heuristic(next, endPoint);
                    frontier.push(std::make_pair(priority, next));
                    cameFrom[next] = current;
                }
            }
        }std::cout<<"5";
        // Reconstruct the path
        glm::ivec2 current = endPoint;
        while (current != startPoint) {
            std::cout<<current.x<<" "<<current.y<<std::endl;
            Paths[i].push_back(current);
            std::cout<<"7\n";
            current = cameFrom[current];
            std::cout<<"8\n";
        }std::cout<<"6";
    }

    // for(auto x:Paths){
    //     for(auto y:x){
    //         std::cout<<y.x<<" "<<y.y<<std::endl;
    //     }
    // }

    return Paths;
}

std::vector<std::vector<bool>> BinaryCombinations(int n){
    std::vector<std::vector<bool>> result;
    for(int i=0;i<(1<<n);i++){
        std::vector<bool> temp;
        for(int j=0;j<n;j++){
            temp.push_back(i&(1<<j));
        }
        result.push_back(temp);
    }
    return result;

} 

int PathFinder::heuristic(const std::vector<glm::ivec2>& start, const std::vector<glm::ivec2>& end) {
    int n = start.size();
    int result = 0;
    for(int i=0;i<n;i++){
        result += abs(start[i].x - end[i].x) + abs(start[i].y - end[i].y);
    }
    return result;
}

std::vector<std::vector<glm::ivec2>> checkConstraints(std::vector<glm::ivec2> &current, std::vector<std::vector<glm::ivec2>> &nexts){
    std::vector<std::vector<glm::ivec2>> result;
    int n = current.size();
    int m = nexts.size();
    for(int i=0;i<m;i++){
        int flag = 0;
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                if(j == k) continue;
                if(nexts[i][j] == nexts[i][k]){
                    flag = 1;
                    break;
                }
            }if(flag) break;
        }

        for(int j=0;j<n;j++){
            if(flag) break;
            for(int k=0;k<n;k++){
                if(j == k) continue;
                if(nexts[i][j] == current[k] && nexts[i][k] == current[j]){
                    flag = 1;
                    break;
                }
            }
        }

        if(!flag){
            result.push_back(nexts[i]);
        }
    }
    return result;
}


// make get next states FUNCTION
std::vector<std::vector<glm::ivec2>> PathFinder::getNextStates(
    std::vector<std::vector<bool>> &combs, 
    std::vector<glm::ivec2> &current, 
    const std::vector<glm::ivec2> &goal, // Change here
    int gridWidth, 
    int gridHeight) {
    // Function implementation remains the same

    int n = current.size();
    std::vector<std::vector<glm::ivec2>> nexts;
    for(auto comb:combs){
        std::vector<std::vector<glm::ivec2>> sub_nexts;
        sub_nexts.push_back(current);
        for(int i=0;i<n;i++){
            if(current[i]==goal[i]) continue;
            if(comb[i]){
                std::vector<std::vector<glm::ivec2>> new_sub_nexts;
                for(auto sub_next:sub_nexts){
                    for(int j=0;j<4;j++){
                        sub_next[i] = sub_next[i] + DIRECTIONS[j];
                        if(sub_next[i].x < 0 || sub_next[i].x >= gridWidth || sub_next[i].y < 0 || sub_next[i].y >= gridHeight){
                            sub_next[i] = sub_next[i] - DIRECTIONS[j];
                            continue;
                        }
                        new_sub_nexts.push_back(sub_next);
                        sub_next[i] = sub_next[i] - DIRECTIONS[j];
                    }
                }sub_nexts = new_sub_nexts;
            }
        }nexts.insert(nexts.end(), sub_nexts.begin(), sub_nexts.end());
    }
    return checkConstraints(current,nexts);
}

std::vector<Path> PathFinder::JointAStar(const std::vector<glm::ivec2>& start, const std::vector<glm::ivec2>& end, int gridWidth, int gridHeight) {
    int n = start.size();
    std::vector<Path> path(n);
    // positions of the agents
    std::vector<glm::ivec2> currentPositions = start;
    std::vector<std::vector<bool>> combs = BinaryCombinations(n);
    // for(auto x:combs){
    //     for(auto y:x){
    //         if(y) std::cout<<"1";
    //         else std::cout<<"0";
    //     }std::cout<<std::endl;
    // }

    // make a priority queue of all the possible combinations of the agents
    std::priority_queue<std::pair<int, std::vector<glm::ivec2>>, std::vector<std::pair<int, std::vector<glm::ivec2>>>, ComparePairVec> frontier;
    frontier.push(std::make_pair(0, currentPositions));
    std::map<std::vector<glm::ivec2>, std::vector<glm::ivec2>, CompareVecIvec2> cameFrom;
    std::map<std::vector<glm::ivec2>, int, CompareVecIvec2> costSoFar;
    cameFrom[currentPositions] = currentPositions;

    
    costSoFar[currentPositions] = 0;
    int iters = 0;
    std::set<std::vector<glm::ivec2>, CompareVecIvec2> visited;
    int waste=0;
    while(!frontier.empty()){
        std::vector<glm::ivec2> current = frontier.top().second;
        iters++;
        // std::cout<<"Current:";
        // for(auto x:current){
        //     std::cout<<x.x<<","<<x.y<<" ";
        // }std::cout<<std::endl;
        frontier.pop();
        if(visited.find(current) != visited.end()){
            waste++;
        }
        visited.insert(current);
        if(current == end){
            std::cout<<"END reACHED\n";
            break;
        }
        for(int i=0;i<combs.size();i++){
            int flag = 0;
            std::vector<std::vector<glm::ivec2>> nexts = getNextStates(combs,current, end, gridWidth, gridHeight); // = current;
            for(auto &next:nexts){
                int newCost = costSoFar[current] + n;
                if(costSoFar.find(next) == costSoFar.end() || newCost < costSoFar[next]){
                    costSoFar[next] = newCost;
                    int priority = newCost + heuristic(next, end);
                    frontier.push(std::make_pair(priority, next));
                    // std::cout<<"Pushed:\n";
                    // for(auto x:next){
                    //     std::cout<<x.x<<","<<x.y<<" ";
                    // }std::cout<<std::endl;
                    cameFrom[next] = current;
                }
            }
        }//std::cout<<"1\n";
    }//std::cout<<"2\n";
    std::cout<<"iters:"<<iters<<std::endl;
    std::cout<<"waste:"<<waste<<std::endl;
    // regenerate the path
    std::vector<std::vector<glm::ivec2>> MegaPath;
    std::vector<glm::ivec2> current = end;
    std::cout<<"Start:";
    for(auto x:start){
        std::cout<<x.x<<","<<x.y<<" ";
    }std::cout<<std::endl;
    std::cout<<"End:";
    for(auto x:end){
        std::cout<<x.x<<","<<x.y<<" ";
    }std::cout<<std::endl;
    // for(auto x:cameFrom){
    //     for(auto y:x.first){
    //         std::cout<<y.x<<","<<y.y<<" ";
    //     }std::cout<<"->";
    //     for(auto y:x.second){
    //         std::cout<<y.x<<","<<y.y<<" ";
    //     }
    //     std::cout<<std::endl;
    // }
    while(current != currentPositions){
        // for(int i=0;i<n;i++){
        //     std::cout<<"curr:"<<i<<" "<<current[i].x<<" "<<current[i].y<<std::endl;
        //     std::cout<<"start:"<<i<<" "<<currentPositions[i].x<<" "<<currentPositions[i].y<<std::endl;

        // }
        MegaPath.push_back(current);
        current = cameFrom[current];
    }//std::cout<<"3\n";
    // reverse mega path
    int ss = MegaPath.size();
    for(int i=0;i<ss/2;i++){
        std::vector<glm::ivec2> temp = MegaPath[i];
        MegaPath[i] = MegaPath[ss-i-1];
        MegaPath[ss-i-1] = temp;
    }//std::cout<<"4\n";
    for(auto x:MegaPath){
        for(int i=0;i<n;i++){
            path[i].push_back(x[i]);
        }
    }//std::cout<<"3\n";
    return path;
}

std::vector<Path> PathFinder::CBS(const std::vector<glm::ivec2>& start, const std::vector<glm::ivec2>& end) {
    std::vector<Path> path;
    // Implement Dijkstra's algorithm here
    // Populate the 'path' vector with the resulting path from start to end
    return path;
}

std::vector<Path> PathFinder::OD(const std::vector<glm::ivec2>& start, const std::vector<glm::ivec2>& end) {
    std::vector<Path> path;
    // Implement Dijkstra's algorithm here
    // Populate the 'path' vector with the resulting path from start to end
    return path;
}

int PathFinder::heuristic(const glm::ivec2& start, const glm::ivec2& end) {
    return abs(start.x - end.x) + abs(start.y - end.y);
}
