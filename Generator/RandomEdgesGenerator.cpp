//
// Created by shaoyu on 2023/12/12.
//

#include "RandomEdgesGenerator.hpp"

#include <random>
// #include <__random/random_device.h>

void RandomEdgesGenerator::generateEdges(std::vector<Node> &nodes) {
    std::vector<int> pool;
    for (int i = 0;i < nodes.size(); i++) {
        for (int d = 0;d < nodes[i].degree; d++) {
            pool.push_back(i);
        }
    }

    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(pool.begin(), pool.end(), rng);
    for (int i = 0;i < pool.size(); i += 2) {
        int n1 = pool[i];
        int n2 = pool[i + 1];
        if (n1 != n2) {
            nodes[n1].edges.push_back(n2);
            nodes[n2].edges.push_back(n1);
        }
    }
}
/*为度数为x的节点新建x-1个副本，所有点重排后将相邻两点连边*/