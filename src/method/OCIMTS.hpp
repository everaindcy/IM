#pragma once

#include "model.hpp"

double OCIMTS(Graph* ghat, Graph* g, std::vector<int> seeds, int k, int T) {
    double ans = 0;
    for (int phase = 0; phase < T; phase++) {
        ghat->genP();
        auto Sp = Greedy(ghat, k, seeds);

        g->test(Sp, seeds);
        ans += g->nodeNum(1);
        updateABp(ghat, g);

        // for (auto &e : ghat->edges) {
        //     std::cout << double(e.alpha)/(e.alpha+e.beta) << ", ";
        // }
        // std::cout << std::endl;
    }
    return ans;
}
