#pragma once
#include "Analyzers/BaseAnalyzer.h"

class BufferOverflowAnalyzer : public BaseAnalyzer {
public:
    void analyze(const CppParser& parser) override;
};