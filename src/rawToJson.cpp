// Traitement appliqué à arcs.csv :
// - suppression des []
// Cela implique la prise en commpte de la première valeur en cas de valeur multiples
// 2400 occurences concernées
// remplacement de tous les "" en " dans le cas de name comprennant ' (2234 occurences)

#include "rawToJson.h"

using json = nlohmann::json;
using namespace std;

void arcsCsvToJson(const string &inputFilePath, const string &outputFilePath)
{
    ifstream inputFile(inputFilePath);
    ofstream outputFile(outputFilePath);

    string line;
    json final;

    if (!inputFile.is_open() || !outputFile.is_open())
    {
        cerr << "Erreur lors de l'ouverture des fichiers." << endl;
        return;
    }

    while (getline(inputFile, line))
    {
        json j;
        stringstream ss(line);
        string word;
        string memory;
        string temporaryId = "";
        bool capturingValue = false;
        string valueBuffer;
        char quoteChar = '\0'; // null (ou fin de chaîne)
        int cpt = 0;

        while (ss >> word)
        {
            // Nettoyer les caractères indésirables (virgules et apostrophes)
            word.erase(remove(word.begin(), word.end(), ','), word.end());

            if (cpt == 0)
            {
                // Chercher les deux premiers nombres séparés par des virgules
                size_t firstComma = line.find(',');
                size_t secondComma = line.find(',', firstComma + 1);

                if (firstComma != string::npos && secondComma != string::npos)
                {
                    // Extraire le StartingNode et le EndingNode
                    string startingNode = line.substr(0, firstComma);
                    string endingNode = line.substr(firstComma + 1, secondComma - firstComma - 1);
                    temporaryId += startingNode;
                    temporaryId += endingNode;

                    // Assigner les valeurs au JSON
                    j["StartingNode"] = startingNode;
                    j["EndingNode"] = endingNode;
                    j["name"] = temporaryId;

                    // Retirer cette portion de la ligne pour le traitement ultérieur
                    line = line.substr(secondComma + 1);
                }
                else
                {
                    cerr << "Erreur : format inattendu sur la ligne : " << line << endl;
                    continue;
                }
                cpt++;
                continue; // Passer à l'itération suivante pour traiter le reste
            }

            // Gérer la capture de la valeur
            if (capturingValue)
            {
                // Si c'est la fin de la chaîne (correspondance avec quoteChar)
                if (word.back() == quoteChar)
                {
                    word.pop_back();           // Enlever le caractère de fin
                    valueBuffer += " " + word; // Ajouter la dernière partie
                    j[memory] = valueBuffer;   // Sauvegarder la valeur complète
                    capturingValue = false;    // Fin de la capture
                    valueBuffer.clear();
                    memory.clear();
                }
                else
                {
                    // Continuer de capturer la valeur
                    valueBuffer += " " + word;
                }
            }
            else
            {
                // Vérifier si le mot est un attribut à capturer
                if (word == "'name':" || word == "'highway':" || word == "'oneway':" ||
                    word == "'reversed':" || word == "'speed_kph':" ||
                    word == "'travel_time':" || word == "'maxspeed':" || word == "'length':" || word == "'lane'")
                {
                    // Nettoyer le mot pour enlever les guillemets simples
                    word = word.substr(1, word.size() - 3); // Retirer le premier et dernier caractère
                    memory = word;                          // Enregistrer l'attribut nettoyé
                    capturingValue = true;                  // Commencer à capturer la valeur

                    // Vérifier si la valeur est entre guillemets ou apostrophes
                    if (word == "name")
                    {
                        ss >> word; // Lire le prochain mot (la valeur du nom)

                        // Vérifier s'il commence par un guillemet ou une apostrophe
                        if ((word.front() == '"' || word.front() == '\'') && word.back() == word.front())
                        {
                            // Si le mot commence et finit par le même caractère délimiteur
                            word.erase(word.begin()); // Supprimer le premier guillemet/apostrophe
                            word.pop_back();          // Supprimer le dernier guillemet/apostrophe
                            j[memory] = word;         // Assigner directement la valeur
                            capturingValue = false;   // Pas besoin de capturer plus
                        }
                        else if (word.front() == '"' || word.front() == '\'')
                        {
                            // Si le mot commence par un guillemet/apostrophe mais ne se termine pas
                            quoteChar = word.front(); // Enregistrer le caractère de délimitation
                            word.erase(word.begin()); // Supprimer le premier guillemet/apostrophe
                            valueBuffer = word;       // Commencer à capturer la valeur
                            capturingValue = true;    // Activer le mode de capture
                        }
                        else
                        {
                            j[memory] = word;       // Si pas de guillemets, on garde la valeur
                            capturingValue = false; // Fin de la capture
                        }
                    }
                    else if (word == "travel_time")
                    {
                        ss >> word;                             // Lire le prochain mot (la valeur du nom)
                        word = word.substr(0, word.size() - 2); // Retirer les 2 derniers caractères
                        j[memory] = word;                       // Assigner directement la valeur
                        capturingValue = false;                 // Pas besoin de capturer plus
                    }
                    else
                    {
                        ss >> word;                             // Lire le prochain mot (la valeur du nom)
                        word = word.substr(0, word.size() - 1); // Retirer  dernier caractère
                        // Vérifier s'il commence par un guillemet ou une apostrophe
                        if ((word.front() == '"' || word.front() == '\'') && word.back() == word.front())
                        {
                            // Si le mot commence et finit par le même caractère délimiteur
                            word.erase(word.begin()); // Supprimer le premier guillemet/apostrophe
                            word.pop_back();          // Supprimer le dernier guillemet/apostrophe
                            j[memory] = word;         // Assigner directement la valeur
                            capturingValue = false;   // Pas besoin de capturer plus
                        }
                        else
                        {
                            j[memory] = word;       // Si pas de guillemets, on garde la valeur
                            capturingValue = false; // Fin de la capture
                        }
                    }
                }
            }
        }
        final.push_back(j); // Ajouter le JSON de la ligne au résultat global
    }
    outputFile << final.dump(4); // Sauvegarder le fichier JSON avec une indentation de 4
}

