#ifndef AGENT_NULL_HPP
#define AGENT_NULL_HPP

#include "agent.hpp"

class AgentNull : Agent {
public: 
    virtual size_t getMove(Board board);
};

#endif // AGENT_NULL_HPP
