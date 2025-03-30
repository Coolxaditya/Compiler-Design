#include "Parser/CppParser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>

CppParser::CppParser(const std::string& filePath) : filePath(filePath), astRoot(nullptr) {}

bool CppParser::parseFile() {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    sourceCode = buffer.str();
    file.close();
    return true;
}

void CppParser::tokenize() {
    std::istringstream stream(sourceCode);
    std::string line;
    int lineNumber = 1;

    while (std::getline(stream, line)) {
        tokenizeLine(line, lineNumber);
        lineNumber++;
    }
}

void CppParser::tokenizeLine(const std::string& line, int lineNumber) {
    // Simple regex patterns for different token types
    std::vector<std::pair<TokenType, std::regex>> patterns = {
        {TokenType::FUNCTION_CALL, std::regex("\\b(\\w+)\\s*\\(")},
        {TokenType::INCLUDE, std::regex("#\\s*include\\s*[<\"]([^>\"]+)[>\"]")},
        {TokenType::KEYWORD, std::regex("\\b(if|while|for|return|int|char|void|const|static)\\b")},
        {TokenType::IDENTIFIER, std::regex("\\b[a-zA-Z_]\\w*\\b")},
        {TokenType::STRING, std::regex("\"[^\"]*\"")},
        {TokenType::OPERATOR, std::regex("[=+\\-*/&|<>!%^]+")},
        {TokenType::PUNCTUATION, std::regex("[(){}\\[\\];,.]")}
    };

    size_t position = 0;
    while (position < line.length()) {
        // Skip whitespace
        if (std::isspace(line[position])) {
            position++;
            continue;
        }

        bool matched = false;
        for (const auto& [type, pattern] : patterns) {
            std::smatch match;
            std::string remaining = line.substr(position);
            
            if (std::regex_search(remaining, match, pattern, std::regex_constants::match_continuous)) {
                std::string value = match.str();
                tokens.emplace_back(type, value, lineNumber, position + 1);
                position += value.length();
                matched = true;
                break;
            }
        }

        if (!matched) {
            // Skip unrecognized character
            position++;
        }
    }
}

void CppParser::parse() {
    // This is a simplified parser. A real C++ parser would be much more complex.
    astRoot = std::make_shared<ASTNode>(ASTNodeType::TRANSLATION_UNIT);
    
    // Example: Extract function calls
    for (const auto& token : tokens) {
        if (token.type == TokenType::FUNCTION_CALL) {
            std::string functionName = token.value;
            // Remove the trailing '('
            if (!functionName.empty() && functionName.back() == '(') {
                functionName.pop_back();
            }
            
            auto callNode = std::make_shared<ASTNode>(
                ASTNodeType::FUNCTION_CALL, 
                functionName, 
                token.line, 
                token.column
            );
            
            astRoot->addChild(callNode);
        }
        // Additional parsing logic would go here
    }
}

bool CppParser::process() {
    if (!parseFile()) {
        return false;
    }
    
    tokenize();
    parse();
    return true;
}

std::shared_ptr<ASTNode> CppParser::getASTRoot() const {
    return astRoot;
}

std::string CppParser::getFilePath() const {
    return filePath;
}

std::string CppParser::getSourceCode() const {
    return sourceCode;
}

std::string CppParser::getCodeSnippet(int lineNumber) const {
    std::istringstream stream(sourceCode);
    std::string line;
    int currentLine = 1;

    while (std::getline(stream, line) && currentLine < lineNumber) {
        currentLine++;
    }

    if (currentLine == lineNumber) {
        return line;
    }
    
    return "";
}