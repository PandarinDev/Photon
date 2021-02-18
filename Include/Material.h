#pragma once

#include "MathUtils.h"
#include "Image.h"

namespace photon {

    struct Material {

        Color color;
        float shininess;

        Material(const Color& color, float shininess);

    };

}