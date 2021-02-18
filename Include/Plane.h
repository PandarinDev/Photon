#pragma once

#include "MathUtils.h"
#include "Geometry.h"

#include <optional>

namespace photon {

    struct Plane : Geometry {

        Vec3f normal;

        Plane(
            const Vec3f& position,
            const Vec3f& normal,
            const Material& material);

        std::optional<float> intersect(const Ray& ray) const override;
        Vec3f get_normal_at_point(const Vec3f& point) const override;

    };

}