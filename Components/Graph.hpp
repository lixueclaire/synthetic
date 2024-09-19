//
// Created by shaoyu on 2023/12/10.
//

#ifndef DATAGENERATOR_GRAPH_HPP
#define DATAGENERATOR_GRAPH_HPP

#include "Node.hpp"
#include "../library.hpp"
#include "../Generator/DistanceEdgesGenerator.hpp"
#include "../Generator/RandomEdgesGenerator.hpp"
#include "../Distribution//FacebookDistribution.hpp"

class Graph {
public:
    int node_num;
    int edge_num;
    std::vector<Node> nodes;
    std::vector<int> f;//判断连通性
    EdgesGenerator* edge_generator;
    DegreeDistribution* degree_distribution;

    void setNodeNum(int new_node_num);
    void setEdgesGenerator(Parameter params);
    void setDegreeDistribution(Parameter params);

    void generateNodes();
    void generateEdges();

    int triangleCounting();
    int diameter();
    void dis_bfs(int node, std::vector<int> &vis);

    int get_fa(int x);

    void print_graph();
};

class RealGraph : public Graph {
public:
    void readGraph(const std::string& s = "../Facebook4039.txt");
    void calcBucket();
};


#endif //DATAGENERATOR_GRAPH_HPP
