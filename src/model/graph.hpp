#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "rand.hpp"

class Node;

class Edge {
public:
    int idx;
    // graph parameter
    Node *in, *out;
    double p;
    // simulation info
    int state, round;
    // model parameter
    int alpha, beta;

    Edge():
        in(nullptr), out(nullptr), p(0), state(0), round(0), alpha(1), beta(1) {}
    Edge(Node *in, Node *out, double p):
        in(in), out(out), p(p), state(0), round(0), alpha(1), beta(1) {}
};

class Node {
public:
    int idx;
    // graph parameter
    std::vector<Edge*> in, out;
    // simulation info
    int state, round;

    Node() = default;

    std::vector<int> neighborOut() {
        std::vector<int> ans;
        for (auto e : out) {
            ans.push_back(e->out->idx);
        }
        return ans;
    }
    std::vector<int> neighborIn() {
        std::vector<int> ans;
        for (auto e : in) {
            ans.push_back(e->in->idx);
        }
        return ans;
    }
};

class Graph {
public:
    typedef bool (*renewFunc)(Graph *, Node *);

    std::vector<Node> nodes;
    std::vector<Edge> edges;
    renewFunc renew1, renew2;

    int round;
    bool active;

    Graph() = delete;
    Graph(int n, int m, renewFunc renew1, renewFunc renew2):
        nodes(std::vector<Node>(n)), edges(std::vector<Edge>(m)), renew1(renew1), renew2(renew2), round(1), active(false) {}
    Graph(std::string path, renewFunc renew1, renewFunc renew2);

    void reset() {
        for (auto &n : nodes) {
            n.state = 0;
            n.round = 0;
        }
        for (auto &e : edges) {
            e.state = 0;
            e.round = 0;
        }
        round = 1;
        active = false;
    }

    void next() {
        active = false;
        for (auto &n : nodes) {
            renew1(this, &n);
        }
        for (auto &n : nodes) {
            active |= renew2(this, &n);
        }

        round++;
        // for (auto &n : nodes) {
        //     std::cout << n.state << ", ";
        // }
        // std::cout << std::endl;
    }

    // run n steps; if n == -1, run until donot change
    void next(int n) {
        if (n < 0) {
            while (active) {
                next();
            }
        }
        for (int i = 0; i < n; i++) {
            next();
        }
    }

    void activeNode(std::vector<int> idx, int state) {
        for (auto i : idx) {
            if (nodes[i].state == 0) {
                nodes[i].state = state;
                nodes[i].round = round;
                active = true;
            }
        }
    }

    void test(std::vector<int> Sp, std::vector<int> Sm) {
        reset();
        activeNode(Sm, -1);
        activeNode(Sp, 1);
        next(-1);
    }

    int nodeNum(int state) {
        int sum = 0;
        for (auto &n : nodes) {
            if (n.state == state) {
                sum++;
            }
        }
        return sum;
    }

    // model functions

    void genP() {
        for (auto &e : edges) {
            e.p = rdm::randbeta(e.alpha, e.beta);
        }
    }
};

Graph::Graph(std::string path, renewFunc renew1, renewFunc renew2):
    renew1(renew1), renew2(renew2), round(1), active(false) {
    std::ifstream infile;
    infile.open(path, std::ios::in);
    int n, m;
    infile >> n >> m;
    nodes = std::vector<Node>(n);
    edges = std::vector<Edge>(m);
    for (int i = 0; i < nodes.size(); i++) {
        nodes[i].idx = i;
    }
    for (int i = 0; i < edges.size(); i++) {
        edges[i].idx = i;
    }

    int a, b;
    double p;
    for (int i = 0; i < m; i++) {
        infile >> a >> b >> p;
        edges[i].in = &nodes[a]; nodes[a].out.push_back(&edges[i]);
        edges[i].out = &nodes[b]; nodes[b].in.push_back(&edges[i]);
        edges[i].p = p;
    }
    infile.close();
}

