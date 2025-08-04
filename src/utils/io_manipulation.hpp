#pragma once
#include <filesystem>
#include <string>
#include <vector>

bool read_file(const std::filesystem::path& file_path, std::vector<std::string>& result);
