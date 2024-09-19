#include "Components//Graph.hpp"
#include "Parameter.hpp"
#include "Components/Louvian.h"
#include "Components/Group.hpp"

void Generator(int node_num, const std::string& output_path) {
    Parameter params{}; 
    
    /*设置参数*/
    params.node_num = node_num;
    params.distribution_type = DistributionParam::FacebookDistribution;
    params.generator_type = GeneratorParam::DistanceHopGenerator;

    Graph graph;
    graph.setNodeNum(params.node_num);
    graph.setEdgesGenerator(params); 
    graph.setDegreeDistribution(params);
    std::cout << "initializing finish" << "\n";
     
    /*生成点并给每个点分配一个根据度分布设定好的度*/
    graph.generateNodes(); 
    std::cout << "generate nodes finish" << "\n";  
    
    /*连边*/
    graph.generateEdges();                     
    std::cout << "generate edges finish" << "\n";    

    /*long long e = 0;
    for (int i = 0;i < graph.node_num; i++) {
        e += graph.nodes[i].edges.size();
    }*/

    /*计算边数*/
    std::cout << "total edges  " << graph.edge_generator->tot_edge << "\n";
    std::cout << "total test  " << graph.edge_generator->tot_test << "\n";

    /*std::cout << "edges = " << e << "\n";*/

    GroupGenerator(graph);

    freopen(output_path.c_str(), "w", stdout);
    //std::ofstream ofs("generated.txt", std::ios::out);
    //ofs << graph.node_num << " " << graph.edge_generator->tot_edge << "\n";
    for(int i = 0; i < graph.node_num; ++i){
        for (int j = 0;j < graph.nodes[i].edges.size(); j++) {
            //if (i < graph.nodes[i].edges[j]) ofs << i << " " << graph.nodes[i].edges[j] << "\n";
            printf("%d %d\n", i, graph.nodes[i].edges[j]);
        }
    }
}

void Sample(const std::string& s) {
    RealGraph graph;
    graph.readGraph(s);
    graph.calcBucket();
    // std::cout << "source graph diameter = " << graph.diameter() << "\n";
    // std::cout << "source graph triangle = " << graph.triangleCounting() << "\n";
}

void Test(){
    RealGraph g;
    g.readGraph("../testGraph.txt");
    Louvian v(g);
    v.solve();
    v.print_result();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <node_num> <output_path>\n";
        return 1;
    }
    
    int node_num = std::atoi(argv[1]);
    std::string output_path = argv[2];
    
    srand(5);
    double start = clock();
    Generator(node_num, output_path);
    double end = clock();
    // std::cout << "Time = " << (end - start) / CLOCKS_PER_SEC << "s \n" << std::endl;

    return 0;
}
