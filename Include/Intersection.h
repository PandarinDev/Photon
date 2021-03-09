#pragma once

#include "MathUtils.h"

namespace photon {

    struct Intersection {

        double t;
        Vec3f normal;

        Intersection(double t, const Vec3f& normal)
            : t(t), normal(normal) {}

    };

}