//
// Created by shaoyu on 2023/12/10.
//

#ifndef DATAGENERATOR_EDGESGENERATOR_HPP
#define DATAGENERATOR_EDGESGENERATOR_HPP

#include "../Components/Node.hpp"
#include "../library.hpp"

class EdgesGenerator {
public:
    long long tot_edge = 0, tot_test = 0;
    virtual void generateEdges(std::vector<Node> &nodes) = 0;
};


#endif //DATAGENERATOR_EDGESGENERATOR_HPP
