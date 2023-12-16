#pragma once

#include "model.hpp"

#define PHASELEN 1100

void OCIMTS(Graph* ghat, Graph* g, std::vector<int> seeds, int k) {
    for (int phase = 0; phase < PHASELEN; phase++) {
        ghat->genP();
        auto Sp = Greedy(ghat, k, seeds);

        g->test(Sp, seeds);
        updateABp(ghat, g);

        for (auto &e : ghat->edges) {
            std::cout << double(e.alpha)/(e.alpha+e.beta) << ", ";
        }
        std::cout << std::endl;
    }
}
