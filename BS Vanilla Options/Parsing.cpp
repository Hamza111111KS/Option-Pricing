//
// Created by meddad on 21/02/2024.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <Windows.h>

#include "OptionsPricing.h"

#include "Parsing.h"
// Fonction pour obtenir la date actuelle en secondes depuis l'époque Unix
double getCurrentDate() {
    SYSTEMTIME systemTime;
    GetSystemTime(&systemTime);
    FILETIME fileTime;
    SystemTimeToFileTime(&systemTime, &fileTime);
    ULARGE_INTEGER uli;
    uli.LowPart = fileTime.dwLowDateTime;
    uli.HighPart = fileTime.dwHighDateTime;
    double secondsSinceEpoch = uli.QuadPart / 10000000ULL - 11644473600ULL;
    return secondsSinceEpoch;
}

// Classe pour gérer la date d'expiration d'une option
class OptionExpirationDate {
private:
    std::tm expirationDate{};

public:
    // Constructeur pour parser la date d'expiration
    OptionExpirationDate(const std::string& dateString, const std::string& format) {
        parseDate(dateString, format);
    }

    // Parser la date d'expiration de l'option
    void parseDate(const std::string& dateString, const std::string& format) {
        std::istringstream iss(dateString);
        std::tm tempDate = {};
        if (!(iss >> std::get_time(&tempDate, format.c_str()))) {
            throw std::invalid_argument("Format de date invalide");
        }
        expirationDate = tempDate;
    }

    // Calculer la différence de temps entre la date d'expiration et la date actuelle
    double getTimeDifference(double currentDate) {
        std::time_t expirationTime = std::mktime(&expirationDate);
        double diff = std::difftime(currentDate, expirationTime);
        return diff / (365.25 * 24 * 60 * 60); // Convertir les secondes en années
    }
};


// Fonction pour parser un fichier CSV contenant les données des options
std::vector<OptionData> parseCSV(const std::string& filename) {
    std::vector<OptionData> options;
    std::string format = "%m/%d/%Y";
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << filename << std::endl;
        return options;
    }

    std::string line;
    // Ignorer la ligne d'en-tête
    std::getline(file, line);

    // Obtenir la date actuelle
    double currentDate = getCurrentDate();

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string cell;

        OptionData option{};
        std::vector<std::string> row; // Stocker les cellules de la ligne actuelle

        // Parser chaque cellule dans la ligne
        while (std::getline(iss, cell, ';')) {
            row.push_back(cell);
        }

        if (row.size() >= 7) { // Vérifier s'il y a suffisamment de colonnes
            OptionExpirationDate maturityDate(row[4], format); // Parser la date de maturité
            option.spotPrice = std::stod(row[1]);
            option.strikePrice = std::stod(row[2]);
            option.maturity = maturityDate.getTimeDifference(currentDate); // Calculer la différence jusqu'à la maturité
            option.currentDate = currentDate/ (365.25 * 24 * 60 * 60); // Définir la date actuelle
            option.interest = 0.05; // Valeur par défaut
            option.volatility = 0.2;
            // option.volatility = std::stod(row[8]);
            option.optionType = std::stoi(row[16]);

            options.push_back(option);
        }
    }

    file.close();
    return options;
}

// Fonction pour afficher les données des options
void displayOptions(std::vector<OptionData> options) {
    for (size_t i = 0; i < options.size(); ++i) {
        const OptionData& option = options[i];
        std::cout << "Option " << (i + 1) << " data:" << std::endl;
        std::cout << "Spot Price: " << option.spotPrice << std::endl;
        std::cout << "Strike Price: " << option.strikePrice << std::endl;
        std::cout << "Maturity: " << option.maturity << std::endl;
        std::cout << "Interest: " << option.interest << std::endl;
        std::cout << "Volatility: " << option.volatility << std::endl;
        std::cout << "Option Type: " << option.optionType << std::endl;
        std::cout << "----------------------------------------" << std::endl;
    }
}
