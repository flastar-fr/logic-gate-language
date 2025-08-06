#include "Parser.hpp"

#include "data_structures/CSRGraph.hpp"
#include "language_processing/language_keywords_config.hpp"
#include "language_processing/token_manipulation/token_verification.hpp"
#include "utils/error_messages.hpp"

void remap_node_indexes(Node& node, const std::unordered_map<size_t, size_t>& index_map) {
    node.index = index_map.at(node.index);
    for (auto& neighbor : node.neighbors) {
        neighbor = index_map.at(neighbor);
    }
    for (auto& predecessor : node.predecessors) {
        predecessor = index_map.at(predecessor);
    }
}

void register_io(Gate& gate, Node& node, size_t& current_input, size_t& current_output,
                 const std::unordered_map<size_t, size_t>& index_map) {
    if (node.node_type == NodeType::INPUT) {
        node.node_type = NodeType::WIRE;
        gate.inputs[gate.inputs_order[current_input++]] = index_map.at(node.index);
    }
    if (node.node_type == NodeType::OUTPUT) {
        node.node_type = NodeType::WIRE;
        gate.outputs[gate.outputs_order[current_output++]] = index_map.at(node.index);
    }
}

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), current_graph({}) {}

Graph Parser::parse() {
    for (; token_index < tokens.size(); ++token_index) {
        if (is_identifier(tokens[token_index], MAIN)) {
            parse_main();
        }
        if (is_identifier(tokens[token_index], GATE)) {
            parse_gate();
        }
    }

    return current_graph;
}

void Parser::parse_main() {
    verify_token_identifier(tokens[token_index++], MAIN);
    verify_token_type(tokens[token_index], TokenType::LEFT_BRACE);

    parse_program_block();
}

void Parser::parse_program_block() {
    verify_token_type(tokens[token_index++], TokenType::LEFT_BRACE);
    for (; !is_node_type(tokens[token_index], TokenType::RIGHT_BRACE) && token_index < tokens.size(); ++token_index) {
        parse_line();
    }

    verify_token_type(tokens[token_index], TokenType::RIGHT_BRACE);
}

void Parser::parse_line() {
    verify_token_type(tokens[token_index], TokenType::IDENTIFIER);
    const auto token_value = tokens[token_index].value;
    if (PRIMITIVE_TYPES.count(token_value) || gates.count(token_value)) {
        parse_declaration();
        verify_token_type(tokens[token_index], TokenType::SEMICOLON);
        return;
    }

    auto& node = parse_identifier();
    switch (tokens[token_index].type) {
        case TokenType::RIGHT_ARROW: {
            parse_edge_declaration(node);
            break;
        }
        case TokenType::EQUAL: {
            parse_assignment(node);
            break;
        }
        default: {
            throw_invalid_argument_error("Uknown operator type " + tostring(tokens[token_index].type));
        }
    }

    verify_token_type(tokens[token_index], TokenType::SEMICOLON);
}

void Parser::parse_declaration() {
    verify_token_type(tokens[token_index], TokenType::IDENTIFIER);
    const auto node_type_s = tokens[token_index++].value;
    if (PRIMITIVE_TYPES.count(node_type_s)) {
        declare_primitive(node_type_s);
    }
    if (gates.count(node_type_s)) {
        declare_gate(node_type_s);
    }

    auto& last_node = current_graph[nodes[tokens[token_index - 1].value]];
    verify_if_declaration_ended(last_node);

    verify_token_type(tokens[token_index], TokenType::SEMICOLON);
}

void Parser::verify_if_declaration_ended(Node& last_node) {
    switch (tokens[token_index].type) {
        case TokenType::RIGHT_ARROW: {
            parse_edge_declaration(last_node);
            break;
        }
        case TokenType::EQUAL: {
            parse_assignment(last_node);
            break;
        }
        case TokenType::SEMICOLON: break;
        default: {
            throw_invalid_argument_error("Invalid node type " + tostring(tokens[token_index].type));
        }
    }
}

void Parser::parse_edge_declaration(const Node& node_left) {
    verify_token_type(tokens[token_index++], TokenType::RIGHT_ARROW);

    const auto& node_right = parse_identifier();

    current_graph.add_edge(node_left, node_right);

    verify_token_type(tokens[token_index], TokenType::SEMICOLON);
}

