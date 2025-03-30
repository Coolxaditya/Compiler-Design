#pragma once
#include <string>
#include <vector>
#include <memory>

enum class ASTNodeType {
    TRANSLATION_UNIT,
    FUNCTION_CALL,
    FUNCTION_DEFINITION,
    VARIABLE_DECLARATION,
    ARRAY_ACCESS,
    BINARY_EXPRESSION,
    BLOCK,
    UNKNOWN
};

class ASTNode {
public:
    ASTNodeType type;
    std::string value;
    int line;
    int column;
    std::vector<std::shared_ptr<ASTNode>> children;

    ASTNode(ASTNodeType type, const std::string& value = "", int line = 0, int column = 0);
    void addChild(std::shared_ptr<ASTNode> child);
};