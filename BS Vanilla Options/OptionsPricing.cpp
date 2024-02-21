// Ceci est un fichier OptionsPricing.cpp

#include <iostream>

#include <vector>

#include <cmath>
#include "OptionsPricing.h"


// Approximation de la fonction de distribution cumulative normale (par des séries de Taylor)
// Fonction reprise du document de Bernt Arne Ødegaard
// Fonction pour approximer la fonction de distribution cumulative normale (CND)
double N(double z) {
    double L = 0.0;
    double K = 0.0;
    double dCND = 0.0;
    const double a1 = 0.31938153;
    const double a2 = -0.356563782;
    const double a3 = 1.781477937;
    const double a4 = -1.821255978;
    const double a5 = 1.330274429;
    L = fabs(z);
    K = 1.0 / (1.0 + 0.2316419 * L);
    dCND = 1.0 - 1.0 / sqrt(2 * M_PI) *
                 exp(-L * L / 2.0) * (a1 * K + a2 * K * K + a3 * pow(K, 3.0) +
                                      a4 * pow(K, 4.0) + a5 * pow(K, 5.0));

    if (z < 0) {
        return 1.0 - dCND;
    }
    else {
        return dCND;
    }
}

// Fonction pour calculer le prix de l'option
double calculateOptionPrice(const OptionData& optionData) {
    double spotPrice = optionData.spotPrice;
    double strikePrice = optionData.strikePrice;
    double maturity = optionData.maturity;
    double interest = optionData.interest;
    double volatility = optionData.volatility;
    int optionType = optionData.optionType;

    double d1 = (log(spotPrice / strikePrice) + (interest + (volatility * volatility) / 2.0) * maturity) / (volatility * sqrt(maturity));
    double d2 = d1 - volatility * sqrt(maturity);

    double x = spotPrice * N(optionType * d1);
    double y = strikePrice * exp(-interest * maturity) * N(optionType * d2);

    if (optionType == 1) {
        return x - y;
    } else if (optionType == -1) {
        return y - x;
    } else {
        throw std::invalid_argument("Type d'option invalide");
    }
}

// Fonction pour calculer les prix des options pour un ensemble d'options
std::vector<double> calculateOptionPrices(const std::vector<OptionData>& options) {
    std::vector<double> optionPrices;
    optionPrices.reserve(options.size());

    for (const auto& optionData : options) {
        double optionPrice = calculateOptionPrice(optionData);
        optionPrices.push_back(optionPrice);
    }

    return optionPrices;
}

// Fonction pour calculer le payoff de l'option
double calculatePayoff(const OptionData& optionData){
    double spotPrice = optionData.spotPrice;
    double strikePrice = optionData.strikePrice;
    int optionType = optionData.optionType;

    if (optionType == 1) {
        return std::max(spotPrice - strikePrice, 0.0);
    }
    else {
        return std::max( strikePrice - spotPrice, 0.0);
    }
}

// Fonction pour calculer les payoffs des options pour un ensemble d'options
std::vector<double> calculateOptionPayoffs(const std::vector<OptionData>& options) {
    std::vector<double> optionPayoff;
    optionPayoff.reserve(options.size());

    for (const auto& optionData : options) {
        double optionPrice = calculatePayoff(optionData);
        optionPayoff.push_back(optionPrice);
    }

    return optionPayoff;
}
