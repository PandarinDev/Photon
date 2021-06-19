#pragma once

#include "TypeUtils.h"
#include "MathUtils.h"
#include "Material.h"
#include "Intersection.h"

#include <optional>

namespace photon {

    struct Sphere;

    struct Geometry {

        Material material;

        Geometry(const Material& material);
        virtual ~Geometry() = default;

        virtual std::optional<Intersection> intersect(const Ray& ray) const = 0;
        virtual std::optional<Sphere> get_bounding_box() const;

    protected:

        bool is_valid_intersection(double t) const;

    };

}