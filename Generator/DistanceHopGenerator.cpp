//
// Created by shaoyu on 2024/1/24.
//

#include "DistanceHopGenerator.hpp"

void DistanceHopGenerator::generateEdges(std::vector<Node>& nodes) {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<> distr(0.0, 1.0);

    int counter = 0;
    double alpha = 10;
    int c = 0, j = 0, k = 0;

    for (int i = 0;i < nodes.size(); i++) {
        if (i % 100000 == 0) std::cout << "current nodes, i = " << i << "\n";
        Node& node_1 = nodes[i];
        c = 0;
        j = i;

        while (node_1.edges.size() < node_1.degree) {
            double f = distr(eng);
            k = j + (int)((1 / f - 1) * c / alpha) + 1;
            if (k >= nodes.size()) break;

            Node& node_2 = nodes[k];
            if (node_2.edges.size() < node_2.degree) {
                node_1.edges.push_back(k);
                node_2.edges.push_back(i);
                tot_edge++;
            }
            c = c + (k -j);
            j = k;
        }
        // 循环结束时，节点的边数若小于设定的度数
        // if(node_1.edges.size() < node_1.degree)
        //     counter++;
    }
    //std::cout << "wrong nodes: " << counter << "\n";


    // 下标i和参数c能够确定一次采样
    /*std::priority_queue<
            std::pair<int, int>,
            std::vector<std::pair<int, int>>,
            std::greater<>>
            sampling_set;
    for (int i = 0;i < nodes.size(); i++) {
        sampling_set.emplace(i, 0);
    }
    while (!sampling_set.empty()) {
        auto params = sampling_set.top();
        sampling_set.pop();
        int idx = params.first;
        Node& node_1 = nodes[idx];
        int c = params.second;

        if (node_1.edges.size() < node_1.degree) {
            double r = distr(eng);
            int k = (int)((1 / r - 1) * c) + 1;
            if (idx + c + k >= nodes.size()) continue;
            Node& node_2 = nodes[idx + k];
            if (node_2.edges.size() < node_2.degree) {
                node_1.edges.push_back(idx + c + k);
                node_2.edges.push_back(idx);
                tot_edge++;
            }
            c = c + k;
            sampling_set.emplace(idx, c);
        }
    }*/




}
