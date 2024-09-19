cmake_minimum_required(VERSION 3.25)
project(DataGenerator)

set(CMAKE_CXX_STANDARD 17)

add_executable(DataGenerator main.cpp
        Components/Node.cpp
        Components/Node.hpp
        library.cpp
        library.hpp
        Parameter.cpp
        Parameter.hpp
        Distribution/DegreeDistribution.cpp
        Distribution/DegreeDistribution.hpp
        Distribution/BucketedDistribution.cpp
        Distribution/BucketedDistribution.hpp
        Distribution/FacebookDistribution.cpp
        Distribution/FacebookDistribution.hpp
        Components/Graph.cpp Components/Graph.hpp
        Generator/EdgesGenerator.cpp
        Generator/EdgesGenerator.hpp
        Generator/DistanceEdgesGenerator.cpp
        Generator/DistanceEdgesGenerator.hpp
        Generator/RandomEdgesGenerator.cpp
        Generator/RandomEdgesGenerator.hpp
        Generator/ProbabilitySampler.cpp
        Generator/ProbabilitySampler.hpp
        Generator/ExponentialSampler.cpp
        Generator/ExponentialSampler.hpp
        Generator/DistanceHopGenerator.cpp
        Generator/DistanceHopGenerator.hpp
        Distribution/NoneDistribution.hpp
        Distribution/NoneDistribution.cpp
        Components/Louvian.cpp
        Components/Louvian.h
        Components/Group.cpp Components/Group.hpp)
