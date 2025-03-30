#pragma once
#include <vector>
#include "Core/Vulnerability.h"
#include "Parser/CppParser.h"

class BaseAnalyzer {
protected:
    std::vector<Vulnerability> vulnerabilities;

public:
    virtual ~BaseAnalyzer() = default;
    
    virtual void analyze(const CppParser& parser) = 0;
    
    const std::vector<Vulnerability>& getVulnerabilities() const {
        return vulnerabilities;
    }
};