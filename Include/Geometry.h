#pragma once

#include "TypeUtils.h"
#include "MathUtils.h"
#include "Material.h"

#include <optional>

namespace photon {

    struct Geometry {

        Vec3f position;
        Material material;

        Geometry(const Vec3f& position, const Material& material);
        virtual ~Geometry() = default;

        virtual std::optional<float> intersect(const Ray& ray) const = 0;
        virtual Vec3f get_normal_at_point(const Vec3f& point) const = 0;

    protected:

        bool is_valid_intersection(float t) const;

    };

}