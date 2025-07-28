#pragma once
#include <unordered_map>
#include <vector>

#include "data_structures/Graph.hpp"
#include "language_processing/Gate.hpp"
#include "language_processing/language_keywords_config.hpp"
#include "language_processing/Token.hpp"

const std::unordered_map<std::string, NodeType> PRIMITIVE_TYPES = {
    {INPUT, NodeType::INPUT},
    {OUTPUT, NodeType::OUTPUT},
    {WIRE, NodeType::WIRE},
};

const std::unordered_map<std::string, bool> BOOLEAN_VALUES = {
    {"1", true},
    {"true", true},
    {"0", false},
    {"false", false}
};

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);

    Graph parse();
    void parse_main();
    void parse_program_block();
    void parse_line();
    void parse_declaration();
    void parse_edge_declaration();
    void parse_assignment();
    void parse_gate();

private:
    std::vector<Token> tokens;
    size_t current_node_id = 0;
    size_t token_index = 0;
    Graph current_graph;
    std::unordered_map<std::string, Gate> gates; // TODO : add N-types and P-types
    std::unordered_map<std::string, size_t> nodes;
};
