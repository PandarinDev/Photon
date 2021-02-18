#pragma once

namespace photon {

    struct Vec2f {

        float x;
        float y;

        Vec2f();
        Vec2f(float x, float y);

    };

    struct Vec3f {

        float x;
        float y;
        float z;

        Vec3f();
        Vec3f(float x, float y, float z);

        Vec3f operator+(const Vec3f& other) const;
        Vec3f operator-() const;
        Vec3f operator-(const Vec3f& other) const;
        Vec3f operator*(float s) const;
        Vec3f operator*(const Vec3f& other) const;
        
        Vec3f& operator+=(const Vec3f& other);

        float length() const;
        Vec3f normalize() const;
        float distance(const Vec3f& other) const;
        float dot(const Vec3f& other) const;

    };

    struct Ray {

        Vec3f origin;
        Vec3f direction;

        Ray(const Vec3f& origin, const Vec3f& direction);

        Vec3f point_at(float t) const;

    };

}