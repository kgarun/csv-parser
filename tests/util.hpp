//
// Created by arun-8593 on 25/10/21.
//

#ifndef CSV_UTIL_HPP
#define CSV_UTIL_HPP

#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY (x)

inline std::vector<std::string> SplitString (std::string_view string, char delim) {
    std::vector<std::string> substrings{ "" };

    for (char c : string) {
        if (c == delim)
            substrings.emplace_back ("");
        else
            substrings.back () += c;
    }

    return substrings;
}

inline std::string GetAbsolutePath (std::string_view file_path) {
    const char *root                   = TOSTRING (CSV_PARSER_ROOT);
    auto abs_path                      = std::filesystem::path (root);
    std::vector<std::string> sub_paths = SplitString (file_path, '/');
    for (const auto &path : sub_paths) abs_path.append (path);
    return abs_path.string ();
}

#endif // CSV_UTIL_HPP
