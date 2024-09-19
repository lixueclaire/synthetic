//
// Created by shaoyu on 2023/12/9.
//

#include "Node.hpp"

void Node::setDegree(int d) {
   this->degree = d;
    // this->degree = std::max(d, 2);
}

int Node::getDegree() {
    return this->degree;
}