#pragma once

namespace photon {

    struct Vec2f {

        double x;
        double y;

        Vec2f();
        Vec2f(double x, double y);

    };

    struct Vec3f {

        double x;
        double y;
        double z;

        Vec3f();
        Vec3f(double x, double y, double z);

        Vec3f operator+(const Vec3f& other) const;
        Vec3f operator-() const;
        Vec3f operator-(const Vec3f& other) const;
        Vec3f operator*(double s) const;
        Vec3f operator*(const Vec3f& other) const;
        
        Vec3f& operator+=(const Vec3f& other);

        double length() const;
        Vec3f normalize() const;
        double distance(const Vec3f& other) const;
        double dot(const Vec3f& other) const;
        Vec3f cross(const Vec3f& other) const;

    };

    struct Ray {

        Vec3f origin;
        Vec3f direction;

        Ray(const Vec3f& origin, const Vec3f& direction);

        Vec3f point_at(double t) const;

    };

}