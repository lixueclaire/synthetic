//
// Created by shaoyu on 2024/1/23.
//

#include "ExponentialSampler.hpp"

void ExponentialSampler::initSampler(double p) {
    prob.clear();
    prob.push_back(1);
    base_prob = p;

}

bool ExponentialSampler::sampling(int x) {
    if (x >= prob.size()) {
        int end = prob.size();
        prob.resize(x);
        for (int i = end; i < prob.size(); i++) {
            prob[i] = prob[i - 1] * base_prob;
        }
    }
    double random = 1.0 * (rand()%100) / 100;
    return (random < prob[x]) || (random < 0.2);
}

