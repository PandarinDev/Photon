#pragma once

#include "MathUtils.h"
#include "Image.h"

namespace photon {

    struct Material {

        Color color;
        double shininess;

        Material(const Color& color, double shininess);

    };

}