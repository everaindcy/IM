#include <map>
#include "OCIMTS.hpp"
#include "random.hpp"
#include "twophasegreedy.hpp"

// runner graphfile seed k N
int main(int argc, char *argv[]) {
    rdm::init(112233);
    // auto graphfile = std::string(argv[1]);
    // auto seed = std::stoi(argv[2]);
    // auto k = std::stoi(argv[3]);
    // auto N = std::stoi(argv[4]);
    auto graphfile = "../graph/graphtest.graph";
    auto seed = 0;
    auto k = 3;
    auto N = 20;
    auto T = 1000;
    auto step = 20;

    auto g = Graph(graphfile, ICrenew1, ICrenew2);
    auto seeds = std::vector<int>({seed});

    // auto ghat = Graph(graphfile, ICrenew1, ICrenew2);
    // RANDOM(&ghat, &g);
    // return 0;

    // for (int i = 0; i < 10; i++) {
    //     g.reset();
    //     g.activeNode(std::vector<int>({0}), -1);
    //     g.activeNode(std::vector<int>({7}), 1);
    //     g.next(-1);
    //     std::cout << g.nodeNum(1) << std::endl;
    // }
    // return 0;

    // std::cout << g.nodes.size() << " " << g.edges.size() << std::endl;
    // for (auto n : g.nodes) {
    //     std::cout << "node " << n.idx << ": in: ";
    //     for (auto e : n.in) {
    //         std::cout << e->in->idx << " ";
    //     }
    //     std::cout << "out: ";
    //     for (auto e : n.out) {
    //         std::cout << e->out->idx << " ";
    //     }
    //     std::cout << std::endl;
    // }
    // for (auto e : g.edges) {
    //     std::cout << e.in->idx << " " << e.out->idx << " " << e.p << std::endl;
    // }

    std::map<int, std::map<int, double> > performMtx;
    for (int p1len = 0; p1len < T / 2; p1len += step) {
        for (int p2len = 0; p2len < T/2-p1len; p2len += step) {
            double perform = 0;
            for (int i = 0; i < N; i++){
                auto ghat = Graph(graphfile, ICrenew1, ICrenew2);
                // auto ans = OCIMTS(&ghat, &g, seeds, k, 1000);
                auto ans = TwoPhaseGreedy(&ghat, &g, seeds, k, p1len, p2len, T);
                perform += ans;
                // std::cout << i << ": " << ans << std::endl;

                // for (auto &e : ghat.edges) {
                //     std::cout << double(e.alpha)/(e.alpha+e.beta) << ", ";
                // }
                // std::cout << std::endl;
            }
            perform /= N*T;
            // std::cout << "mean: " << perform << std::endl;
            performMtx[p1len][p2len] = perform;
        }
    }

    int maxp1len, maxp2len;
    double max = 0;
    for (auto &line : performMtx) {
        std::cout << line.first << ": {";
        for (auto &item : line.second) {
            std::cout << item.first << ":" << item.second << ", ";
            if (item.second > max) {
                maxp1len = line.first;
                maxp2len = item.first;
                max = item.second;
            }
        }
        std::cout << "}" << std::endl;
    }
    std::cout << "max: " << maxp1len << ", " << maxp2len << ", " << max << std::endl;

    double perform = 0;
    for (int i = 0; i < N; i++){
        auto ghat = Graph(graphfile, ICrenew1, ICrenew2);
        auto ans = OCIMTS(&ghat, &g, seeds, k, T);
        // auto ans = TwoPhaseGreedy(&ghat, &g, seeds, k, p1len, p2len, T);
        perform += ans;
        // std::cout << i << ": " << ans << std::endl;

        // for (auto &e : ghat.edges) {
        //     std::cout << double(e.alpha)/(e.alpha+e.beta) << ", ";
        // }
        // std::cout << std::endl;
    }
    perform /= N*T;
    std::cout << "mean: " << perform << std::endl;

    return 0;
}