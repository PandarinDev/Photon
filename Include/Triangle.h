#pragma once

#include "Geometry.h"

namespace photon {

    struct Triangle : Geometry {

        Vec3f v0;
        Vec3f v1;
        Vec3f v2;
        Vec3f normal;

        Triangle(
            const Vec3f& v0,
            const Vec3f& v1,
            const Vec3f& v2,
            const Material& material);

        std::optional<Intersection> intersect(const Ray& ray) const override;

    };

}