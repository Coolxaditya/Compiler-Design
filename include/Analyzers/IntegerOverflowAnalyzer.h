#pragma once
#include "Analyzers/BaseAnalyzer.h"

class IntegerOverflowAnalyzer : public BaseAnalyzer {
public:
    void analyze(const CppParser& parser) override;
};