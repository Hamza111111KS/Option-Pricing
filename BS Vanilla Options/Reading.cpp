
// Ceci c'est le fichier Reading.cpp
#include "Reading.h"
#include "OptionsPricing.h"
#include <fstream> // Bibliothèque pour gérer les flux de fichiers
#include <ctime> // Bibliothèque pour gérer le temps
#include <algorithm> // Bibliothèque pour utiliser des algorithmes standard
#include <iostream> // Bibliothèque pour les entrées/sorties
#include <string> // Bibliothèque pour gérer les chaînes de caractères
#include <vector> // Bibliothèque pour utiliser des vecteurs
#include <thread> // Bibliothèque pour gérer les threads
#include <mutex> // Bibliothèque pour utiliser des mutex
#include <queue> // Bibliothèque pour utiliser des files



using namespace std; // Utiliser l'espace de noms standard

// Structure pour représenter une tâche
struct Task {
    std::string line; // Ligne du fichier CSV
    std::vector<std::string> row; // Vecteur pour stocker les cellules de la ligne
};

// Fonction pour lire un fichier CSV et stocker les données dans un vecteur de vecteurs
std::vector<std::vector<std::string>> readCSV(const std::string& filename) {
    std::vector<std::vector<std::string>> data; // Vecteur pour stocker les données CSV

    std::ifstream file(filename); // Ouvrir le fichier CSV
    if (!file.is_open()) { // Vérifier si le fichier est ouvert avec succès
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << filename << std::endl;
        return data; // Retourner des données vides si le fichier ne peut pas être ouvert
    }

    // Primitives de synchronisation
    std::mutex mtx; // Mutex pour la synchronisation
    std::queue<Task> tasks; // File de tâches

    // Fonction exécutée par les threads pour lire et analyser les lignes du fichier
    auto worker = [&]() {
        while (true) {
            Task task;
            {
                std::lock_guard<std::mutex> lock(mtx); // Verrouillage pour accéder en toute sécurité à la file de tâches
                if (tasks.empty()) break; // S'il n'y a plus de tâches, sortir de la boucle
                task = tasks.front(); // Récupérer la première tâche de la file
                tasks.pop(); // Supprimer la tâche de la file
            }
            std::istringstream iss(task.line); // Convertir la ligne en string stream pour l'analyse
            std::string cell;
            // Analyser chaque cellule de la ligne
            while (std::getline(iss, cell, ';')) {
                task.row.push_back(cell); // Stocker chaque cellule dans le vecteur de la ligne
            }
            {
                std::lock_guard<std::mutex> lock(mtx); // Verrouillage pour accéder en toute sécurité au vecteur de données
                data.push_back(task.row); // Ajouter la ligne analysée au vecteur de données
            }
        }
    };

    // Créer des threads travailleurs
    std::vector<std::thread> threads;
    const size_t numThreads = std::thread::hardware_concurrency(); // Obtenir le nombre de threads supportés par le matériel
    for (size_t i = 0; i < numThreads; ++i) {
        threads.emplace_back(worker); // Ajouter un thread travailleur à la liste
    }

    // Lire les lignes du fichier et ajouter des tâches à la file
    std::string line;
    while (std::getline(file, line)) { // Lire chaque ligne du fichier
        Task task;
        task.line = line; // Affecter la ligne à la tâche
        {
            std::lock_guard<std::mutex> lock(mtx); // Verrouillage pour accéder en toute sécurité à la file de tâches
            tasks.push(task); // Ajouter la tâche à la file
        }
    }

    // Attendre la fin des threads travailleurs
    for (auto& thread : threads) {
        thread.join(); // Attendre que chaque thread se termine
    }

    file.close(); // Fermer le fichier
    return data; // Retourner le vecteur contenant les données CSV
}

// Fonction pour enregistrer les résultats des prix et des payoffs dans un fichier CSV
void outputResults(const std::string& OutFileName, const std::vector<OptionData>& options, const std::vector<double>& optionPrices, const std::vector<double>& optionPayoffs) {
    std::ofstream outputFile(OutFileName);
    if (!outputFile.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << OutFileName << std::endl;
        return;
    }

    // En-tête
    outputFile << "Spot Price,Strike Price,Maturity,Interest,Volatility,Option Type,Option Price,Option Payoff" << std::endl;

    // Écrire les données pour chaque option
    for (size_t i = 0; i < options.size(); ++i) {
        const OptionData& option = options[i];
        double optionPrice = optionPrices[i];
        double optionPayoff = optionPayoffs[i];

        outputFile << option.spotPrice << ","
                   << option.strikePrice << ","
                   << option.maturity << ","
                   << option.interest << ","
                   << option.volatility << ","
                   << option.optionType << ","
                   << optionPrice << ","
                   << optionPayoff << std::endl;
    }

    outputFile.close();
}



