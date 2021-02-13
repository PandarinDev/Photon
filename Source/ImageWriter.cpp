#include "ImageWriter.h"

#include <fstream>
#include <stdexcept>

namespace photon {

    void ImageWriter::write_image_to_file(const Image& image, const std::string& destination) {
        std::ofstream file_handle(destination);
        if (!file_handle) {
            throw std::runtime_error("Failed to open '" + destination + "' for writing.");
        }
        // Write image header
        file_handle << "P3\n" << image.width << " " << image.height << "\n255";
        std::uint32_t line_counter = 0;
        for (auto i = 0; i < image.pixels.size(); ++i) {
            if (i % image.width == 0) {
                file_handle << "\n";
            }
            const auto& pixel = image.pixels[i];
            file_handle
                << static_cast<unsigned>(pixel.r) << " "
                << static_cast<unsigned>(pixel.g) << " "
                << static_cast<unsigned>(pixel.b) << " ";
        }
    }

}