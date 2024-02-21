//Ceci est un fichier OptionsPricing.h
#ifndef OPTIONS_PRICING_H
#define OPTIONS_PRICING_H

#include <string>
#include <vector>


// Déclaration de la structure OptionData
struct OptionData {
    double spotPrice;       // Prix actuel
    double strikePrice;     // Prix d'exercice
    double maturity;        // Maturité de l'option
    double currentDate;     // Date actuelle
    double interest;        // Taux d'intérêt
    double volatility;      // Volatilité
    int optionType;         // Type d'option (call ou put)
};
// OptionExpirationDate classe pour gérer la date d'expiration de l'option


double N(double z);

double calculateOptionPrice(const OptionData& optionData);       // Fonction pour calculer le prix de l'option
std::vector<double> calculateOptionPrices(const std::vector<OptionData>& options);  // Fonction pour calculer les prix des options

double calculatePayoff(const OptionData& optionData);           // Fonction pour calculer le payoff de l'option
std::vector<double> calculateOptionPayoffs(const std::vector<OptionData>& options); // Fonction pour calculer les payoffs des options


#endif // OPTIONS_PRICING_H
