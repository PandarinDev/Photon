#pragma once

#include "TypeUtils.h"
#include "MathUtils.h"
#include "Material.h"
#include "Intersection.h"

#include <optional>

namespace photon {

    struct Geometry {

        Material material;

        Geometry(const Material& material);
        virtual ~Geometry() = default;

        virtual std::optional<Intersection> intersect(const Ray& ray) const = 0;

    protected:

        bool is_valid_intersection(float t) const;

    };

}