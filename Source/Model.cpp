#include "Model.h"

namespace photon {

    Model::Model(
        const Vec3f& position,
        const std::vector<Triangle>& triangles,
        const Material& material)
        : Geometry(material), position(position), triangles(triangles) {}

    std::optional<Intersection> Model::intersect(const Ray& ray) const {
        std::optional<Intersection> closest_intersection;
        for (const auto& triangle : triangles) {
            const auto intersection = triangle.intersect(ray);
            if (!intersection) {
                continue;
            }
            if (!closest_intersection || intersection->t < closest_intersection->t) {
                closest_intersection = intersection;
            }
        }
        return closest_intersection;
    }

}