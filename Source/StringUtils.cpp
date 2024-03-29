#include "StringUtils.h"

#include <cstdlib>

namespace photon {

    std::vector<std::string_view> StringUtils::split(std::string_view input, std::string_view delimiter) const {
        std::vector<std::string_view> result;
        std::size_t position = 0;
        while (position < input.size()) {
            const auto match_position = input.find_first_of(delimiter, position);
            // Do not put empty strings into the result
            if (position != match_position) {
                result.emplace_back(input.substr(position, match_position - position));
            }
            // Note: Important to check after emplacing, otherwise last entry won't be added
            if (match_position == std::string_view::npos) {
                break;
            }
            position = match_position + 1;
        }
        return result;
    }

    double StringUtils::to_float(std::string_view str) const {
        char* end_ptr = const_cast<char*>(str.data() + str.size());
        return std::strtod(str.data(), &end_ptr);
    }

    size_t StringUtils::to_size(std::string_view str) const {
        char* end_ptr = const_cast<char*>(str.data() + str.size());
        return std::strtoull(str.data(), &end_ptr, 10);
    }

}