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

    double perform = 0;
    for (int i = 0; i < N; i++){
        auto ghat = Graph(graphfile, ICrenew1, ICrenew2);
        // OCIMTS(&ghat, &g, seeds, k);
        TwoPhaseGreedy(&ghat, &g, seeds, k);
        ghat.genP();

        for (auto &e : ghat.edges) {
            std::cout << double(e.alpha)/(e.alpha+e.beta) << ", ";
        }
        std::cout << std::endl;
        for (auto &e : ghat.edges) {
            std::cout << e.p << ", ";
        }
        std::cout << std::endl;

        auto Sp = Greedy(&ghat, k, seeds);
        auto ans = TestGraph(1000, &g, Sp, seeds);
        perform += ans;
        std::cout << i << ": " << ans << std::endl;
    }
    perform /= N;
    std::cout << "mean: " << perform << std::endl;

    return 0;
}