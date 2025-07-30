#include "Parser.hpp"

#include "language_processing/language_keywords_config.hpp"
#include "language_processing/token_manipulation/token_verification.hpp"
#include "utils/error_messages.hpp"

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

    verify_token_type(tokens[token_index], TokenType::SEMICOLON);
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
    const auto gate_index = nodes.at(gate_identifier);
    const auto node_index = get_gate_index_node(node_gate_aimed, gate) + gate_index + 1;
    Node& node = current_graph[node_index];
    return node;
}

void Parser::parse_gate() {
    verify_token_identifier(tokens[token_index++], GATE);
    verify_token_type(tokens[token_index], TokenType::IDENTIFIER);
    const auto& gate_identifier = tokens[token_index++].value;
    verify_token_type(tokens[token_index++], TokenType::LEFT_BRACE);
    const std::vector<std::string> inputs = parse_inputs();
    const std::vector<std::string> outputs = parse_outputs();

    Gate gate;
    if (is_identifier(tokens[token_index], TABLE)) {
        const auto table = parse_table();
        gate = Gate(inputs, outputs, table, true);
    }

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

uint32_t Parser::parse_table() {
    verify_token_identifier(tokens[token_index++], TABLE);
    verify_token_type(tokens[token_index++], TokenType::COLON);
    verify_token_type(tokens[token_index++], TokenType::LEFT_BRACE);

    uint32_t table = 0;
    do {
        table <<= 1;
        if (BOOLEAN_VALUES.at(tokens[token_index++].value)) table |= 1;
    } while (tokens[token_index++].type == TokenType::COMMA);

    verify_token_type(tokens[token_index - 1], TokenType::RIGHT_BRACE);
    verify_token_type(tokens[token_index++], TokenType::SEMICOLON);

    return table;
}

void Parser::declare_primitive(const std::string& node_type_s) {
    const auto node_type = PRIMITIVE_TYPES.at(node_type_s);
    nodes.insert({tokens[token_index++].value, current_node_id});
    const auto node = Node(current_node_id++, node_type);
    current_graph.add_node(node);
}

void Parser::declare_gate(const std::string& node_type_s) {
    const auto gate = gates.at(node_type_s);
    Node node_gate;

    gates_identifier.insert({tokens[token_index].value, gate});
    nodes.insert({tokens[token_index++].value, current_node_id});
    if (gate.prerendered) {
        node_gate = Node(current_node_id++, NodeType::GATE, GateData(gate.table, gate.outputs.size(), GateRenderType::PRERENDERED));
    } else {
        // TODO : to implement
    }
    current_graph.add_node(node_gate);

    current_graph.resize(current_graph.get_nodes().size() + gate.inputs.size() + gate.outputs.size());
    const Node& node_gate_ref = current_graph[current_node_id - 1];
    for (int i = 0; i < gate.inputs.size(); ++i) {
        const auto node_input = Node(current_node_id++, NodeType::WIRE);
        current_graph.add_edge(node_input, node_gate_ref);
    }

    for (int i = 0; i < gate.outputs.size(); ++i) {
        const auto node_output = Node(current_node_id++, NodeType::GATE_OUTPUT);
        current_graph.add_edge(node_gate_ref, node_output);
    }
}
