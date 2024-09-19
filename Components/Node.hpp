//
// Created by shaoyu on 2023/12/9.
//

#ifndef DATAGENERATOR_NODE_HPP
#define DATAGENERATOR_NODE_HPP

#include "../library.hpp"

class Node {
public:
    int degree;
    std::vector<int> edges;

    void setDegree(int d);
    int getDegree();
};


#endif //DATAGENERATOR_NODE_HPP
