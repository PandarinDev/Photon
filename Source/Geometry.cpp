#include "Geometry.h"

#include <limits>

namespace photon {

    Geometry::Geometry(const Material& material) : material(material) {}

    bool Geometry::is_valid_intersection(double t) const {
        return t > 0.0f;
    }

}