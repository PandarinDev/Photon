#include "Sphere.h"

#include <cmath>

namespace photon {

    Sphere::Sphere(const Vec3f& position, float radius, const Material& material)
        : position(position), radius(radius), material(material) {}

    std::optional<Pair<float, float>> Sphere::intersect(const Ray& ray) const {
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
        auto t1 = (-b + sqrt_d) / two_a;
        auto t2 = (-b - sqrt_d) / two_a;
        return Pair(t1, t2);
    }

}