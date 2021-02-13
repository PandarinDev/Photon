#pragma once

#include <vector>
#include <cstdint>

namespace photon {

    struct Color {

        std::uint8_t r;
        std::uint8_t g;
        std::uint8_t b;

        Color() : r(0), g(0), b(0) {}

        Color(std::uint8_t r, std::uint8_t g, std::uint8_t b)
            : r(r), g(g), b(b) {}

    };

    using ImagePixel = Color;

    struct Image {

        std::uint32_t width;
        std::uint32_t height;
        std::vector<ImagePixel> pixels;

        Image(std::uint32_t width, std::uint32_t height, const std::vector<ImagePixel>& pixels) :
            width(width), height(height), pixels(pixels) {}

    };

}