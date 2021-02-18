#pragma once

#include "MathUtils.h"
#include "Geometry.h"

#include <optional>

namespace photon {

    struct Sphere : public Geometry {

        float radius;

        Sphere(const Vec3f& position, float radius, const Material& material);

        std::optional<float> intersect(const Ray& ray) const override;
        Vec3f get_normal_at_point(const Vec3f& point) const override;

    };

}