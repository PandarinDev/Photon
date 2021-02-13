#pragma once

#include "MathUtils.h"

namespace photon {

    enum class LightType {
        POINT,
        DIRECTIONAL,
        AMBIENT
    };

    struct Light {

        LightType type;
        Vec3f intensity;

        Light(LightType type, Vec3f intensity)
            : type(type), intensity(intensity) {}

    };

    struct PointLight : Light {

        Vec3f position;

        PointLight(Vec3f position, Vec3f intensity)
            : Light(LightType::POINT, intensity), position(position) {}

    };

    struct DirectionalLight : Light {

        Vec3f direction;

        DirectionalLight(Vec3f direction, Vec3f intensity)
            : Light(LightType::DIRECTIONAL, intensity), direction(direction) {}

    };

    struct AmbientLight : Light {

        AmbientLight(Vec3f intensity)
            : Light(LightType::AMBIENT, intensity) {}

    };

}