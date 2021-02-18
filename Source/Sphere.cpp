#include "Sphere.h"

#include <cmath>

namespace photon {

    Sphere::Sphere(const Vec3f& position, float radius, const Material& material)
        : Geometry(position, material), radius(radius) {}

    std::optional<float> Sphere::intersect(const Ray& ray) const {
        const auto to_center = ray.origin - position;
        // Note: a, b, c as per the variable names regularly
        // used in the quadratic equation. The values here
        // come from algebraicly simplified ray-sphere intersection
        // equation, as explained in "Computer Graphics from Scratch"
        const auto a = ray.direction.dot(ray.direction);
        const auto b = 2.0f * to_center.dot(ray.direction);
        const auto c = to_center.dot(to_center) - radius * radius;
        const auto discriminant = b * b - 4.0f * a * c;
        if (discriminant < 0.0f) {
            return std::nullopt;
        }

        const auto sqrt_d = std::sqrtf(discriminant);
        const auto two_a = 2.0f * a;
        const auto t1 = (-b + sqrt_d) / two_a;
        const auto t2 = (-b - sqrt_d) / two_a;
        const auto t1_valid = is_valid_intersection(t1);
        const auto t2_valid = is_valid_intersection(t2);
        if (t1_valid && t2_valid) return t1 < t2 ? t1 : t2;
        if (t1_valid) return t1;
        if (t2_valid) return t2;
        return std::nullopt;
    }
    
    Vec3f Sphere::get_normal_at_point(const Vec3f& point) const {
        return point - position;
    }

}