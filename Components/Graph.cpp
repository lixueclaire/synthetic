//
// Created by shaoyu on 2023/12/10.
//

#include "Graph.hpp"

#include "../Generator/DistanceHopGenerator.hpp"

void Graph::setNodeNum(int new_node_num) {
    this->node_num = new_node_num;
}

void Graph::setEdgesGenerator(Parameter params) {
    switch (params.generator_type) {
        case GeneratorParam::DistanceGenerator:
            this->edge_generator = new DistanceEdgesGenerator();
            break;
        case GeneratorParam::RandomGenerator:
            this->edge_generator = new RandomEdgesGenerator();
            break;
        case GeneratorParam::DistanceHopGenerator:
            this->edge_generator = new DistanceHopGenerator();
            break;
        default:
            assert(false);
    }
}

void Graph::setDegreeDistribution(Parameter params) {
    switch (params.distribution_type) {
        case DistributionParam::NoneDistribution:

        case DistributionParam::FacebookDistribution:
            this->degree_distribution = new FacebookDistribution();
            this->degree_distribution->initialize(params);
            break;
        default:
            assert(false);
    }
}

void Graph::generateNodes() {
    nodes.clear();
    for (int i = 0;i < this->node_num; i++) {
        Node node;
        node.setDegree(this->degree_distribution->nextDegree());
        nodes.push_back(node);
    }
}

void Graph::generateEdges() {
    edge_generator->generateEdges(nodes);
    for(int i = 0; i < node_num; ++i){
        Node& node1 = nodes[i];
        edge_num += node1.edges.size();
    }
    edge_num /= 2;
}

void RealGraph::readGraph(const std::string& s) {
    std::ifstream ifs(s, std::ios::in);
    ifs >> this->node_num >> this->edge_num;
    this->nodes.resize(this->node_num);

    std::vector<int> uu, vv, list;
    std::unordered_map<int, int> mp;
    for (int i = 0;i < this->edge_num; i++) {
        int u, v;
        ifs >> u >> v;
        uu.push_back(u);
        vv.push_back(v);
        list.push_back(u);
        list.push_back(v);
    }
    std::cout << "sorting...\n";
    sort(list.begin(), list.end());
    int k = 0;
    for (int i = 0;i < list.size(); i++) {
        if (i == 0 || list[i] != list[i - 1]) {
            mp[list[i]] = k++;
        }
    }

    for (int i = 0;i < this->edge_num; i++) {
        int u = mp[uu[i]];
        int v = mp[vv[i]];
        this->nodes[u].edges.push_back(v);
        this->nodes[v].edges.push_back(u);
        this->nodes[u].degree++;
        this->nodes[v].degree++;
    }

    std::cout << "reading finish\n";
}

void RealGraph::calcBucket() {
    std::vector<int> degrees;
    for (auto &node : this->nodes) {
        degrees.push_back(node.degree);
    }
    sort(degrees.begin(), degrees.end());

    int j = 0;
    std::vector<double> new_degrees;
    for (int i = 1;i < degrees.size(); i++) {
        if (degrees[i] == degrees[i - 1]) continue;
        int len = i - 1 - j + 1;
        for (int k = 0;k < len; k++) {
            new_degrees.push_back(degrees[j] + 1.0 * k / len);
        }
        j = i;
    }
    int len = degrees.size() - 1 - j + 1;
    for (int k = 0;k < len; k++) {
        new_degrees.push_back(degrees[j] + 1.0 / len);
    }

    std::fstream ofs("../LiveJournalDistribution.txt");
    for (int i = 0;i < 100; i++) {
        ofs << new_degrees[(int)(1.0 * i / 100 * this->node_num)] << " " << new_degrees[(int)(1.0 * (i + 1) / 100 * this->node_num - 1)] << " " << i + 1 << "\n";
    }
}

int  Graph::triangleCounting() {
    int count = 0;
    int total = 0;
    for (int i = 0;i < node_num; i++) {
        total += nodes[i].degree * (nodes[i].degree - 1) / 2;
        for (int &j : nodes[i].edges) {
            if (j > i) {
                std::unordered_set<int> s;
                for (auto &x : nodes[i].edges) {
                    if (x > j) s.insert(x);
                }
                for (auto &x : nodes[j].edges) {
                    if (s.count(x)) count++;
                }
            }
        }
    }
//    total = (total - count * 3) + count;
//    std::cout << "frac1 " << count << " " << total << " ";
//    double frac = 1.0 * count / total;
//    std::cout << frac << "\n";
    return count;
}

void Graph::dis_bfs(int node, std::vector<int> &vis) {
    vis[node] = 1;
    std::queue<int> q;
    q.push(node);
    while (!q.empty()){
        int u = q.front();
        q.pop();
        for(auto &v : nodes[u].edges) {
            if (vis[v] == 0){
                vis[v] = vis[u] + 1;
                q.push(v);
            }
        }
    }
}
int Graph::get_fa(int x){
    return f[x] == x ? x : f[x] = get_fa(f[x]);
}
int Graph::diameter() {
    /*int diameter = 0;
    for (int i = 0;i < node_num; i++) {
        std::vector<int> vis;
        vis.resize(node_num);
        vis[i] = 1;
        std::queue<int> q;
        q.push(i);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto &v : nodes[u].edges) {
                if (vis[v] == 0) {
                    vis[v] = vis[u] + 1;
                    q.push(v);
                    diameter = std::max(diameter, vis[v]);
//                    diameter += vis[v];
                }
            }
        }
    }
    //return diameter;
    std::cout << diameter << "(correct) ";*/

    f.resize(node_num);
    for(int i = 0; i < node_num; ++i)
        f[i] = i;
    for(int i = 0; i < node_num; ++i){
        for(auto v:nodes[i].edges){
            int fi = get_fa(i);
            int fv = get_fa(v);
            if(fi != fv)
                f[fi] = fv;
        }
    }//判断联通性
    std::vector<int> d, sign;
    d.resize(node_num);
    sign.resize(node_num);
    for(int i = 0; i < node_num; ++i){
        int fi = get_fa(i);
        if(sign[fi] == 0){
            sign[fi] = 1;
            dis_bfs(fi,d);
        }
    }//每个联通块分别做bfs
    for(int i = 0; i < node_num; ++i){
        int fi = get_fa(i);
        if(d[i] > sign[fi])sign[fi] = d[i];
    }
    int d2 = 0;

    for(int i = 0; i < node_num; ++i){
        int fi = get_fa(i);
        if(d[i] == sign[fi]){
            std::vector<int> d_;
            d_.resize(node_num);
            dis_bfs(i, d_);
            for(int j = 0; j < node_num; ++j)
                if(d_[j] > d2)d2 = d_[j];
        }
    }

    return d2;
}
void Graph::print_graph() {
    for(int i = 0; i < node_num; ++i){
        std::cout << i << ": ";
        for(auto j : nodes[i].edges){
            std::cout << j << " ";
        }
        putchar('\n');
    }
}