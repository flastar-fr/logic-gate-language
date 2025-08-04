#pragma once
#include <filesystem>
#include <unordered_set>
#include <vector>

class Preprocessor {
public:
    explicit Preprocessor(const std::vector<std::string>& lines, const std::filesystem::path& include_path, const std::filesystem::path& main_file);

    std::vector<std::string>& preprocess();
    void remove_comments();
    void process_includes();
    bool process_include(const std::string& include_line, std::vector<std::string>& processed_lines);

private:
    std::vector<std::string> lines;
    std::unordered_set<std::filesystem::path> included_files;
    std::filesystem::path include_path;
    std::filesystem::path main_file;
};
