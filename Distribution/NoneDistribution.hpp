//
// Created by 13183 on 2024/1/27.
//

#ifndef DATAGENERATOR_NONEDISTRIBUTION_H
#define DATAGENERATOR_NONEDISTRIBUTION_H

#include "../library.hpp"
#include "DegreeDistribution.hpp"

class NoneDistribution : public DegreeDistribution{
public:
    void initialize(Parameter params) override;
    int nextDegree() override;
};


#endif //DATAGENERATOR_NONEDISTRIBUTION_H
