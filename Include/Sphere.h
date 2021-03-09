#pragma once

#include "MathUtils.h"
#include "Geometry.h"

#include <optional>

namespace photon {

    struct Sphere : public Geometry {

        Vec3f position;
        double radius;

        Sphere(const Vec3f& position, double radius, const Material& material);

        std::optional<Intersection> intersect(const Ray& ray) const override;

    };

}