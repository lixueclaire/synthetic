//
// Created by shaoyu on 2023/12/9.
//

#ifndef DATAGENERATOR_DEGREEDISTRIBUTION_HPP
#define DATAGENERATOR_DEGREEDISTRIBUTION_HPP

#include "../Parameter.hpp"

class DegreeDistribution {
public:
    virtual void initialize(Parameter params) = 0;
    virtual int nextDegree() = 0;

    void reset(int s);
private:
    int seed = 0;
};


#endif //DATAGENERATOR_DEGREEDISTRIBUTION_HPP
