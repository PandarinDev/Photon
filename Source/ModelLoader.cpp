#include "ModelLoader.h"
#include "ModelFace.h"
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
        std::vector<Vec3f> normals;
        std::vector<ModelFace> faces;
        std::optional<std::pair<double, Vec3f>> furthest_vertex;
        while (std::getline(file_handle, line)) {
            const auto parts = string_utils.split(line);
            // Handle vertex lines
            if (parts[0] == "v") {
                Vec3f vertex(
                    string_utils.to_float(parts[1]),
                    string_utils.to_float(parts[2]),
                    string_utils.to_float(parts[3]));
                // Store the furthest vertex for bounding box building
                const auto vertex_distance = vertex.length();
                if (!furthest_vertex || furthest_vertex->first < vertex_distance) {
                    furthest_vertex = std::make_pair(vertex_distance, vertex);
                }
                vertices.emplace_back(vertex);
            }
            // Handle normal lines
            else if (parts[0] == "vn") {
                normals.emplace_back(
                    string_utils.to_float(parts[1]),
                    string_utils.to_float(parts[2]),
                    string_utils.to_float(parts[3])
                );
            }
            // Handle face lines
            else if (parts[0] == "f") {
                // Note: The -1 is because indexing in OBJ starts from 1.
                std::vector<std::vector<std::string_view>> parts_split;
                for (std::size_t i = 1; i <= 3; ++i) {
                    parts_split.emplace_back(string_utils.split(parts[i], "/"));
                }

                std::array<ModelVertex, 3> model_vertices;
                for (std::size_t i = 0; i < model_vertices.size(); ++i) {
                    const auto& part = parts_split[i];
                    model_vertices[i] = ModelVertex(
                        string_utils.to_size(part[0]) - 1,
                        string_utils.to_size(part[1]) - 1
                    );
                }
                faces.emplace_back(model_vertices);
            }
        }

        // Construct geometry from parsed data
        std::vector<Triangle> triangles;
        triangles.reserve(faces.size());
        for (const auto& face : faces) {
            std::array<Vec3f, 3> triangle_vertices = {
                vertices[face.vertices[0].vertex],
                vertices[face.vertices[1].vertex],
                vertices[face.vertices[2].vertex]
            };
            std::array<Vec3f, 3> triangle_normals = {
                normals[face.vertices[0].normal],
                normals[face.vertices[1].normal],
                normals[face.vertices[2].normal]
            };
            triangles.emplace_back(
                triangle_vertices,
                triangle_normals,
                material
            );
        }

        return std::make_unique<Model>(Vec3f(), Sphere(Vec3f(), furthest_vertex->first, material), triangles, material);
    }

}