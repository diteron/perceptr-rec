#include "pch.h"
#include "perceptron.h"

Perceptron::Perceptron(size_t classCount, size_t vectorsDimension, unsigned int maxIterationsCount)
    : classCount_(classCount),
    vectorsDimension_(vectorsDimension),
    maxIterationsCount_(maxIterationsCount),
    isLearningConverged_(false),
    sumFunctions_(classCount, SumFunction(vectorsDimension + 1))
{}

void Perceptron::learning(const std::vector<std::vector<Vector>>& dataSet)
{
    assert(dataSet.size() >= classCount_ && "Data set for learning is smaller than class count!");

    bool isOneMoreIteration = true;
    unsigned int iterationsCnt = 0;
    while (isOneMoreIteration && iterationsCnt < maxIterationsCount_) {
        isOneMoreIteration = doOneLearningIteration(dataSet);
        ++iterationsCnt;
    }

    if (iterationsCnt < maxIterationsCount_) {
        isLearningConverged_ = true;
    }
}

bool Perceptron::isLearningConverged() const
{
    return isLearningConverged_;
}

int Perceptron::getVectorClass(const Vector& vector) const
{
    int maxValue = sumFunctions_[0].getVectorValue(vector);
    int bestClass = 0;
    int maxValuesCount = 1;
    for (int i = 1; i < classCount_; i++) {
        int currentValue = sumFunctions_[i].getVectorValue(vector);;
        if (currentValue == maxValue) {
            ++maxValuesCount;
            continue;
        }

        if (currentValue > maxValue) {
            maxValuesCount = 1;
            maxValue = currentValue;
            bestClass = i;
        }
    }

    return maxValuesCount == 1 ? bestClass : -1;
}

const std::vector<SumFunction>& Perceptron::getSumFunctions() const
{
    return sumFunctions_;
}

bool Perceptron::doOneLearningIteration(const std::vector<std::vector<Vector>>& dataSet)
{
    bool isWeightsCorrected = false;
    for (int classIndex = 0; classIndex < classCount_; ++classIndex) {
        for (int vectorIndex = 0; vectorIndex < dataSet[classIndex].size(); ++vectorIndex) {
            if (!isVectorClassCorrect(dataSet[classIndex][vectorIndex], classIndex)) {
                correctFunctionsWeights(dataSet[classIndex][vectorIndex], classIndex);
                isWeightsCorrected = true;
            }
        }
    }

    return isWeightsCorrected;
}

bool Perceptron::isVectorClassCorrect(const Vector& vector, int vectorClass) const
{
    int bestClassForVector = getVectorClass(vector);
    return vectorClass == bestClassForVector;
}

void Perceptron::correctFunctionsWeights(const Vector& vector, int vectorClass)
{
    int workingVectorValue = sumFunctions_[vectorClass].getVectorValue(vector);
    sumFunctions_[vectorClass] += vector;

    for (int i = 0; i < classCount_; ++i) {
        if (i == vectorClass) {
            continue;
        }

        int currentVectorValue = sumFunctions_[i].getVectorValue(vector);
        if (workingVectorValue <= currentVectorValue) {
            sumFunctions_[i] += -1 * vector;
        }
    }
}