void Parser::parse_assignment(Node& node) {
    verify_token_type(tokens[token_index++], TokenType::EQUAL);

    verify_token_type(tokens[token_index], TokenType::BOOLEAN);
    const bool boolean_state = BOOLEAN_VALUES.at(tokens[token_index++].value);

    node.state = boolean_state;

    verify_token_type(tokens[token_index], TokenType::SEMICOLON);
}

Node& Parser::parse_identifier() {
    verify_token_type(tokens[token_index], TokenType::IDENTIFIER);
    if (is_node_type(tokens[token_index + 1], TokenType::DOT)) {
        return parse_identifier_gate();
    }
    const auto identifier = tokens[token_index++].value;
    const auto node_index = nodes.at(identifier);
    Node& node = current_graph[node_index];

    return node;
}

Node& Parser::parse_identifier_gate() {
    const auto gate_identifier = tokens[token_index++].value;
    const Gate& gate = gates_identifier.at(gate_identifier);

    if (gates_identifier.count(gate_identifier) == 0)
        throw_invalid_argument_error("Unregistered gate " + gate_identifier);

    verify_token_type(tokens[token_index++], TokenType::DOT);
    verify_token_type(tokens[token_index], TokenType::IDENTIFIER);
    const auto node_gate_aimed = tokens[token_index++].value;
    const auto node_index = get_gate_index_node(node_gate_aimed, gate);
    Node& node = current_graph[node_index];
    return node;
}

void Parser::parse_gate() {
    bool is_prerendered = false;

    verify_token_identifier(tokens[token_index++], GATE);
    if (is_identifier(tokens[token_index], PRERENDER)) {
        ++token_index;
        is_prerendered = true;
    }
    verify_token_type(tokens[token_index], TokenType::IDENTIFIER);
    const auto& gate_identifier = tokens[token_index++].value;
    verify_token_type(tokens[token_index++], TokenType::LEFT_BRACE);
    const std::vector<std::string> inputs = parse_inputs();
    const std::vector<std::string> outputs = parse_outputs();

    auto gate = parse_gate_content(is_prerendered, inputs, outputs);

    gates.insert({gate_identifier, gate});

    verify_token_type(tokens[token_index], TokenType::RIGHT_BRACE);
}

std::vector<std::string> Parser::parse_inputs() {
    verify_token_identifier(tokens[token_index++], INPUTS);
    verify_token_type(tokens[token_index++], TokenType::COLON);
    std::vector<std::string> inputs;
    do {
        inputs.push_back(tokens[token_index++].value);
    } while (tokens[token_index++].type == TokenType::COMMA);

    verify_token_type(tokens[token_index - 1], TokenType::SEMICOLON);

    return inputs;
}

std::vector<std::string> Parser::parse_outputs() {
    verify_token_identifier(tokens[token_index++], OUTPUTS);
    verify_token_type(tokens[token_index++], TokenType::COLON);
    std::vector<std::string> ouputs;
    do {
        ouputs.push_back(tokens[token_index++].value);
    } while (tokens[token_index++].type == TokenType::COMMA);

    verify_token_type(tokens[token_index - 1], TokenType::SEMICOLON);

    return ouputs;
}

Gate Parser::parse_gate_content(const bool is_prerendered, const std::vector<std::string>& inputs,
                                const std::vector<std::string>& outputs) {
    if (is_identifier(tokens[token_index], TABLE)) {
        const auto table = parse_table(inputs, outputs);
        return {inputs, outputs, table, true};
    }
    if (is_identifier(tokens[token_index], CIRCUIT) && is_prerendered) {
        const auto graph = parse_gate_graph(inputs, outputs);
        auto graph_csr = CSRGraph(graph);
        const auto table = graph_csr.determine_graph_gate_data();
        return {inputs, outputs, table.truth_table, true};
    }
    if (is_identifier(tokens[token_index], CIRCUIT) && !is_prerendered) {
        const auto graph = parse_gate_graph(inputs, outputs);
        return {inputs, outputs, graph, false};
    }

    throw_invalid_argument_error(
        "Invalid gate definition : pre render " + std::to_string(is_prerendered) + ". Keyword : " + tokens[token_index].
        value);
    return {};
}

