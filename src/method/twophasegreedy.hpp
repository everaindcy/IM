#pragma once

#include <algorithm>
#include "OCIMTS.hpp"
#include "model.hpp"

double TwoPhaseGreedyPhase1(Graph* ghat, Graph* g, std::vector<int> seeds, int k, int plen) {
    auto seed = &g->nodes[seeds[0]];
    auto seedout = seed->neighborOut();
    if (seedout.size() >= k) return -1;
    auto k1 = k - seedout.size();

    double ans = 0;

    for (int phase = 0; phase < plen; phase++) {
        auto Sp = std::vector<int>(0);

        auto order = std::vector<int>(ghat->edges.size());
        for (int i = 0; i < order.size(); i++) order[i] = i;
        std::sort(order.begin(), order.end(),
            [ghat](const int &lhs, const int &rhs)->bool {
                return ghat->edges[lhs].alpha+ghat->edges[lhs].beta < ghat->edges[rhs].alpha+ghat->edges[rhs].beta;
            });
        
        for (auto i : order) {
            auto n = ghat->edges[i].in->idx;
            bool exist = false;
            for (auto j : seeds) {
                if (n == j) {
                    exist = true;
                    break;
                }
            }
            for (auto j : Sp) {
                if (n == j) {
                    exist = true;
                    break;
                }
            }
            if (exist) continue;
            Sp.push_back(n);
            if (Sp.size() >= k1) break;
        }
        for (auto i : seedout) {
            Sp.push_back(i);
        }

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

double TwoPhaseGreedyPhase2(Graph *ghat, Graph* g, std::vector<int> seeds, int k, int plen) {
    auto seed = &g->nodes[seeds[0]];
    auto seedout = seed->neighborOut();
    if (seedout.size() >= k) return -1;

    double ans = 0;

    for (int phase = 0; phase < plen; phase++) {
        auto Sp = std::vector<int>(0);
        for (auto i : seedout) {
            for (auto e : ghat->nodes[i].in) {
                auto n = e->in->idx;
                bool exist = false;
                for (auto j : seeds) {
                    if (n == j) {
                        exist = true;
                        break;
                    }
                }
                if (exist) continue;
                for (auto j : Sp) {
                    if (n == j) {
                        exist = true;
                        break;
                    }
                }
                if (exist) break;
                Sp.push_back(n);
            }
        }

        auto order = std::vector<int>(ghat->edges.size());
        for (int i = 0; i < order.size(); i++) order[i] = i;
        std::sort(order.begin(), order.end(),
            [ghat](const int &lhs, const int &rhs)->bool {
                return ghat->edges[lhs].alpha+ghat->edges[lhs].beta < ghat->edges[rhs].alpha+ghat->edges[rhs].beta;
            });
        
        for (auto i : order) {
            auto n = ghat->edges[i].in->idx;
            bool exist = false;
            for (auto j : seeds) {
                if (n == j) {
                    exist = true;
                    break;
                }
            }
            for (auto j : Sp) {
                if (n == j) {
                    exist = true;
                    break;
                }
            }
            if (exist) continue;
            Sp.push_back(n);
            if (Sp.size() >= k) break;
        }

        g->test(Sp, seeds);
        ans += g->nodeNum(1);
        updateABp(ghat, g);

        for (auto &e : seed->out) {
            auto ehat = &ghat->edges[e->idx];
            auto n = e->out;
            int pos = 0;
            for (auto &ein : n->in) {
                if (ein->round == 1 && ein->state == 1) {
                    pos++;
                }
            }
            if (pos == 0) continue;
            if (n->round != 2) continue;
            if (n->state == 1) {
                ehat->beta++;
            } else {
                ehat->alpha += pos+1;
                ehat->beta -= pos;
            }
        }

        // for (auto &e : ghat->edges) {
        //     std::cout << double(e.alpha)/(e.alpha+e.beta) << ", ";
        // }
        // std::cout << std::endl;
    }
    return ans;
}

double TwoPhaseGreedy(Graph *ghat, Graph* g, std::vector<int> seeds, int k, int p1len, int p2len, int T) {
    auto ans1 = TwoPhaseGreedyPhase1(ghat, g, seeds, k, p1len);
    if (ans1 < 0) return -1;
    auto ans2 = TwoPhaseGreedyPhase2(ghat, g, seeds, k, p2len);
    if (ans2 < 0) return -1;
    ghat->genP();
    auto Sp = Greedy(ghat, k, seeds);
    auto ans3 = TestGraph(T - p1len - p2len, g, Sp, seeds)*(T - p1len - p2len);
    // auto ans3 = OCIMTS(ghat, g, seeds, k, T-p1len-p2len);
    return ans1 + ans2 + ans3;
}