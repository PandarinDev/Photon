#pragma once

#include "MathUtils.h"

namespace photon {

    struct Intersection {

        float t;
        Vec3f normal;

        Intersection(float t, const Vec3f& normal)
            : t(t), normal(normal) {}

    };

}