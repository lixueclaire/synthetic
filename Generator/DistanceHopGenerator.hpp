//
// Created by shaoyu on 2024/1/24.
//

#ifndef DISTANCEHOPGENERATOR_HPP
#define DISTANCEHOPGENERATOR_HPP

#include "../library.hpp"
#include "EdgesGenerator.hpp"

class DistanceHopGenerator : public EdgesGenerator {
public:
    void generateEdges(std::vector<Node> &nodes) override;
};



#endif //DISTANCEHOPGENERATOR_HPP
