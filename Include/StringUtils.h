#pragma once

#include <vector>
#include <charconv>
#include <stdexcept>
#include <string_view>

namespace photon {

    struct StringUtils {

        std::vector<std::string_view> split(std::string_view input, std::string_view delimiter = " ");
        
        template<typename T>
        T str_to(std::string_view input) {
            T instance;
            if (auto [p, ec] = std::from_chars(input.data(), input.data() + input.size(), instance);
                ec == std::errc::invalid_argument) {
                throw std::runtime_error("Failed to convert string to requested type.");
            }
            return instance;
        }

    };

}