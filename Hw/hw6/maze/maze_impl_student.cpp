#include "maze.h"
#include "bfs.h"
#include "dfs.h"

/** \brief Return the valid next states from a given state */
std::vector<State> ProblemDefinition::validStates(const State &state) const
{
    // HINT: use isStateValid()
    // --- Your code here
    std::vector<State> res;

    std::vector<std::vector<int>> moves;

    if(this->allow_diagonal_){
        moves = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}, {-1, 1}, {1, 1}, {1, -1}, {-1, -1}};
    }
    else{
       moves = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
    }
    
    for(auto const& move : moves){
        State next_state = State(state.x + move[0], state.y + move[1]);

        if(isStateValid(next_state)){
            res.push_back(next_state);
        }
    }

    return res;
    // ---
}

/** \brief Given a node, extract the path from it to the root */
void TreeSearch::extractPath(NodePtr node)
{
    // --- Your code here
    while(node){
        path_.push_back(node->state);
        node = node->parent;
    }

    std::reverse(path_.begin(), path_.end());

    // ---
}

/** \brief Solve the planning problem. Override TreeSearch::solve() */
bool BFS::solve()
{
    // check start and goal are valid
    if (!pdef_.isStateValid(pdef_.startState()) ||
        !pdef_.isStateValid(pdef_.goalState()))
    {

        return false;
    }

    // if start and goal coincide, terminate
    auto start = pdef_.startState();
    if (pdef_.isGoal(start))
    {
        std::cout << "Start and goal are equal\n";
        return true;
    }

    NodePtr solution;
    // --- Your code here
    State goal = pdef_.goalState();

    NodePtr startNode = std::make_shared<Node>();
    startNode->state = start;

    BFS::addNode(startNode);

    while(!q.empty()){

        NodePtr cur_node = q.front();
        q.pop();
        
        if(isVisited(cur_node)) continue;
        visited_.push_back(cur_node->state);

        // Goal found
        if(pdef_.isGoal(cur_node->state)){
            solution = cur_node;
            break;
        }

        // Expand neighbors of current node
        for(auto const& next_state : pdef_.validStates(cur_node->state)){
            NodePtr next_node = std::make_shared<Node>();
            next_node->state = next_state;
            next_node->parent = cur_node;

            // Have not visited yet, push to queue
            if(!TreeSearch::isVisited(next_node)){
                BFS::addNode(next_node);
            }
        }
    }
    
    if(solution == nullptr) return false;
    // ---

    // get the path from last node to root
    extractPath(solution);

    return true;
}

/** \brief add node to the tree */
bool BFS::addNode(const NodePtr &node)
{
    // --- Your code here
	if(isVisited(node)) return false;
	
    BFS::q.push(node);
    return true;

    // ---
}

/** \brief Solve the planning problem. Override TreeSearch::solve() */
bool DFS::solve()
{
    // check start and goal are valid
    if (!pdef_.isStateValid(pdef_.startState()) ||
        !pdef_.isStateValid(pdef_.goalState()))
    {
        return false;
    }

    // if start and goal coincide, terminate
    auto start = pdef_.startState();
    if (pdef_.isGoal(start))
    {
        std::cout << "Start and goal are equal\n";
        return true;
    }

    NodePtr solution;
    // --- Your code here
    State goal = pdef_.goalState();

    NodePtr startNode = std::make_shared<Node>();
    startNode->state = start;

    DFS::addNode(startNode);

    while(!DFS::stk.empty()){

        NodePtr cur_node = DFS::stk.top();
        DFS::stk.pop();
        visited_.push_back(cur_node->state);

        // Goal found
        if(pdef_.isGoal(cur_node->state)){
            solution = cur_node;
            break;
        }

        // Expand neighbors of current nodes
        for(auto const& next_state : pdef_.validStates(cur_node->state)){
            NodePtr next_node = std::make_shared<Node>();
            next_node->state = next_state;
            next_node->parent = cur_node;
            // Have not visited yet, push to stack
            if(!TreeSearch::isVisited(next_node)){
                DFS::addNode(next_node);
            }
            else{
                std::cout << "Node visited" << std::endl;
            }
        }
    }

    if(solution == nullptr) return false;
    // ---

    // get the path from last node to root
    extractPath(solution);

    return true;
}

/** \brief add node to the tree */
bool DFS::addNode(const NodePtr &node)
{
    // --- Your code here
	if(isVisited(node)) return false;
	
    DFS::stk.push(node);
    return true;

    // ---
}
