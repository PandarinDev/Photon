#pragma once

#include "Geometry.h"
#include "Triangle.h"

#include <vector>

namespace photon {

    struct Model : Geometry {

        Vec3f position;
        std::vector<Triangle> triangles;

        Model(
            const Vec3f& position,
            const std::vector<Triangle>& triangles,
            const Material& material);

        std::optional<Intersection> intersect(const Ray& ray) const override;

    };

}