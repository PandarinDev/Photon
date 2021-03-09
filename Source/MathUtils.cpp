#include "MathUtils.h"

#include <cmath>

namespace photon {

    Vec2f::Vec2f() : x(0.0f), y(0.0f) {}

    Vec2f::Vec2f(double x, double y) : x(x), y(y) {}

    Vec3f::Vec3f() : x(0.0f), y(0.0f), z(0.0f) {}

    Vec3f::Vec3f(double x, double y, double z) : x(x), y(y), z(z) {}

    Vec3f Vec3f::operator+(const Vec3f& other) const {
        return Vec3f(x + other.x, y + other.y, z + other.z);
    }

    Vec3f Vec3f::operator-() const {
        return Vec3f(-x, -y, -z);
    }

    Vec3f Vec3f::operator-(const Vec3f& other) const {
        return Vec3f(x - other.x, y - other.y, z - other.z);
    }

    Vec3f Vec3f::operator*(double s) const {
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

    double Vec3f::length() const {
        return sqrt(x * x + y * y + z * z);
    }

    Vec3f Vec3f::normalize() const {
        const auto len = length();
        return Vec3f(x / len, y / len, z / len);
    }

    double Vec3f::distance(const Vec3f& other) const {
        return (other - *this).length();
    }

    double Vec3f::dot(const Vec3f& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vec3f Vec3f::cross(const Vec3f& other) const {
        return Vec3f(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    Ray::Ray(const Vec3f& origin, const Vec3f& direction)
        : origin(origin), direction(direction.normalize()) {}

    Vec3f Ray::point_at(double t) const {
        return origin + direction * t;
    }

}
