#pragma once

#include "Sphere.h"
#include "Light.h"
#include "MathUtils.h"

#include <vector>
#include <memory>

namespace photon {

    struct Scene {

        std::vector<Sphere> spheres;
        std::vector<std::unique_ptr<Light>> lights;

        Scene(const std::vector<Sphere>& spheres, std::vector<std::unique_ptr<Light>>&& lights)
            : spheres(spheres), lights(std::move(lights)) {}

    };

}