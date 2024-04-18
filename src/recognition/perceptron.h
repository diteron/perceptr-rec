#pragma once

#include "sum_function.h"

class Perceptron {
public:
    Perceptron() = delete;
    Perceptron(size_t classCount, size_t vectorsDimension, unsigned int maxIterationsCount);
    
    void learning(const std::vector<std::vector<Vector>>& dataSet);
    bool isLearningConverged() const;
    int getVectorClass(const Vector& vector) const;

    const std::vector<SumFunction>& getSumFunctions() const;

private:
    bool doOneLearningIteration(const std::vector<std::vector<Vector>>& dataSet);
    bool isVectorClassCorrect(const Vector& vector, int vectorClass) const;
    void correctFunctionsWeights(const Vector& vector, int vectorClass);

    size_t classCount_;
    size_t vectorsDimension_;
    const unsigned int maxIterationsCount_;
    bool isLearningConverged_;

    std::vector<SumFunction> sumFunctions_;
};

