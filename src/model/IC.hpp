#pragma once

#include "graph.hpp"

bool ICrenew1(Graph *g, Node *n) {
    if (n->round != g->round) return false;
    auto ok = false;
    for (auto e : n->out) {
        e->round = n->round;
        if (rdm::randreal() <= e->p) {
            e->state = n->state;
            ok = true;
        }
    }
    return ok;
}

bool ICrenew2(Graph *g, Node *n) {
    if (n->state != 0) return false;
    auto pos = 0, neg = 0;
    for (auto e : n->in) {
        if (e->round != g->round) continue;
        if (e->state == 1) pos++;
        if (e->state == -1) neg++;
    }
    if (pos == 0 && neg == 0) {
        return false;
    // } else if (neg == 0) {
    //     n->round = g->round + 1;
    //     n->state = 1;
    // } else if (pos == 0) {
    //     n->round = g->round + 1;
    //     n->state = -1;
    } else {
        n->round = g->round + 1;
        double p = double(pos) / (double(pos) + double(neg));
        if (rdm::randreal() < p) n->state = 1;
        else n->state = -1;
    }
    return true;
}