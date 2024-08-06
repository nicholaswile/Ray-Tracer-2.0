#pragma once

#include <stdexcept>
#include <iostream>
#include <cmath> // gives sqrt()
#include <limits> // gives numeric_limits


// 2D Vector class that stores an x- and y-component.
class vector2 {
public:
    float x, y;

    vector2(float x, float y);

    // Binary operators
    vector2 operator+(const vector2 &rhs) const;
    vector2 operator-(const vector2 &rhs) const;
    float operator*(const vector2 &rhs) const;

    // Unary operators
    vector2& operator+=(const vector2 &rhs);
    vector2& operator-=(const vector2 &rhs);
    vector2& operator*=(const float f);
    vector2& operator/=(const float f);

    // Scalar operators
    vector2 operator*(const float f) const;
    vector2 operator/(const float f) const;

    float mag();
    vector2 noramlize();

    // Display
    void print();
};

// 3D vector class that stores an x-, y-, and z-component.
class vector3 {
public:
    float x, y, z;

    vector3(float x, float y, float z);

    // Binary operators
    vector3 operator+(const vector3 &rhs) const;
    vector3 operator-(const vector3 &rhs) const;
    float operator*(const vector3 &rhs) const;
    vector3 operator^(const vector3 &rhs) const;

    // Unary operators
    vector3& operator+=(const vector3 &rhs);
    vector3& operator-=(const vector3 &rhs);
    vector3& operator*=(const float f);
    vector3& operator/=(const float f);

    // Scalar operators
    vector3 operator*(const float f) const;
    vector3 operator/(const float f) const;

    float mag() const;
    vector3 normalize() const;

    // Display
    void print();
};

// Homogeneous vector with four components.
class hvector {
    // TODO
};

// RGBA color that stores red, green, blue, and alpha components. Alpha is 255 by default.
class rgba {
public:
    int r, g, b, a;
    rgba();
    rgba(int r, int g, int b, int a=255);

    // Binary operators
    rgba operator+(const rgba &rhs) const;
    rgba operator-(const rgba &rhs) const;
    rgba operator*(const rgba &rhs) const;

    // Unary operators
    rgba& operator+=(const rgba &rhs);
    rgba& operator-=(const rgba &rhs);
    rgba& operator*=(const rgba &rhs);
    rgba& operator*=(const float f);
    rgba& operator/=(const float f);

    // Scalar operators
    rgba operator*(const float f) const;
    rgba operator/(const float f) const;

    // Display
    void print();
};

// 4x4 matrix for transformations.
class transform {
    // TODO
};

// 2D array of RGBA pixels.
class image {
public:
    int width; 
    int height;
    rgba **buffer;
    image (const int width, const int height);
    ~image();
    void set_pixel(int x, int y, const rgba &color);
    rgba get_pixel(int x, int y);
};

// Ray
class Ray {
public:
    vector3 origin;
    vector3 direction;
    Ray(const vector3 &origin, const vector3 &direction);
};