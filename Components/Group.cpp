#include "Group.hpp"

void GroupGenerator(Graph &graph) {
    std::ofstream ofs("community.txt", std::ios::out);
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<> distr(0.0, 1.0);

    for (int i = 0;i < graph.node_num; i++) {
        double random = distr(eng);
        if (random >= 0.05) continue;
        std::unordered_map<int, int> mp;
        mp[i] = 1;
        for (auto &neighbor : graph.nodes[i].edges) {
            mp[neighbor] = 1;
        }
        int num = (int)(distr(eng) * 100);
        ofs << i;
        int iter = 0;
        while (num) {
            iter++;
//            if (i > 9800) {
//                std::cout << "???\n";
//            }
            random = distr(eng);
            if (random < 0.3 && !graph.nodes[i].edges.empty()) {
                int idx = (int)(distr(eng) * graph.nodes[i].edges.empty());
                int v = graph.nodes[i].edges[idx];
                if (mp[v] == 1) {
                    ofs << " " << v;
                    mp[v] = 2;
                    num--;
                }
            }   else {
                random = distr(eng);
                int v = (int)(distr(eng) * 1000);
                if (distr(eng) > 0.5) v = i + v; else v = i - v;
                v = std::max(v, 0); v = std::min(v, (int)graph.nodes.size() - 1);
                if (random < 0.1 && mp[v] != 2) {
                    ofs << " " << v;
                    mp[v] = 2;
                    num--;
                }
            }
        }
        ofs << "\n";
    }
}