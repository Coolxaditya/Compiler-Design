#include "Parser/ASTNode.h"

ASTNode::ASTNode(ASTNodeType type, const std::string& value, int line, int column)
    : type(type), value(value), line(line), column(column) {}

void ASTNode::addChild(std::shared_ptr<ASTNode> child) {
    children.push_back(child);
}