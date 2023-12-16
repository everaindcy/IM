#pragma once

#include "graph.hpp"

void updateABp(Graph *ghat, Graph* g) {
    for (auto &ehat : ghat->edges) {
        auto e = g->edges[ehat.idx];
        if (e.round == 0) continue;
        if (e.in->state != 1) continue;
        if (e.state == 1) ehat.alpha++;
        else ehat.beta++;
    }
}

void updateAB(Graph *ghat, Graph* g) {
    for (auto &ehat : ghat->edges) {
        auto e = g->edges[ehat.idx];
        if (e.round == 0) continue;
        if (e.state != 0) ehat.alpha++;
        else ehat.beta++;
    }
}
