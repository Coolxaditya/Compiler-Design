#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Parser/Token.h"
#include "Parser/ASTNode.h"

class CppParser {
private:
    std::string filePath;
    std::string sourceCode;
    std::vector<Token> tokens;
    std::shared_ptr<ASTNode> astRoot;

    bool parseFile();
    void tokenize();
    void tokenizeLine(const std::string& line, int lineNumber);
    void parse();

public:
    CppParser(const std::string& filePath);

    bool process();
    std::shared_ptr<ASTNode> getASTRoot() const;
    std::string getFilePath() const;
    std::string getSourceCode() const;
    std::string getCodeSnippet(int lineNumber) const;
};