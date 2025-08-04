#include "Preprocessor.hpp"

#include "language_processing/language_keywords_config.hpp"
#include "utils/error_messages.hpp"
#include "utils/io_manipulation.hpp"

std::string extract_file_name(const std::string& line) {
    bool is_string = false;
    std::string file_name;
    for (const auto char_path : line) {
        if (is_string && char_path != '"') file_name += char_path;
        if (char_path == '"') is_string = !is_string;
    }

    if (is_string || file_name.empty()) {
        throw_invalid_argument_error("Invalid string path");
    }

    return file_name;
}

Preprocessor::Preprocessor(const std::vector<std::string>& lines, const std::filesystem::path& include_path,
                           const std::filesystem::path& main_file) : lines(lines), include_path(include_path),
                                                              main_file(main_file) {
    included_files.insert(include_path / main_file);
}

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
    bool has_include = true;

    while (has_include) {
        has_include = false;
        std::vector<std::string> new_lines;

        for (const auto& line : lines) {
            const size_t include_length = INCLUDE.length() + 1;

            if (line.size() >= include_length &&
                line[0] == PREPROCESSOR_CHAR &&
                line.substr(1, include_length - 1) == INCLUDE) {
                if (process_include(line, new_lines)) {
                    has_include = true;
                }
            } else {
                new_lines.push_back(line);
            }
        }

        lines = std::move(new_lines);
    }
}

bool Preprocessor::process_include(const std::string& include_line, std::vector<std::string>& processed_lines) {
    const auto file_name = extract_file_name(include_line);
    const std::filesystem::path complete_path = include_path / file_name;
    if (included_files.count(complete_path)) return false;

    std::vector<std::string> included_lines;
    const bool is_open = read_file(complete_path, included_lines);
    if (!is_open) throw_invalid_argument_error("File cannot be opened");

    processed_lines.insert(processed_lines.end(), included_lines.begin(), included_lines.end());
    included_files.insert(complete_path);
    return true;
}
