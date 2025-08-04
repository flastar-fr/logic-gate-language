#pragma once
#include <filesystem>
#include <vector>

class Preprocessor {
public:
    explicit Preprocessor(const std::vector<std::string>& lines, std::filesystem::path include_path);

    std::vector<std::string>& preprocess();
    void remove_comments();
    void process_includes();

private:
    std::vector<std::string> lines;
    std::vector<std::string> included_files;
    std::filesystem::path include_path;
};
