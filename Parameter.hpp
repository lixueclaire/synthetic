//
// Created by shaoyu on 2023/12/9.
//

#ifndef DATAGENERATOR_PARAMETER_HPP
#define DATAGENERATOR_PARAMETER_HPP

namespace DistributionParam {
    enum DistributionType {
        NoneDistribution = 0,
        FacebookDistribution = 1
    };
}

namespace GeneratorParam {
    enum GeneratorType {
        NoneGenerator = 0,
        DistanceGenerator = 1,
        DistanceHopGenerator = 2,
        RandomGenerator = 3
    };
}
class Parameter {
public:
    int node_num;
    DistributionParam::DistributionType distribution_type;
    GeneratorParam::GeneratorType generator_type;
};

#endif //DATAGENERATOR_PARAMETER_HPP
