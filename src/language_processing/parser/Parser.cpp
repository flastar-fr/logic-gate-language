#include "Parser.hpp"

#include "language_processing/language_keywords_config.hpp"
#include "language_processing/token_verification.hpp"
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
    if (PRIMITIVE_TYPES.count(tokens[token_index].value)) {
        parse_declaration();
        verify_token_type(tokens[token_index], TokenType::SEMICOLON);
        return;
    }

    verify_token_type(tokens[token_index], TokenType::IDENTIFIER);
    switch (tokens[token_index + 1].type) {
        case TokenType::RIGHT_ARROW: {
            parse_edge_declaration();
            break;
        }
        case TokenType::EQUAL: {
            parse_assignment();
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
    const auto node_type = PRIMITIVE_TYPES.at(node_type_s);
    nodes.insert({tokens[token_index++].value, current_node_id});
    const auto node = Node(current_node_id++, node_type);
    current_graph.add_node(node);

    switch (tokens[token_index].type) {
        case TokenType::RIGHT_ARROW: {
            --token_index;
            parse_edge_declaration();
            break;
        }
        case TokenType::EQUAL: {
            --token_index;
            parse_assignment();
            break;
        }
        case TokenType::SEMICOLON: break;
        default: {
            throw_invalid_argument_error("Invalid node type " + tostring(tokens[token_index].type));
        }
    }

    verify_token_type(tokens[token_index], TokenType::SEMICOLON);
}

void Parser::parse_edge_declaration() {
    verify_token_type(tokens[token_index], TokenType::IDENTIFIER);
    const auto identifier_left = tokens[token_index++].value;

    verify_token_type(tokens[token_index++], TokenType::RIGHT_ARROW);

    verify_token_type(tokens[token_index], TokenType::IDENTIFIER);
    const auto identifier_right = tokens[token_index++].value;

    const auto node_index_left = nodes.at(identifier_left);
    const auto node_index_right = nodes.at(identifier_right);

    const Node& node_left = current_graph[node_index_left];
    const Node& node_right = current_graph[node_index_right];

    current_graph.add_edge(node_left, node_right);

    verify_token_type(tokens[token_index], TokenType::SEMICOLON);
}

void Parser::parse_assignment() {
    verify_token_type(tokens[token_index], TokenType::IDENTIFIER);
    const auto identifier = tokens[token_index++].value;

    verify_token_type(tokens[token_index++], TokenType::EQUAL);

    verify_token_type(tokens[token_index], TokenType::BOOLEAN);
    const bool boolean_state = BOOLEAN_VALUES.at(tokens[token_index++].value);

    const auto node_index = nodes.at(identifier);

    Node& node = current_graph[node_index];
    node.state = boolean_state;

    verify_token_type(tokens[token_index], TokenType::SEMICOLON);
}

void Parser::parse_gate() {
    verify_token_identifier(tokens[token_index++], GATE);
    // TODO : to implement
}
