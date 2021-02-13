#pragma once

#include <cstdint>

namespace photon {

    struct Canvas {
        
        std::uint32_t width;
        std::uint32_t height;
        float distance;

        Canvas(std::uint32_t width, std::uint32_t height, float distance) :
            width(width), height(height), distance(distance) {}

    };

}