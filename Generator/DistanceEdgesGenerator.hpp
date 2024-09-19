//
// Created by shaoyu on 2023/12/10.
//

#ifndef DATAGENERATOR_DISTANCEEDGESGENERATOR_HPP
#define DATAGENERATOR_DISTANCEEDGESGENERATOR_HPP

#include "EdgesGenerator.hpp"
#include "ExponentialSampler.hpp"

class DistanceEdgesGenerator : public EdgesGenerator {
public:
    void generateEdges(std::vector<Node> &nodes) override;
    bool edgeTest(Node &n1, Node &n2, int dist) const;
private:
    const double baseProbCorrelated = 0.95;
    ProbabilitySampler *sampler;
};


#endif //DATAGENERATOR_DISTANCEEDGESGENERATOR_HPP
