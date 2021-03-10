#include "Triangle.h"

namespace photon {

    Triangle::Triangle(
        const std::array<Vec3f, 3>& vertices,
        const std::array<Vec3f, 3>& normals,
        const Material& material) :
        Geometry(material), vertices(vertices), normals(normals) {}

    std::optional<Intersection> Triangle::intersect(const Ray& ray) const {
        // Check ray-plane intersection
        const auto v0v1 = vertices[1] - vertices[0];
        const auto v0v2 = vertices[2] - vertices[0];
        const auto pvec = ray.direction.cross(v0v2);
        const auto det = v0v1.dot(pvec);
        if (det < 1e-6) return std::nullopt;

        // Do inside-outside check using polar coordinates
        const auto inv_det = 1.0 / det;
        const auto tvec = ray.origin - vertices[0];
        const auto u = tvec.dot(pvec) * inv_det;
        if (u < 0.0 || u > 1.0) return std::nullopt;

        const auto qvec = tvec.cross(v0v1);
        const auto v = ray.direction.dot(qvec) * inv_det;
        if (v < 0.0 || u + v > 1.0) return std::nullopt;

        // Found the intersection point
        const auto t = v0v2.dot(qvec) * inv_det;

        // Calculate the normal at the intersection using barycentric
        // coordinates. Since u + v + w = 1.0, we can use them as
        // weights for a weighted average of the vertex normals.
        const auto w = 1.0 - u - v;
        const auto normal = Vec3f(
            u * normals[1].x + v * normals[2].x + w * normals[0].x,
            u * normals[1].y + v * normals[2].y + w * normals[0].y,
            u * normals[1].z + v * normals[2].z + w * normals[0].z
        );

        return std::make_optional<Intersection>(t, normal);
    }

}