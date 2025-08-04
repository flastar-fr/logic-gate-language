#include "Preprocessor.hpp"

#include "language_processing/language_keywords_config.hpp"
#include "utils/io_manipulation.hpp"

Preprocessor::Preprocessor(const std::vector<std::string>& lines, std::filesystem::path include_path) : lines(lines),
    include_path(std::move(include_path)) {}

std::vector<std::string>& Preprocessor::preprocess() {
    remove_comments();
    process_includes();

    return lines;
}

void Preprocessor::remove_comments() {
    for (auto& line : lines) {
        const auto comment_index = line.find_first_of(COMMENT_PREFIX);
        if (comment_index != std::string::npos) {
            line = line.substr(0, comment_index);
        }
    }
}

void Preprocessor::process_includes() {
    // TODO : to implement
}
