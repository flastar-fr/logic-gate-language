#pragma once
#include <unordered_map>
#include <vector>

#include "data_structures/Graph.hpp"
#include "language_processing/default_gates.hpp"
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
    void parse_edge_declaration(const Node& node_left);
    void parse_assignment(Node& node);
    Node& parse_identifier();
    Node& parse_identifier_gate();
    void parse_gate();
    void declare_primitive(const std::string& node_type_s);
    void declare_gate(const std::string& node_type_s);

private:
    std::vector<Token> tokens;
    size_t current_node_id = 0;
    size_t token_index = 0;
    Graph current_graph;
    std::unordered_map<std::string, Gate> gates = DEFAULT_GATES;
    std::unordered_map<std::string, Gate> gates_identifier;
    std::unordered_map<std::string, size_t> nodes;
};
