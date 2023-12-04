#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    string input_filename = "";
    cout << "Input file: ";
    getline(cin, input_filename);
    ifstream file_object(input_filename);
    if ( not file_object ) {
        cout << "Error! The file " << input_filename << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    //Read player score from the file
    map<string, int> playerScores;
    string line;
        while (getline(file_object, line)) {
            // Split the line into playerName and points
            size_t colonPos = line.find(':');
            if (colonPos != string::npos) { // if ":" is not found, special const value npos (no position) is returned
                string playerName = line.substr(0, colonPos);
                int points = stoi(line.substr(colonPos + 1));
                playerScores[playerName] += points;
            }
        }
    file_object.close();

    //Sort players alphabetically by their names
    vector<pair<string, int>> sortedPlayers(playerScores.begin(), playerScores.end());
    sort(sortedPlayers.begin(), sortedPlayers.end());

    //Print the final scores
    cout << "Final scores:" << endl;
    for (const auto& player : sortedPlayers) {
        cout << player.first << ": " << player.second << endl;
    }

    return EXIT_SUCCESS;
}
