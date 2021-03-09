#include "ModelLoader.h"
#include "StringUtils.h"

#include <tuple>
#include <string>
#include <fstream>
#include <charconv>
#include <stdexcept>

namespace photon {

    std::unique_ptr<Model> ModelLoader::load_model(const std::string& file_path, const Material& material) const {
        std::ifstream file_handle(file_path);
        if (!file_handle) {
            throw std::runtime_error("Failed to open file at '" + file_path + "'.");
        }
        StringUtils string_utils;

        // Read file and parse vertex and face data
        std::string line;
        std::vector<Vec3f> vertices;
        std::vector<std::tuple<std::size_t, std::size_t, std::size_t>> faces;
        while (std::getline(file_handle, line)) {
            const auto parts = string_utils.split(line);
            // Handle vertex lines
            if (parts[0] == "v") {
                vertices.emplace_back(
                    string_utils.to_float(parts[1]),
                    string_utils.to_float(parts[2]),
                    string_utils.to_float(parts[3])
                );
            }
            // Handle face lines
            else if (parts[0] == "f") {
                // Note: The -1 is because indexing in OBJ starts from 1.
                faces.emplace_back(
                    string_utils.to_size(parts[1]) - 1,
                    string_utils.to_size(parts[2]) - 1,
                    string_utils.to_size(parts[3]) - 1
                );
            }
        }

        // Construct geometry from parsed data
        std::vector<Triangle> triangles;
        triangles.reserve(faces.size());
        for (const auto& face : faces) {
            triangles.emplace_back(
                vertices.at(std::get<0>(face)),
                vertices.at(std::get<1>(face)),
                vertices.at(std::get<2>(face)),
                material
            );
        }

        return std::make_unique<Model>(Vec3f(), triangles, material);
    }

}