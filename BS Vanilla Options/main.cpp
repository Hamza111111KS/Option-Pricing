
// Ceci c'est le fichier main.cpp

#include <iostream>
#include <ctime>
#include <vector>
#include <string>

#include "Parsing.h"
#include "Reading.h"


using namespace std; // Place this directive before using cout

int main() {

    // Displaying the results
    std::string filename = "E:/AF/S4/c++/BSM/option_GS_df.csv"; // Replace "your_csv_file.csv" with your actual CSV file path

    // Read the CSV file
    std::vector<std::vector<std::string>> csvData = readCSV(filename);

    // Display the CSV data
    for (const auto& row : csvData) {
        for (const auto& cell : row) {
            std::cout << cell << '\t';
        }
        std::cout << std::endl;
    }

    // Parsing the CSV file
    std::vector<OptionData> options = parseCSV(filename);

    displayOptions(options);

    std::vector<double> optionPrices = calculateOptionPrices(options);
    std::vector<double> optionPayoffs = calculateOptionPayoffs(options);

    // Output option prices
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << "Option " << (i + 1) << " Price : " << optionPrices[i] << std::endl;
        std::cout << "Option " << (i+1) << " Payoff :" << optionPayoffs[i] << std::endl;
        std::cout << "----------------------------------------" << std::endl;

    }

    std::string outputFilename = "E:/AF/S4/c++/BSM/output.csv"; // Replace "output.csv" with your desired output CSV file path
    outputResults(outputFilename, options, optionPrices, optionPayoffs);
    return 0;
}
