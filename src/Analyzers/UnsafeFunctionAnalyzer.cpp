#include "Analyzers/UnsafeFunctionAnalyzer.h"

UnsafeFunctionAnalyzer::UnsafeFunctionAnalyzer() {
    // Dictionary of unsafe functions and their safer alternatives
    unsafeFunctions["gets"] = {
        SeverityLevel::CRITICAL,
        "Unbounded read, can lead to buffer overflow",
        "fgets(buffer, size, stdin)"
    };
    
    unsafeFunctions["strcpy"] = {
        SeverityLevel::HIGH,
        "No bounds checking, can lead to buffer overflow",
        "strncpy(dest, src, dest_size)"
    };
    
    unsafeFunctions["strcat"] = {
        SeverityLevel::HIGH,
        "No bounds checking, can lead to buffer overflow",
        "strncat(dest, src, dest_size)"
    };
    
    unsafeFunctions["sprintf"] = {
        SeverityLevel::HIGH,
        "No bounds checking, can lead to buffer overflow",
        "snprintf(buffer, buffer_size, format, ...)"
    };
    
    unsafeFunctions["scanf"] = {
        SeverityLevel::MEDIUM,
        "Can lead to buffer overflow with %s without limit",
        "scanf(\"%Ns\", buffer) with size limit"
    };
}

void UnsafeFunctionAnalyzer::analyze(const CppParser& parser) {
    auto root = parser.getASTRoot();
    if (!root) {
        return;
    }

    for (const auto& child : root->children) {
        if (child->type == ASTNodeType::FUNCTION_CALL) {
            std::string functionName = child->value;
            
            auto it = unsafeFunctions.find(functionName);
            if (it != unsafeFunctions.end()) {
                const auto& info = it->second;
                
                // Get the code snippet
                std::string codeSnippet = parser.getCodeSnippet(child->line);
                
                vulnerabilities.emplace_back(
                    VulnerabilityType::UNSAFE_FUNCTION,
                    parser.getFilePath(),
                    child->line,
                    child->column,
                    info.severity,
                    "Call to unsafe function '" + functionName + "': " + info.description,
                    codeSnippet,
                    "Consider using " + info.alternative + " instead"
                );
            }
        }
    }
}