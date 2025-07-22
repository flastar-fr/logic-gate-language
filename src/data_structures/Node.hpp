#pragma once

#include <vector>

struct Node {
    Node() = default;
    explicit Node(const size_t to) : index(to) {}

    size_t index{};
    std::vector<Node> adjacents;
};
