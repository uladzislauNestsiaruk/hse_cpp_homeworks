#include "unixpath.h"

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::string result_path;
    std::string processing_part;
    for (char character : current_working_dir) {
        result_path += character;
    }
    auto go_to_parent_directory = [&]() {
        while (!result_path.empty() && result_path.back() != '/') {
            result_path.pop_back();
        }
        if (result_path.size() > 1) {
            result_path.pop_back();
        }
    };
    for (size_t i = 0; i < path.size(); ++i) {
        if (path[i] == '/') {
            continue;
        }
        while (i < path.size() && path[i] != '/') {
            processing_part += path[i];
            ++i;
        }
        if (processing_part == "..") {
            go_to_parent_directory();
        } else if (processing_part != ".") {
            if (result_path.back() != '/' && !processing_part.empty()) {
                result_path += "/";
            }
            result_path += processing_part;
        }
        processing_part = "";
    }
    return result_path;
}
