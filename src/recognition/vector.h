#pragma once

class Vector {
public:
    Vector() = delete;
    Vector(size_t dimension);
    
    const std::vector<int>& getElements() const;
    size_t getDimension() const;
    void setElement(size_t idx, int value);
    std::string toString() const;


    Vector& operator *=(double scale);
    Vector& operator *=(int scale);
    friend bool operator==(const Vector& lv, const Vector& rv);
    friend bool operator!=(const Vector& lv, const Vector& rv);
    friend Vector operator*(Vector v, double scale);
    friend Vector operator*(Vector v, int scale);
    friend Vector operator*(double scale, Vector v);
    friend Vector operator*(int scale, Vector v);

private:
    size_t dimension_;
    std::vector<int> elements_;
};
