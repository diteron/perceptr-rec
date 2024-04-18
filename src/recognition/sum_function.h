#pragma once

#include "vector.h"

class SumFunction {
public:
    SumFunction() = delete;
    SumFunction(size_t weightsCount);
    
    std::vector<int>& getWeights();
    void setWeight(size_t idx, int value);
    int getVectorValue(const Vector& vector) const;
    std::string toString(size_t funNum = 0) const;

    SumFunction& operator +=(const Vector& v);
    friend SumFunction operator+(SumFunction sfun, const Vector& v);
    friend SumFunction operator+(const Vector& v, SumFunction sfun);

private:
    size_t weightsCount_;
    std::vector<int> weights_;
};

