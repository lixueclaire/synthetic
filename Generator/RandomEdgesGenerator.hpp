//
// Created by shaoyu on 2023/12/12.
//

#ifndef DATAGENERATOR_RANDOMEDGESGENERATOR_HPP
#define DATAGENERATOR_RANDOMEDGESGENERATOR_HPP

#include "EdgesGenerator.hpp"

class RandomEdgesGenerator : public EdgesGenerator {
    void generateEdges(std::vector<Node> &nodes) override;

};


#endif //DATAGENERATOR_RANDOMEDGESGENERATOR_HPP
