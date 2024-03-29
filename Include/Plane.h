#pragma once

#include "MathUtils.h"
#include "Geometry.h"

#include <optional>

namespace photon {

    struct Plane : Geometry {

        Vec3f position;
        Vec3f normal;

        Plane(
            const Vec3f& position,
            const Vec3f& normal,
            const Material& material);

        std::optional<Intersection> intersect(const Ray& ray) const override;

    };

}