#include "Geometry.h"

namespace photon {

    Geometry::Geometry(const Material& material) : material(material) {}

    bool Geometry::is_valid_intersection(float t) const {
        // TODO: Replace 0.0f with the appropriate distance
        return t > 0.0f;
    }

}