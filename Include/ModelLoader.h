#pragma once

#include "Model.h"
#include "Material.h"

#include <memory>
#include <string>

namespace photon {

    struct ModelLoader {

        std::unique_ptr<Model> load_model(const std::string& file_path, const Material& material) const;

    };

}