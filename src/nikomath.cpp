#include "../headers/nikomath.h"

vector2::vector2(float x, float y) : x(x), y(y) {}

vector2 vector2::operator+(const vector2 &rhs) const {
    return vector2(x+rhs.x, y+rhs.y);
}

vector2 vector2::operator-(const vector2 &rhs) const {
    return vector2(x-rhs.x, y-rhs.y);
}

float vector2::operator*(const vector2 &rhs) const {
    return x * rhs.x + y * rhs.y;
}

vector2& vector2::operator+=(const vector2 &rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

vector2& vector2::operator-=(const vector2 &rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}


vector2& vector2::operator*=(const float f) {
    x *= f;
    y *= f;
    return *this;
}

vector2 &vector2::operator/=(const float f)
{
    if (f == 0) 
        throw std::runtime_error("Cannot divide by zero.\n");
    x /= f;
    y /= f;
    return *this;
}

vector2 vector2::operator*(const float f) const {
    return vector2(x*f, y*f);
}

vector2 vector2::operator/(const float f) const {
    if (f == 0)
        throw std::runtime_error("Cannot divide by zero.\n");
    return vector2(x/f, y/f);
}

float vector2::mag() {
    return sqrt(x*x+y*y);
}

vector2 vector2::noramlize()
{
    return vector2(x, y)/mag();
}

void vector2::print() {
    std::cout << "(" << x << ", " << y << ")\n";
}

vector3::vector3(float x, float y, float z) : x(x), y(y), z(z) {}

// Binary operators
vector3 vector3::operator+(const vector3 &rhs) const {
    return vector3(x+rhs.x, y+rhs.y, z+rhs.z);
}

vector3 vector3::operator-(const vector3 &rhs) const {
    return vector3(x-rhs.x, y-rhs.y, z-rhs.z);
}

float vector3::operator*(const vector3 &rhs) const {
    return x * rhs.x + y * rhs.y + z * rhs.z;
}

vector3 vector3::operator^(const vector3 &rhs) const {
    return vector3(y*rhs.z - rhs.y*z, -(x*rhs.z - rhs.x*z), x*rhs.y - rhs.x*y);
}

// Unary operators
vector3& vector3::operator+=(const vector3 &rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

vector3& vector3::operator-=(const vector3 &rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

vector3& vector3::operator*=(const float f) {
    x *= f;
    y *= f;
    z *= f;
    return *this;
}

vector3& vector3::operator/=(const float f) {
    if (f==0) 
        throw std::runtime_error("Cannot divide by zero.\n");
    x /= f;
    y /= f;
    z /= f;
    return *this;   
}

// Scalar operators
vector3 vector3::operator*(const float f) const {
    return vector3(x*f, y*f, z*f);
}

vector3 vector3::operator/(const float f) const {
    if (f == 0)
        throw std::runtime_error("Cannot divide by zero.\n");

    return vector3(x / f, y / f, z / f);
}

float vector3::mag() {
    return sqrt(x*x+y*y+z*z);
}

vector3 vector3::normalize()
{
    return vector3(x,y,z)/mag();
}

void vector3::print() {
    std::cout << "(" << x << ", " << y << ", " << z << ")\n";
}

rgba::rgba() : r(0), g(0), b(0), a(0) {}

rgba::rgba(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {}

// Binary operators
rgba rgba::operator+(const rgba &rhs) const {
    return rgba(r+rhs.r, g+rhs.g, b+rhs.b, a+rhs.a);
}

rgba rgba::operator-(const rgba &rhs) const {
    return rgba(r-rhs.r, g-rhs.g, b-rhs.b, a-rhs.a);
}

rgba rgba::operator*(const rgba &rhs) const {
    return rgba(r*rhs.r, g*rhs.g, b*rhs.b, a*rhs.a);
}

// Unary operators
rgba& rgba::operator+=(const rgba &rhs) {
    r += rhs.r;
    g += rhs.g;
    b += rhs.b;
    a += rhs.a;
    return *this;
}

rgba& rgba::operator-=(const rgba &rhs) {
    r -= rhs.r;
    g -= rhs.g;
    b -= rhs.b;
    a -= rhs.a;
    return *this;
}

rgba &rgba::operator*=(const rgba &rhs)
{
    r *= rhs.r;
    g *= rhs.g;
    b *= rhs.b;
    a *= rhs.a;
    return *this;
}

rgba& rgba::operator*=(const float f) {
    r *= f;
    g *= f;
    b *= f;
    a *= f;
    return *this;
}

rgba& rgba::operator/=(const float f) {
    if (f==0)
        throw std::runtime_error("Cannot divide by zero.\n");
    r /= f;
    g /= f;
    b /= f;
    a /= f;
    return *this;
}

// Scalar operators
rgba rgba::operator*(const float f) const {
    return rgba(r*f, g*f, b*f, a*f);
}

rgba rgba::operator/(const float f) const {
    if (f==0)
        throw std::runtime_error("Cannot divide by zero.\n");
    return rgba(r/f, g/f, b/f, a/f);
}

void rgba::print() {
    std::cout << "(" << r << ", " << g << ", " << b << ", " << a << ")\n";
}

image::image(const int width, const int height) : width(width), height(height) {
    buffer = new rgba*[height];
    for (int i = 0; i < height; i++)
        buffer[i] = new rgba[width];
}

image::~image()
{
    for (int i = 0; i < height; i++) 
        delete[] buffer[i];
    delete[] buffer;
}

void image::set_pixel(int x, int y, const rgba &color) {
    if (x < 0 || x >= width || y < 0 || y >= height)
        std::runtime_error("Pixel coordinates out of bounds.\n");
    buffer[y][x] = color;
}

rgba image::get_pixel(int x, int y)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
        std::runtime_error("Pixel coordinates out of bounds.\n");
    return buffer[y][x];
}

Ray::Ray(const vector3 &origin, const vector3 &direction) : origin(origin), direction(direction) {}