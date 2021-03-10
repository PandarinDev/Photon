#pragma once

#include "Geometry.h"

#include <array>

namespace photon {

    struct Triangle : Geometry {

        std::array<Vec3f, 3> vertices;
        std::array<Vec3f, 3> normals;

        Triangle(
            const std::array<Vec3f, 3>& vertices,
            const std::array<Vec3f, 3>& normals,
            const Material& material);

        std::optional<Intersection> intersect(const Ray& ray) const override;

    };

}