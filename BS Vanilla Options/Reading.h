/*
   Fichier : Reading.h
   Auteur : meddad Hamza
   Date de création : 14/02/2024
*/


// Ceci c'est le fichier Reading.h
#ifndef BSM_READING_H // Directive de préprocesseur pour éviter les multiples inclusions
#define BSM_READING_H
#include "OptionsPricing.h"
#include "Parsing.h"


#include <iomanip> // Bibliothèque pour formater les entrées/sorties
#include <ctime> // Bibliothèque pour gérer le temps
#include <vector> // Bibliothèque pour utiliser des vecteurs
#include <string> // Bibliothèque pour gérer les chaînes de caractères

using namespace std; // Utiliser l'espace de noms standard

// Déclarations des fonctions
std::vector<std::vector<std::string>> readCSV(const std::string& filename); // Fonction pour lire un fichier CSV et stocker les données


void outputResults(const std::string& outfilename, const std::vector<OptionData>& options, const std::vector<double>& optionPrices, const std::vector<double>& optionPayoffs);  // Fonction pour produire les résultats en sortie

#endif //BSM_READING_H // Fin de la directive de préprocesseur

