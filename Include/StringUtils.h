#pragma once

#include <vector>
#include <charconv>
#include <stdexcept>
#include <string_view>

namespace photon {

    struct StringUtils {

        std::vector<std::string_view> split(std::string_view input, std::string_view delimiter = " ") const;
        double to_float(std::string_view str) const;
        std::size_t to_size(std::string_view str) const;

    };

}