#pragma once
#include <vector>

#include "CSRNode.hpp"
#include "Graph.hpp"

class CSRGraph {
public:
    explicit CSRGraph(Graph graph);

    void print_graph() const noexcept;
    void process();
    void print_process() const noexcept;
    [[nodiscard]] std::vector<CSRNode>& get_edges() noexcept { return edges; }
    [[nodiscard]] std::vector<size_t>& get_offsets() noexcept { return offsets; }

private:
    std::vector<CSRNode> edges;
    std::vector<size_t> offsets;
    std::vector<CSRNode> csrnodes;
};
