#pragma once
#include "Analyzers/BaseAnalyzer.h"
#include <map>
#include <string>

class UnsafeFunctionAnalyzer : public BaseAnalyzer {
private:
    struct UnsafeFunctionInfo {
        SeverityLevel severity;
        std::string description;
        std::string alternative;
    };

    std::map<std::string, UnsafeFunctionInfo> unsafeFunctions;

public:
    UnsafeFunctionAnalyzer();
    void analyze(const CppParser& parser) override;
};