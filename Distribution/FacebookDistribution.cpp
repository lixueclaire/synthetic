//
// Created by shaoyu on 2023/12/9.
//

#include "FacebookDistribution.hpp"

void FacebookDistribution::initBuckets(std::vector<Bucket> &buckets, Parameter params) {
    mean = (int)calcMean(params.node_num);
//    mean = FB_MEAN;
    std::cout << params.node_num << " mean=" << mean << "\n";
    buckets.resize(100);
    loadFacebookBuckets();
    rebuildBuckets();
}

double FacebookDistribution::calcMean(int node_num) {
    return round(pow(node_num, 0.512-0.028 * log10(node_num)));
}

void FacebookDistribution::loadFacebookBuckets() {
    std::ifstream ifs("../facebookBucket100.dat", std::ios::in);
    assert(ifs.is_open());
    double min_degree, max_degree;
    int id;
    int siz = 0;
    for (int i = 0; i <= 99; i++) {
        ifs >> min_degree >> max_degree >> id;
        assert(id == i + 1);
        siz += (max_degree + min_degree) / 2;
        buckets[i].min_degree = min_degree;
        buckets[i].max_degree = max_degree;
    }
    ifs.close();
}

void FacebookDistribution::rebuildBuckets() {
    double new_min_degree;
    double new_max_degree;
    for (Bucket& bucket : buckets) {
        new_min_degree = 1.0 * bucket.min_degree * mean / FB_MEAN;
        new_max_degree = 1.0 * bucket.max_degree * mean / FB_MEAN;
        if (new_max_degree < new_min_degree) new_max_degree = new_min_degree;
        bucket.min_degree = new_min_degree;
        bucket.max_degree = new_max_degree;
    }
}