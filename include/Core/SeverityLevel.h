#pragma once
#include <string>

enum class SeverityLevel {
    LOW,
    MEDIUM,
    HIGH,
    CRITICAL
};

std::string to_string(SeverityLevel level);