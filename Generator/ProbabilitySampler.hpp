//
// Created by shaoyu on 2024/1/23.
//

#ifndef PROBABILITYSAMPLER_HPP
#define PROBABILITYSAMPLER_HPP



class ProbabilitySampler {
public:
    virtual void initSampler(double p) = 0;
    virtual bool sampling(int x) = 0;
};



#endif //PROBABILITYSAMPLER_HPP
