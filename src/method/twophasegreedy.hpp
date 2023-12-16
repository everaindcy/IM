#pragma once

#include "greedy.hpp"

#define PHASE1LEN 100
#define PHASE2LEN 20

bool TwoPhaseGreedyPhase1(Graph* ghat, Graph* g, std::vector<int> seeds, int k) {
    auto seed = &g->nodes[seeds[0]];
    auto Sp = seed->neighborOut();
    if (Sp.size() >= k) return false;


}

bool TwoPhaseGreedyPhase2(Graph *ghat, Graph* g, std::vector<int> seeds, int k) {
    
}

bool TwoPhaseGreedy(Graph *ghat, Graph* g, std::vector<int> seeds, int k) {
    
}