//
// Created by meddad on 21/02/2024.
//

// Ceci c'est le fichier Parsing.h
#ifndef BSM_PARSING_H
#define BSM_PARSING_H

#include <string>
#include <vector>
#include "OptionsPricing.h" // Include OptionsPricing.h to access OptionData



// OptionData struct pour contenir les attributs de l'option


// OptionExpirationDate classe pour gérer la date d'expiration de l'option
class OptionExpirationDate;


// Prototypes de fonctions
std::vector<OptionData> parseCSV(const std::string& filename); // Function to parse the CSV file

void displayOptions(std::vector<OptionData> options);


#endif //BSM_PARSING_H
