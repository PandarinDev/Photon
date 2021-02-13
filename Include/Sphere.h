#pragma once

#include "MathUtils.h"
#include "TypeUtils.h"
#include "Material.h"

#include <optional>

namespace photon {

    struct Sphere {

        Vec3f position;
        float radius;
        Material material;

        Sphere(const Vec3f& position, float radius, const Material& material);

        std::optional<Pair<float, float>> intersect(const Ray& ray) const;

    };

}