uint32_t Parser::parse_table(const std::vector<std::string>& inputs, const std::vector<std::string>& outputs) {
    verify_token_identifier(tokens[token_index++], TABLE);
    verify_token_type(tokens[token_index++], TokenType::COLON);
    verify_token_type(tokens[token_index++], TokenType::LEFT_BRACE);

    size_t amount_bits = 0;
    const uint32_t table = parse_table_content(amount_bits, inputs.size(), outputs.size());

    const size_t amount_bits_per_output = inputs.size() * inputs.size();
    if (amount_bits_per_output * outputs.size() != amount_bits)
        throw_invalid_argument_error(
            "Invalid amount of bits for truth table. Expected " + std::to_string(
                amount_bits_per_output * outputs.size()) + ", got " + std::to_string(amount_bits));

    return table;
}

uint32_t Parser::parse_table_content(size_t& amount_bits, const size_t amount_inputs, const size_t amount_outputs) {
    switch (tokens[token_index].type) {
        case TokenType::BOOLEAN: return parse_table_content_short(amount_bits);
        case TokenType::LEFT_PAREN: return parse_table_content_long(amount_bits, amount_inputs, amount_outputs);
        default: throw_invalid_argument_error("Invalid token type " + tostring(tokens[token_index].type));
    }
    return -1; // prevent IDE warning for a branch without return
}

uint32_t Parser::parse_table_content_short(size_t& amount_bits) {
    uint32_t table = 0;
    do {
        table <<= 1;
        if (BOOLEAN_VALUES.at(tokens[token_index++].value)) table |= 1;
        ++amount_bits;
    } while (tokens[token_index++].type == TokenType::COMMA);

    verify_token_type(tokens[token_index - 1], TokenType::RIGHT_BRACE);
    verify_token_type(tokens[token_index++], TokenType::SEMICOLON);

    return table;
}

uint32_t Parser::parse_table_content_long_truth_table(size_t& amount_bits, const size_t amount_inputs,
                                                      const size_t amount_outputs) {
    uint32_t table = 0;
    size_t previous_inputs = -1;
    size_t current_line = 0;

    do {
        auto [inputs, outputs] = parse_table_content_long_item();
        if (inputs != previous_inputs + 1)
            throw_invalid_argument_error("Incorrect order for truth table");
        ++previous_inputs;
        amount_bits += amount_outputs;

        for (int i = 0; i < amount_outputs; ++i) {
            const bool value = outputs & 1;
            outputs >>= 1;
            const size_t bit_index = current_line + amount_inputs * amount_inputs * i;
            if (value) table |= 1 << bit_index;
        }

        ++current_line;
    } while (tokens[++token_index].type == TokenType::LEFT_PAREN);

    return table;
}

uint32_t Parser::parse_table_content_long(size_t& amount_bits, const size_t amount_inputs,
                                          const size_t amount_outputs) {
    const uint32_t table = parse_table_content_long_truth_table(amount_bits, amount_inputs, amount_outputs);

    verify_token_type(tokens[token_index++], TokenType::RIGHT_BRACE);
    verify_token_type(tokens[token_index++], TokenType::SEMICOLON);

    return table;
}

std::pair<size_t, size_t> Parser::parse_table_content_long_item() {
    verify_token_type(tokens[token_index++], TokenType::LEFT_PAREN);
    size_t inputs = 0;
    do {
        inputs <<= 1;
        if (BOOLEAN_VALUES.at(tokens[token_index++].value)) inputs |= 1;
    } while (tokens[token_index++].type == TokenType::COMMA);

    verify_token_type(tokens[token_index - 1], TokenType::PIPE);

    size_t outputs = 0;
    do {
        outputs <<= 1;
        if (BOOLEAN_VALUES.at(tokens[token_index++].value)) outputs |= 1;
    } while (tokens[token_index++].type == TokenType::COMMA);

    verify_token_type(tokens[--token_index], TokenType::RIGHT_PAREN);

    return {inputs, outputs};
}

