#pragma once

#include "Geometry.h"
#include "Light.h"
#include "MathUtils.h"

#include <vector>
#include <memory>

namespace photon {

    struct Scene {

        std::vector<std::unique_ptr<Geometry>> geometry;
        std::vector<std::unique_ptr<Light>> lights;

        Scene(
            std::vector<std::unique_ptr<Geometry>>&& geometry,
            std::vector<std::unique_ptr<Light>>&& lights)
            : geometry(std::move(geometry)), lights(std::move(lights)) {}

    };

}