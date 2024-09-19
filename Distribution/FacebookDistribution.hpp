//
// Created by shaoyu on 2023/12/9.
//

#ifndef DATAGENERATOR_FACEBOOKDISTRIBUTION_HPP
#define DATAGENERATOR_FACEBOOKDISTRIBUTION_HPP

#include "BucketedDistribution.hpp"

class FacebookDistribution : public BucketedDistribution {
public:
    void initBuckets(std::vector<Bucket> &buckets, Parameter params) override;
private:
    int mean = 0;
    const int FB_MEAN = 190;
    static double calcMean(int node_num);
    void loadFacebookBuckets();
    void rebuildBuckets();
};


#endif //DATAGENERATOR_FACEBOOKDISTRIBUTION_HPP
