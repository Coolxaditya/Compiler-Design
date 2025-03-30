#include <iostream>
#include <string>
#include <memory>
#include <filesystem>
#include "Core/VulnerabilityScanner.h"
#include "Analyzers/UnsafeFunctionAnalyzer.h"
#include "Analyzers/BufferOverflowAnalyzer.h"
#include "Analyzers/IntegerOverflowAnalyzer.h"
#include "Reporting/VulnerabilityReporter.h"

namespace fs = std::filesystem;

// Function to display usage information
void displayUsage(const std::string& programName) {
    std::cout << "Usage: " << programName << " <target> [options]\n"
              << "Options:\n"
              << "  -r, --recursive     Scan directories recursively\n"
              << "  -o, --output FORMAT Output format (text or json)\n"
              << "  -h, --help          Display this help message\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        displayUsage(argv[0]);
        return 1;
    }

    // Parse command line arguments
    std::string target;
    bool recursive = false;
    std::string outputFormat = "text";

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (arg == "-h" || arg == "--help") {
            displayUsage(argv[0]);
            return 0;
        } else if (arg == "-r" || arg == "--recursive") {
            recursive = true;
        } else if (arg == "-o" || arg == "--output") {
            if (i + 1 < argc) {
                outputFormat = argv[++i];
                if (outputFormat != "text" && outputFormat != "json") {
                    std::cerr << "Error: Invalid output format. Use 'text' or 'json'.\n";
                    return 1;
                }
            } else {
                std::cerr << "Error: Output format not specified.\n";
                return 1;
            }
        } else if (target.empty()) {
            target = arg;
        } else {
            std::cerr << "Error: Unexpected argument: " << arg << "\n";
            displayUsage(argv[0]);
            return 1;
        }
    }

    if (target.empty()) {
        std::cerr << "Error: No target specified.\n";
        displayUsage(argv[0]);
        return 1;
    }

    // Initialize scanner
    VulnerabilityScanner scanner;

    // Register analyzers
    scanner.registerAnalyzer(std::make_shared<UnsafeFunctionAnalyzer>());
    scanner.registerAnalyzer(std::make_shared<BufferOverflowAnalyzer>());
    scanner.registerAnalyzer(std::make_shared<IntegerOverflowAnalyzer>());

    // Scan target
    if (fs::is_regular_file(target)) {
        std::cout << "Scanning file: " << target << std::endl;
        scanner.scanFile(target);
    } else if (fs::is_directory(target)) {
        std::cout << "Scanning directory: " << target << std::endl;
        int filesScanned = scanner.scanDirectory(target, recursive);
        std::cout << "Scanned " << filesScanned << " files" << std::endl;
    } else {
        std::cerr << "Error: Target not found: " << target << std::endl;
        return 1;
    }

    // Generate and print report
    const auto& vulnerabilities = scanner.getVulnerabilities();
    VulnerabilityReporter reporter(vulnerabilities, outputFormat);
    std::string report = reporter.generateReport();
    std::cout << report << std::endl;

    return 0;
}