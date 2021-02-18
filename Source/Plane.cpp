#include "Plane.h"

namespace photon {

    Plane::Plane(
        const Vec3f& position,
        const Vec3f& normal,
        const Material& material)
        : Geometry(position, material), normal(normal) {}

    std::optional<float> Plane::intersect(const Ray& ray) const {
        const auto denominator = ray.direction.dot(normal);
        if (denominator == 0.0f) {
            return std::nullopt;
        }
        const auto t = (position - ray.origin).dot(normal) / denominator;
        return is_valid_intersection(t) ? std::optional(t) : std::nullopt;
    }

    Vec3f Plane::get_normal_at_point(const Vec3f& point) const {
        return normal;
    }

}