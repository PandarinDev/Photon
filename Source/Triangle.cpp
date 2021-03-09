#include "Triangle.h"

namespace photon {

    Triangle::Triangle(
        const Vec3f& v0,
        const Vec3f& v1,
        const Vec3f& v2,
        const Material& material)
        : Geometry(material), v0(v0), v1(v1), v2(v2), normal((v1 - v0).cross(v2 - v0)) {}

    std::optional<Intersection> Triangle::intersect(const Ray& ray) const {
        // Compute ray-plane intersection
        const auto denominator = ray.direction.dot(normal);
        if (denominator == 0.0f) {
            return std::nullopt;
        }
        const auto t = (v0 - ray.origin).dot(normal) / denominator;
        if (!is_valid_intersection(t)) {
            return std::nullopt;
        }
        
        const auto p = ray.point_at(t);
        // Do inside-outside checking for triangle edges
        const auto edge0 = v1 - v0;
        const auto edge1 = v2 - v1;
        const auto edge2 = v0 - v2;
        const auto c0 = p - v0;
        const auto c1 = p - v1;
        const auto c2 = p - v2;
        const auto hit =
            normal.dot(edge0.cross(c0)) > 0.0 &&
            normal.dot(edge1.cross(c1)) > 0.0 &&
            normal.dot(edge2.cross(c2)) > 0.0;

        return hit ? std::make_optional<Intersection>(t, normal) : std::nullopt;
    }

}