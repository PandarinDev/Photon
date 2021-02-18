#include "Geometry.h"

namespace photon {

    Geometry::Geometry(const Vec3f& position, const Material& material)
        : position(position), material(material) {}

    bool Geometry::is_valid_intersection(float t) const {
        // TODO: Replace 0.0f with the appropriate distance
        return t > 0.0f;
    }

}