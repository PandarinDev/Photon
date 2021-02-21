#include "Plane.h"

namespace photon {

    Plane::Plane(
        const Vec3f& position,
        const Vec3f& normal,
        const Material& material)
        : Geometry(material), position(position), normal(normal) {}

    std::optional<Intersection> Plane::intersect(const Ray& ray) const {
        const auto denominator = ray.direction.dot(normal);
        if (denominator == 0.0f) {
            return std::nullopt;
        }
        const auto t = (position - ray.origin).dot(normal) / denominator;
        return is_valid_intersection(t)
            ? std::make_optional<Intersection>(t, normal)
            : std::nullopt;
    }

}