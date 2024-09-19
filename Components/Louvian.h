//
// Created by 13183 on 2024/2/28.
//

#ifndef DATAGENERATOR_LOUVIAN_H
#define DATAGENERATOR_LOUVIAN_H


#include "Graph.hpp"

class Louvian{
public:
    explicit Louvian(const Graph &g);
    Graph G;
    std::vector<double> modularity;
    std::vector<int> inner_p;
    std::vector<int> outer_p;
    std::vector<int> community;
    std::vector<int> num;

    void merge(int x, int y);   //merge node x to community y
    void solve();
    void print_result();
    static double calcModularity(int x, int y);
};


#endif //DATAGENERATOR_LOUVIAN_H
