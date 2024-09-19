//
// Created by shaoyu on 2023/12/10.
//

#include "DistanceEdgesGenerator.hpp"

void DistanceEdgesGenerator::generateEdges(std::vector<Node> &nodes) {
    sampler = new ExponentialSampler;
    sampler->initSampler(baseProbCorrelated);

//     for (int i = 0;i < nodes.size() - 1; i++) {
//         nodes[i].edges.push_back(i + 1);
//         nodes[i + 1].edges.push_back(i);
//     }

    std::vector<int> order;
    for (int i = 0;i < nodes.size(); i++) order.push_back(i);

    int iter_num = 3;
    for (int iter = 0;iter < iter_num; iter++) {
        for (int i = 0;i < nodes.size(); i++) {
            Node& node_1 = nodes[order[i]];
            for (int j = i + 1;j < nodes.size(); j++) {
                tot_test++;
                if ((int)(node_1.degree * 1.0 * (iter + 1) / iter_num) == node_1.edges.size()) break;
                if (j - i > 1000) break;
                Node& node_2 = nodes[order[j]];
                if (edgeTest(node_1, node_2, j - i)) {
                    node_1.edges.push_back(order[j]);
                    node_2.edges.push_back(order[i]);
                    tot_edge++;
                }
            }
        }
        std::random_shuffle(order.begin(), order.end());
    }

}

bool DistanceEdgesGenerator::edgeTest(Node &n1, Node &n2, int dist) const {

    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<> distr(0.0, 1.0);

    if (n1.degree == n1.edges.size()) return false;
    if (n2.degree == n2.edges.size()) return false;

    return sampler->sampling(dist);

//    double random = 1.0 * (rand()%100) / 100;
//    double prob = pow(baseProbCorrelated, dist);

    double random = distr(eng);
//    double prob = (11 * 0.95) / (dist + 10);
    double prob = 1.0 / dist;
    return (random < prob) || (random < 0.2);
}
/*边测试，每条边有一定的的概率得到保留，未通过test的边会被删掉*/