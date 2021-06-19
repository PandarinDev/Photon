#include "Model.h"

namespace photon {

    Model::Model(
        const Vec3f& position,
        const Sphere& bounding_box,
        const std::vector<Triangle>& triangles,
        const Material& material)
        : Geometry(material), position(position),
          bounding_box(bounding_box), triangles(triangles) {}

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

    std::optional<Sphere> Model::get_bounding_box() const {
        return bounding_box;
    }

}
