#include "Core/SeverityLevel.h"

std::string to_string(SeverityLevel level) {
    switch (level) {
        case SeverityLevel::LOW: return "Low";
        case SeverityLevel::MEDIUM: return "Medium";
        case SeverityLevel::HIGH: return "High";
        case SeverityLevel::CRITICAL: return "Critical";
        default: return "Unknown";
    }
}