#include "MathUtils.h"

#include <cmath>

namespace photon {

    Vec2f::Vec2f() : x(0.0f), y(0.0f) {}

    Vec2f::Vec2f(float x, float y) : x(x), y(y) {}

    Vec3f::Vec3f() : x(0.0f), y(0.0f), z(0.0f) {}

    Vec3f::Vec3f(float x, float y, float z) : x(x), y(y), z(z) {}

    Vec3f Vec3f::operator+(const Vec3f& other) const {
        return Vec3f(x + other.x, y + other.y, z + other.z);
    }

    Vec3f Vec3f::operator-(const Vec3f& other) const {
        return Vec3f(x - other.x, y - other.y, z - other.z);
    }

    Vec3f Vec3f::operator*(float s) const {
        return Vec3f(x * s, y * s, z * s);
    }

    Vec3f Vec3f::operator*(const Vec3f& other) const {
        return Vec3f(x * other.x, y * other.y, z * other.z);
    }

    Vec3f& Vec3f::operator+=(const Vec3f& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    float Vec3f::length() const {
        return sqrtf(x * x + y * y + z * z);
    }

    Vec3f Vec3f::normalize() const {
        const auto len = length();
        return Vec3f(x / len, y / len, z / len);
    }

    float Vec3f::distance(const Vec3f& other) const {
        return (other - *this).length();
    }

    float Vec3f::dot(const Vec3f& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Ray::Ray(const Vec3f& origin, const Vec3f& direction)
        : origin(origin), direction(direction.normalize()) {}

    Vec3f Ray::point_at(float t) const {
        return origin + direction * t;
    }

}