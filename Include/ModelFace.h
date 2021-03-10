#pragma once

#include <array>
#include <cstddef>

namespace photon {

    struct ModelVertex {

        std::size_t vertex;
        std::size_t normal;

        ModelVertex() : vertex(0), normal(0) {}

        ModelVertex(std::size_t vertex, std::size_t normal) :
            vertex(vertex), normal(normal) {}

    };

    struct ModelFace {

        std::array<ModelVertex, 3> vertices;

        ModelFace(const std::array<ModelVertex, 3>& vertices) :
            vertices(vertices) {}

    };

}