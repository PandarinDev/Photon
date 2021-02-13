#pragma once

#include "MathUtils.h"

namespace photon {

    struct Camera {

        Vec3f position;
        // TOOD: Currently not respected
        Vec3f direction;

        Camera(const Vec3f& position, const Vec3f& direction)
            : position(position), direction(direction) {}

    };

}