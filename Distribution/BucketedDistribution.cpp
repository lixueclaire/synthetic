//
// Created by shaoyu on 2023/12/9.
//

#include "BucketedDistribution.hpp"

void BucketedDistribution::initialize(Parameter params) {
    initBuckets(this->buckets, params);
}

int BucketedDistribution::nextDegree() {
    int bucket = rand() % buckets.size();
    int min_degree = (int)buckets[bucket].min_degree;
    int max_degree = (int)buckets[bucket].max_degree;
    return rand() % (max_degree - min_degree + 1) + min_degree;
}