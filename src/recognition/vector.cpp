#include "pch.h"
#include "vector.h"

Vector::Vector(size_t dimension) 
    : dimension_(dimension), elements_(dimension)
{
    for (int& element : elements_) {
        element = 0;
    }
}

const std::vector<int>& Vector::getElements() const
{
    return elements_;
}

size_t Vector::getDimension() const
{
    return dimension_;
}

void Vector::setElement(size_t idx, int value)
{
    assert(idx < dimension_ && "The index is greater than or equal to the size of the vector!");
    elements_[idx] = value;
}

std::string Vector::toString() const
{
    std::string vectorStr = "(";
    for (size_t i = 0; i < elements_.size() - 1; ++i) {
        vectorStr += std::to_string(elements_[i]) + "; ";
    }
    vectorStr.erase(vectorStr.end() - 2, vectorStr.end());
    vectorStr += ")";

    return vectorStr;
}

Vector& Vector::operator*=(double scale)
{
    for (int& element : elements_) {
        int newValue = static_cast<int>(std::round(element * scale));
        element = newValue;
    }
    
    return *this;
}

Vector& Vector::operator*=(int scale)
{
    for (int& element : elements_) {
        element *= scale;
    }

    return *this;
}

bool operator==(const Vector& lv, const Vector& rv)
{
    assert(lv.dimension_ == rv.dimension_ && "Vectors have different dimension!");
    
    for (size_t i = 0; i < lv.dimension_; ++i) {
        if (lv.elements_[i] != rv.elements_[i]) {
            return false;
        }
    }

    return true;
}

bool operator!=(const Vector& lv, const Vector& rv)
{
    return !(lv == rv);
}

Vector operator*(Vector v, double scale)
{
    v *= scale;
    return v;
}

Vector operator*(Vector v, int scale)
{
    v *= scale;
    return v;
}

Vector operator*(double scale, Vector v)
{
    v *= scale;
    return v;
}

Vector operator*(int scale, Vector v)
{
    v *= scale;
    return v;
}
