#include "Geometry.h"
#include "Sphere.h"

#include <limits>

namespace photon {

    Geometry::Geometry(const Material& material) : material(material) {}

    std::optional<Sphere> Geometry::get_bounding_box() const {
        return std::nullopt;
    }

    bool Geometry::is_valid_intersection(double t) const {
        return t > 0.0f;
    }

}