Graph Parser::parse_gate_graph(const std::vector<std::string>& inputs, const std::vector<std::string>& outputs) {
    verify_token_identifier(tokens[token_index++], CIRCUIT);
    verify_token_type(tokens[token_index++], TokenType::COLON);

    verify_token_type(tokens[token_index], TokenType::LEFT_BRACE);
    const std::vector<Token> circuit_tokens = extract_block();
    auto parser = Parser(circuit_tokens);
    for (const auto& input : inputs) {
        parser.add_input(input);
    }
    for (const auto& output : outputs) {
        parser.add_output(output);
    }
    parser.parse_program_block();

    return parser.get_graph();
}

std::vector<Token> Parser::extract_block() {
    verify_token_type(tokens[token_index++], TokenType::LEFT_BRACE);

    std::vector block = {Token(TokenType::LEFT_BRACE)};
    size_t current_brace_level = 1;
    while (current_brace_level > 0) {
        block.push_back(tokens[token_index]);
        if (is_node_type(tokens[token_index], TokenType::LEFT_BRACE)) ++current_brace_level;
        else if (is_node_type(tokens[token_index], TokenType::RIGHT_BRACE)) --current_brace_level;
        ++token_index;
    }

    verify_token_type(tokens[token_index - 1], TokenType::RIGHT_BRACE);
    verify_token_type(tokens[token_index++], TokenType::SEMICOLON);

    return block;
}

void Parser::declare_primitive(const std::string& node_type_s) {
    const auto node_type = PRIMITIVE_TYPES.at(node_type_s);
    nodes.insert({tokens[token_index++].value, current_node_id});
    const auto node = Node(current_node_id++, node_type);
    current_graph.add_node(node);
}

void Parser::declare_gate(const std::string& node_type_s) {
    auto gate = gates.at(node_type_s);

    gates_identifier.insert({tokens[token_index].value, gate});
    auto& gate_ref = gates_identifier.at(tokens[token_index].value);
    nodes.insert({tokens[token_index++].value, current_node_id});
    if (!gate.prerendered) {
        declare_non_prerender_gate(gate_ref);
        return;
    }

    declare_prerender_gate(gate, gate_ref);
}

void Parser::declare_prerender_gate(const Gate& gate, Gate& gate_ref) {
    const auto node_gate = Node(current_node_id++, NodeType::GATE,
                                GateData(gate.table, gate.outputs.size(), GateRenderType::PRERENDERED));
    current_graph.add_node(node_gate);

    current_graph.resize(current_graph.get_nodes().size() + gate.inputs.size() + gate.outputs.size());
    const Node& node_gate_ref = current_graph[current_node_id - 1];
    for (auto& [key, value] : gate_ref.inputs) {
        value = current_node_id;
        const auto node_input = Node(current_node_id++, NodeType::WIRE);
        current_graph.add_edge(node_input, node_gate_ref);
    }
    for (auto& [key, value] : gate_ref.outputs) {
        value = current_node_id;
        const auto node_output = Node(current_node_id++, NodeType::GATE_OUTPUT);
        current_graph.add_edge(node_gate_ref, node_output);
    }
}

void Parser::declare_non_prerender_gate(Gate& gate) {
    const auto& nodes_gate = gate.graph.get_nodes();
    std::unordered_map<size_t, size_t> index_map;
    for (const auto& node : nodes_gate) {
        if (node.node_type == NodeType::UNDEFINED) continue;
        index_map.insert({node.index, current_node_id++});
    }

    size_t current_input = 0;
    size_t current_output = 0;
    for (const auto& node : nodes_gate) {
        if (node.node_type == NodeType::UNDEFINED) continue;

        auto new_node = node;
        register_io(gate, new_node, current_input, current_output, index_map);

        remap_node_indexes(new_node, index_map);

        current_graph.add_node(new_node);
    }
}

void Parser::add_input(const std::string& identifier) {
    nodes.insert({identifier, current_node_id});
    const auto node = Node(current_node_id++, NodeType::INPUT);
    current_graph.add_node(node);
}

void Parser::add_output(const std::string& identifier) {
    nodes.insert({identifier, current_node_id});
    const auto node = Node(current_node_id++, NodeType::OUTPUT);
    current_graph.add_node(node);
}