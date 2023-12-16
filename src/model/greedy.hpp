#pragma once

#include "graph.hpp"

#define MONTECARLOSAMPLENUM 100

int TestGraph(Graph *g, std::vector<int> Sp, std::vector<int> Sm) {
    g->test(Sp, Sm);
    return g->nodeNum(1);
}

double TestGraph(int num, Graph *g, std::vector<int> Sp, std::vector<int> Sm) {
    double ans = 0;
    for (int i = 0; i < num; i++) {
        ans += double(TestGraph(g, Sp, Sm));
    }
    return ans/double(num);
}

std::vector<int> Greedy(Graph *g, int k, std::vector<int> Sm) {
    std::vector<int> Sp;
    int n = g->nodes.size();
    while (Sp.size() < k) {
        int idx;
        double max = 0;
        for (int i = 0; i < n; i++) {
            bool exist = false;
            for (auto j : Sp) {
                if (i == j) {
                    exist = true;
                    break;
                }
            }
            for (auto j : Sm) {
                if (i == j) {
                    exist = true;
                    break;
                }
            }
            if (exist) continue;
            Sp.push_back(i);
            double now = TestGraph(MONTECARLOSAMPLENUM, g, Sp, Sm);
            if (now > max) {
                idx = i;
                max = now;
            }
            Sp.pop_back();
        }
        Sp.push_back(idx);
    }
    return Sp;
}