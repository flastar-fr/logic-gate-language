#pragma once
#include <iostream>
#include <string>

static void throw_invalid_argument_error(const std::string& message) {
    std::cerr << message << std::endl;
    throw std::invalid_argument(message);
}
