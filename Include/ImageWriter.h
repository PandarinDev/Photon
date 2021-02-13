#pragma once

#include "Image.h"

#include <string>

namespace photon {

    struct ImageWriter {

        void write_image_to_file(const Image& image, const std::string& destination);

    };

}