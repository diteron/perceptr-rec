#include "pch.h"
#include "sum_function.h"

SumFunction::SumFunction(size_t weightsCount)
    : weightsCount_(weightsCount), weights_(weightsCount, 0)
{}

std::vector<int>& SumFunction::getWeights()
{
    return weights_;
}

void SumFunction::setWeight(size_t idx, int value)
{
    assert(idx < weightsCount_ 
           && "The index is greater than or equal to the size of the weights vector!");

    weights_[idx] = value;
}

int SumFunction::getVectorValue(const Vector& vector) const
{
    assert(vector.getDimension() == weightsCount_
           && "The dimension of vector is not equal to the dimension of the weights vector!");
    
    int vectorValue = 0;
    const std::vector<int>& vectorElements = vector.getElements();
    for (size_t i = 0; i < vector.getDimension(); ++i) {
        vectorValue += vectorElements[i] * weights_[i];
    }

    return vectorValue;
}

std::string SumFunction::toString(size_t funNum) const
{
    std::string functionStr = "d(" + std::to_string(funNum) + ") = " + std::to_string(weights_[0]) + "x1";
    
    for (size_t i = 1; i < weightsCount_; ++i) {
        if (weights_[i] >= 0) {
            functionStr += " + " + std::to_string(weights_[i]);
        }
        else {
            functionStr += " - " + std::to_string(-weights_[i]);
        }
        functionStr += "x" + std::to_string(i + 1);
    }
    functionStr.erase(functionStr.end() - 2, functionStr.end());

    return functionStr;
}

SumFunction& SumFunction::operator+=(const Vector& v)
{
    assert(v.getDimension() == weightsCount_
           && "The dimension of vector is not equal to the dimension of the weights vector!");
    
    for (size_t i = 0; i < weightsCount_; ++i) {
        weights_[i] += v.getElements()[i];
    }

    return *this;
}

SumFunction operator+(SumFunction sfun, const Vector& v)
{
    sfun += v;
    return sfun;
}

SumFunction operator+(const Vector& v, SumFunction sfun)
{
    sfun += v;
    return sfun;
}
