//
// Created by 13183 on 2024/2/28.
//

#include "Louvian.h"


Louvian::Louvian(const Graph &g) {
    G = g;
    for (int i = 0; i < G.node_num; ++i) {
        int t = G.nodes[i].edges.size();
        num.push_back(1);
        inner_p.push_back(0);
        outer_p.push_back(t);
        modularity.push_back(calcModularity(0, t));
        community.push_back(i);
    }
    //G.print_graph();
}

void Louvian::merge(int x, int y) {
    int o = community[x];
    community[x] = y;
    Node &node_x = G.nodes[x];
    for (int tmp: node_x.edges) {
        if (community[tmp] == o) {
            inner_p[o]--;
            outer_p[o]++;
            outer_p[y]++;
        } else if (community[tmp] == y) {
            outer_p[o]--;
            outer_p[y]--;
            inner_p[y]++;
        } else {
            outer_p[o]--;
            outer_p[y]++;
        }
    }
    int outer_edge = 0, inner_edge = 0;
    for (int i = 0; i < G.node_num; ++i)
        outer_edge += outer_p[i], inner_edge += inner_p[i];
    outer_edge /= 2;
    assert(outer_edge + inner_edge == G.edge_num);
    modularity[o] = calcModularity(inner_p[o], outer_p[o]);
    modularity[y] = calcModularity(inner_p[y], outer_p[y]);
    num[y]++;
    num[o]--;
}

void Louvian::solve() {
    double sum = 0;
    for (int i = 0; i < G.node_num; ++i)sum += modularity[i];//模块度之和
    //while (true) {
    for (int T = 10; T >= 1; T--) {
        double newSum = sum;
        for (int i = 0; i < G.node_num; ++i) {
            Node &node1 = G.nodes[i];
            double increment = 0.0;
            int newCommunity = -1;
            std::vector<std::pair<int, int> > v;
            for (auto j: node1.edges) {
                bool fl = true;
                for (auto &k: v)
                    if (k.first == community[j])k.second++, fl = false;
                if (fl)v.emplace_back(community[j], 1);
            }
            /*record all the community that the nodes connected with node i belong to*/
            for (auto j: v)
                if (community[i] != j.first) {
                    int a = inner_p[community[i]];
                    int b = outer_p[community[i]];
                    int c = inner_p[j.first];
                    int d = outer_p[j.first];
                    double e = modularity[community[i]] + modularity[j.first];
                    for (auto k: v) {
                        if (k.first == j.first) {
                            b -= k.second;
                            c += k.second;
                            d -= k.second;
                        } else if (k.first == community[i]) {
                            a -= k.second;
                            b += k.second;
                            d += k.second;
                        } else {
                            b -= k.second;
                            d += k.second;
                        }
                    }
                    e = calcModularity(a, b) + calcModularity(c, d) - e;
                    if (e > increment)
                        increment = e, newCommunity = j.first;
                }
            if (increment > 0) {
                newSum += increment;
                merge(i, newCommunity);
            }
        }
        //if (newSum == sum)break;
        sum = newSum;
        std::cout << sum << std::endl;
    }
}

void Louvian::print_result() {
    double sum = 0;
    for (int i = 0; i < G.node_num; ++i)sum += modularity[i];//模块度之和
    std::cout << " the sum pf modularity is " << sum << std::endl;
    for (int i = 0; i < G.node_num; ++i) {
        if (num[i] > 1) {
            std::cout << "the number " << i << " community has " << num[i] << " nodes\n";
        }
//        if (num[i] == 1)
//            assert(outer_p[i] == 0);
    }
}

double Louvian::calcModularity(int x, int y) {
    return 1.0 * x - y * sqrt(y);
}
