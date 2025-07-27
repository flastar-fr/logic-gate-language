#pragma once
#include <iosfwd>
#include <string>

enum class NodeType {
    UNDEFINED,
    GATE,
    WIRE,
    INPUT,
    OUTPUT,
    FIXED,
    GATE_OUTPUT
};

inline std::string tostring(const NodeType& type) {
    std::string to_display;

    switch (type) {
        case NodeType::UNDEFINED: {
            to_display = "UNDEFINED";
            break;
        }
        case NodeType::GATE: {
            to_display = "GATE";
            break;
        }
        case NodeType::WIRE: {
            to_display = "WIRE";
            break;
        }
        case NodeType::INPUT: {
            to_display = "INPUT";
            break;
        }
        case NodeType::OUTPUT: {
            to_display = "OUTPUT";
            break;
        }
        case NodeType::FIXED: {
            to_display = "FIXED";
            break;
        }
        case NodeType::GATE_OUTPUT: {
            to_display = "GATE_OUTPUT";
            break;
        }

        default: {
            to_display = "UNKNOWN_NODE";
            break;
        }
    }

    return to_display;
}

inline std::ostream& operator<<(std::ostream& lhs, const NodeType& rhs) {
    lhs << tostring(rhs);
    return lhs;
}
