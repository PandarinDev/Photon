#pragma once

#include "Geometry.h"
#include "Triangle.h"
#include "Sphere.h"

#include <vector>

namespace photon {

    struct Model : Geometry {

        Vec3f position;
        std::vector<Triangle> triangles;
        Sphere bounding_box;

        Model(
            const Vec3f& position,
            const Sphere& bounding_box,
            const std::vector<Triangle>& triangles,
            const Material& material);

        std::optional<Intersection> intersect(const Ray& ray) const override;
        std::optional<Sphere> get_bounding_box() const override;

    };

}