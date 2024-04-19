#include "pch.h"
#include "vector_dataset_generator.h"

VectorDataSetGenerator::VectorDataSetGenerator(int minVectorValue_, int maxVectorValue_)
    : minVectorValue_(minVectorValue_),
    maxVectorValue_(maxVectorValue_),
    dataSet_(),
    rdseed_(),
    random_(rdseed_()),
    distribution_(minVectorValue_, maxVectorValue_)
{}

void VectorDataSetGenerator::setVectorsValuesRange(int minVal, int maxVal)
{
    minVectorValue_ = minVal;
    maxVectorValue_ = maxVal;

    using uni_int_distr_param = std::uniform_int_distribution<int>::param_type;
    distribution_.param(uni_int_distr_param(minVal, maxVal));
}

const std::vector<std::vector<Vector>>&
VectorDataSetGenerator::generateDataSet(size_t classCount, size_t vectorsCountForClass,
                                        size_t vectorsDimension)
{
    if (!isEnoughRandomVectors(classCount, vectorsCountForClass, vectorsDimension)) {
        return dataSet_;
    }

    std::vector<Vector> generatedVectors;
    dataSet_ = std::vector<std::vector<Vector>>(classCount,
                                                std::vector<Vector>(vectorsCountForClass, Vector(vectorsDimension + 1)));
    for (size_t classIdx = 0; classIdx < classCount; ++classIdx) {
        for (size_t vectorIdx = 0; vectorIdx < vectorsCountForClass; ++vectorIdx) {
            for (size_t elemIdx = 0; elemIdx < vectorsDimension; ++elemIdx) {
                dataSet_[classIdx][vectorIdx].setElement(elemIdx, distribution_(random_));
            }
            dataSet_[classIdx][vectorIdx].setElement(vectorsDimension, 1);

            if (isSameVectorGenerated(dataSet_[classIdx][vectorIdx], generatedVectors)) {
                --vectorIdx;    // Generate a new vector at the same index in the next iteration
            }
            else {
                generatedVectors.push_back(dataSet_[classIdx][vectorIdx]);
            }
        }
    }

    return dataSet_;
}

bool VectorDataSetGenerator::isEnoughRandomVectors(size_t classCount, size_t vectorsCountForClass, size_t vectorsDimension) const
{
    assert(maxVectorValue_ > minVectorValue_ && "Min value for vector is larger than max value!");

    int maxRandomVectors = maxVectorValue_ - minVectorValue_ + 1;
    return (classCount * vectorsCountForClass <= std::pow(maxRandomVectors, vectorsDimension));
}

bool VectorDataSetGenerator::isSameVectorGenerated(const Vector& newVector, const std::vector<Vector>& generatedVectors) const
{
    for (const auto& generatedVector : generatedVectors) {
        if (newVector == generatedVector) {
            return true;
        }
    }

    return false;
}
