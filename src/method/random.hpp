#pragma once

#include "model.hpp"

#define RANDOMPHASELEN 11000

void RANDOM(Graph* ghat, Graph* g) {
    int idx = 0;
    for (int phase = 0; phase < RANDOMPHASELEN; phase++) {
        auto Sp = std::vector<int>({idx});
        g->test(Sp, std::vector<int>());
        updateABp(ghat, g);
        idx = (idx+1) % ghat->nodes.size();

        for (auto &e : ghat->edges) {
            std::cout << double(e.alpha)/(e.alpha+e.beta) << ", ";
        }
        std::cout << std::endl;
    }
}