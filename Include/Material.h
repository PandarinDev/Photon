#pragma once

#include "MathUtils.h"
#include "Image.h"

namespace photon {

    struct Material {

        Color diffuse_color;

        Material(const Color& diffuse_color);

    };

}