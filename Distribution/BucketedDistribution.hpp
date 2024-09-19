//
// Created by shaoyu on 2023/12/9.
//

#ifndef DATAGENERATOR_BUCKETEDDISTRIBUTION_HPP
#define DATAGENERATOR_BUCKETEDDISTRIBUTION_HPP

#include "../library.hpp"
#include "DegreeDistribution.hpp"

struct Bucket{
    double min_degree, max_degree;
};

class BucketedDistribution : public DegreeDistribution {
public:
    void initialize(Parameter params) override;
    int nextDegree() override;
    virtual void initBuckets(std::vector<Bucket> &buckets, Parameter params) = 0;

protected:
    std::vector<Bucket> buckets;
};


#endif //DATAGENERATOR_BUCKETEDDISTRIBUTION_HPP
