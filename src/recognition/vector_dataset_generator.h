#pragma once

#include "vector.h"

class VectorDataSetGenerator {
public:
    VectorDataSetGenerator() = delete;
    VectorDataSetGenerator(int minVectorValue_, int maxVectorValue_);

    void setVectorsValuesRange(int minVal, int maxVal);
    const std::vector<std::vector<Vector>>& generateDataSet(size_t classCount, size_t vectorsCountForClass,
                                                            size_t vectorsDimension);

private:
    bool isEnoughRandomVectors(size_t classCount, size_t vectorsCountForClass,
                               size_t vectorsDimension) const;
    bool isSameVectorGenerated(const Vector& newVector, const std::vector<Vector>& generatedVectors) const;

    int minVectorValue_;
    int maxVectorValue_;
    std::vector<std::vector<Vector>> dataSet_;

    std::random_device rdseed_;
    std::mt19937 random_;
    std::uniform_int_distribution<> distribution_;
};
