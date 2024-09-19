//
// Created by shaoyu on 2024/1/23.
//

#ifndef EXPONENTIALSAMPLER_HPP
#define EXPONENTIALSAMPLER_HPP
#include "../library.hpp"
#include "ProbabilitySampler.hpp"


class ExponentialSampler : public ProbabilitySampler {
    void initSampler(double p) override;
    bool sampling(int x) override;
private:
    std::vector<double> prob;
    double base_prob;
};



#endif //EXPONENTIALSAMPLER_HPP