void nodesCsvToJson(const string &inputFilePath, const string &outputFilePath)
{
    ifstream inputFile(inputFilePath);
    ofstream outputFile(outputFilePath);

    string line;
    json final;

    if (!inputFile.is_open() || !outputFile.is_open())
    {
        cerr << "Erreur lors de l'ouverture des fichiers." << endl;
        return;
    }

    while (getline(inputFile, line))
    {
        json j;
        stringstream ss(line);
        string id, word;

        // Récupérer l'ID
        if (getline(ss, id, ','))
        {
            j["id"] = id; // Stocker l'ID
        }

        // Récupérer la valeur de y
        ss >> word;
        ss >> word;                                                         // Récupérer le mot
        word.erase(std::remove(word.begin(), word.end(), ','), word.end()); // Enlever la virgule
        j["y"] = word;                                                      // Stocker y

        // Récupérer la valeur de x
        ss >> word;                                                         // Récupérer le mot suivant
        ss >> word;                                                         // Récupérer encore le mot
        word.erase(std::remove(word.begin(), word.end(), ','), word.end()); // Enlever la virgule
        j["x"] = word;                                                      // Stocker x

        // Récupérer street_count et enlever les deux derniers caractères
        ss >> word;                             // Récupérer le mot
        ss >> word;                             // Récupérer encore le mot
        word.erase(word.end() - 2, word.end()); // Enlever les deux derniers caractères (les guillemets)
        j["street_count"] = word;               // Stocker street_count

        // Ajouter l'objet JSON de cette ligne à la liste finale
        final.push_back(j);
    }

    // Sauvegarder le résultat final dans le fichier de sortie
    outputFile << final.dump(4); // Sauvegarder avec une indentation de 4
}