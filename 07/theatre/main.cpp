/* Theatre
 *
 * Desc:
 *   This program implements a program that reads the play collection data of different
 *   theatres in many towns from a file at startup, stores them in a nested map and give the users
 *   opportunity to search the information regarding to the play or theatres.
 *   The program terminates when the user gives a quitting command ('quit').
 *
 * Program author ( Fill with your own info )
 * Name: Chi Nguyen
 * Student number: 050358427
 * UserID: svchng ( Necessary due to gitlab folder naming. )
 * E-Mail: chi.nguyen@tuni.fi
 *
 * Notes about the program and it's implementation (if any):
 * - Nested map is chosen as the main datastructure to store the theatre data
 * - map<string, map<string, map<string, vector<pair<string, string>>>>>
 * _ For players and its corresponding seat, vector<pair<string,string>> is used to
 *   preserve the order of the given data in the original input file
 * */

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <iomanip>
#include <optional>

using namespace std;

// Fields in the input file
const int NUMBER_OF_FIELDS = 5;

// Command prompt
const string PROMPT = "the> ";

// Error and other messages
const string EMPTY_FIELD = "Error: empty field in line ";
const string FILE_ERROR = "Error: input file cannot be opened";
const string WRONG_PARAMETERS = "Error: wrong number of parameters";
const string THEATRE_NOT_FOUND = "Error: unknown theatre";
const string PLAY_NOT_FOUND = "Error: unknown play";
const string PLAYER_NOT_FOUND = "Error: unknown player";
const string TOWN_NOT_FOUND = "Error: unknown town";
const string COMMAND_NOT_FOUND = "Error: unknown command";
const string NOT_AVAILABLE = "No plays available";

// Casual split function, if delim char is between "'s, ignores it.
vector<string> split(const string& str, char delim)
{
    vector<string> result = {""};
    bool inside_quotation = false;
    for(char current_char : str)
    {
        if(current_char == '"')
        {
            inside_quotation = not inside_quotation;
        }
        else if(current_char == delim and not inside_quotation)
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    return result;
}

// Print all the theatres function
void theatres(map<string, map<string, map<string, vector<pair<string, string>>>> >& theatreData) {
    set<string> theatres;

    for (const auto& town : theatreData) {
        for (const auto& theatre : town.second) {
            theatres.insert(theatre.first);
        }
    }

    for (const string& theatre : theatres) {
        cout << theatre << endl;
    }
}

// Print all the plays function
void plays(map<string, map<string, map<string, vector<pair<string, string>>>>>& theatreData) {
    set<string> plays;

    for (const auto& town : theatreData) {
        for (const auto& theatre : town.second) {
            for (const auto& play : theatre.second) {
                // Split the play names if it has alias
                vector<string> playNames = split(play.first, '/');
                // Store the play names with or without alias in the set plays as required
                int size = playNames.size();
                string play_and_alias;
                if (size == 2) {
                   play_and_alias = playNames.at(0) + " *** " + playNames.at(1);
                } else {
                   play_and_alias = playNames.at(0);
                }
                plays.insert(play_and_alias);
            }
        }
    }

    for (const string& play : plays) {
        cout << play << endl;
    }
}

// Print all the theatres offering the given play function
void theatres_of_play(map<string, map<string, map<string, vector<pair<string, string>>>>>& theatreData,
                              string given_play) {
    set<string> theatres;
    bool playFound = false;

    for (const auto& town : theatreData) {
        for (const auto& theatre : town.second) {
            for (const auto& play : theatre.second) {
                // Split the play names if it has alias
                vector<string> playNames = split(play.first, '/');
                for (const auto& playName : playNames){
                    if (playName == given_play){
                        playFound = true;
                        theatres.insert(theatre.first);
                    }
                }
            }
        }
    }

    for (const string& theatre : theatres) {
        cout << theatre << endl;
    }
    // Checks the validity of the given_play
    if (!playFound) {
        cout << PLAY_NOT_FOUND << endl;
    }
}

void plays_in_theatre(map<string, map<string, map<string, vector<pair<string, string>>>>>& theatreData,
                            string given_theatre) {
    set<string> plays;
    bool theatreFound = false;

    for (const auto& town : theatreData) {
        for (const auto& theatre : town.second) {
            if (theatre.first == given_theatre) {
                theatreFound = true;
                for (const auto& play : theatre.second) {
                    // Split the play names if it has alias
                    vector<string> playNames = split(play.first, '/');
                    // Store the play names with or without alias in the set plays as required
                    int size = playNames.size();
                    string play_and_alias;
                    if (size == 2) {
                       play_and_alias = playNames.at(0) + " *** " + playNames.at(1);
                    } else {
                       play_and_alias = playNames.at(0);
                    }
                    plays.insert(play_and_alias);
                }
            }
        }
    }
    // Checcks the validity of the given theatre
    if (!theatreFound) {
        cout << THEATRE_NOT_FOUND << endl;
    } else {
        for (const string& play : plays) {
            cout << play << endl;
        }
     }
}

// A comparator struct to sort the plays'name alphabetically
struct PlayComparator {
    bool operator()(const std::string& a, const std::string& b) const {
        return a < b;
    }
};

void plays_in_town(map<string, map<string, map<string, vector<pair<string, string>>>>>& theatreData,
                   string given_town) {
    map<string, multimap<string, int, PlayComparator>> sortedTheatre;
    bool townFound = false;

    for (const auto& town : theatreData) {
        if (town.first == given_town) {
            townFound = true;
            for (const auto& theatre : town.second) {
                multimap<string,int, PlayComparator> availableSeat;               
                for (const auto& play : theatre.second) {                  
                    int finalSeats = 0;
                    bool noneFound = false;

                    for (const auto& player : play.second) {
                          int seatLeft = (player.second == "none") ? 0 : std::stoi(player.second); // Read "none" as 0 and put all the seat values to int
                          finalSeats = seatLeft; // Update the finalSeats for each player encountered

                          if (seatLeft == 0) {
                                noneFound = true;
                                break;
                          }
                     }
                     // If available seat is found in the final seat of the play, add the play and its final available seat
                     if (!noneFound) {
                          vector<string> playNames = split(play.first, '/');
                          string play_and_alias = (playNames.size() == 2) ? playNames[0] + " --- " + playNames[1] : playNames[0];
                          availableSeat.emplace(play_and_alias, finalSeats);
                     }
                }

                if (!availableSeat.empty()) {
                    sortedTheatre[theatre.first] = availableSeat;
                }
          }

        }
    }

    // Checks the validity of the given town
    if (!townFound) {
        cout << TOWN_NOT_FOUND << endl;
    } else {
        for (const auto& theatre : sortedTheatre) {
            for (const auto& play : theatre.second) {
                cout << theatre.first << " : ";
                cout << play.first << " : " << play.second << endl;
            }
        }
        // Prints the result when there is no available seat in the given city
        if (sortedTheatre.empty()) {
            cout << NOT_AVAILABLE << endl;
        }
     }
}

void players_in_play(const map<string, map<string, map<string, vector<pair<string, string>>>>>& theatreData,
                     const std::string& play, const optional<string>& given_theatre = nullopt) {
    map<string, vector<string>> playersByTheatre;
    bool theatreFound = false;

    for (const auto& town : theatreData) {
        for (const auto& theatre : town.second) {
            if (!given_theatre) {
                // When the theatre name is not given or enclosed in " ", the last part of play name is interpreted as theatre name
                vector<string> play_parts = split(play, ' ');
                if (play_parts.size() >= 2) {
                        string theatre_name = play_parts.back();
                        if (theatre_name != theatre.first) {
                            theatreFound = false;
                        }
                // Flags the program not to check the condition of given theatre as it is not given and cannot be extracted from the play name
                } else {
                    theatreFound = true;
                }
            }
            if (given_theatre == theatre.first) {
                theatreFound = true;
            }
            for (const auto& playData : theatre.second) {
                 const string& currentPlay = playData.first;
                 vector<string> playNames = split(currentPlay, '/');
                 for (const auto& playName : playNames) {
                      if (playName == play) {
                          if (!given_theatre|| given_theatre == theatre.first) {
                              for (const auto& player : playData.second) {
                                  playersByTheatre[theatre.first].push_back(player.first);
                              }
                          }
                      }
                  }

            }
        }
    }
    // Checks the presence and validity of the given theatre
    if (!theatreFound) {
        cout << THEATRE_NOT_FOUND << endl;
    } else {
        bool playFound = !playersByTheatre.empty();

        // Prints the sorted players by theater and then by player's forenames
        for (auto& theatrePlayers : playersByTheatre) {
            sort(theatrePlayers.second.begin(), theatrePlayers.second.end());
            for (const auto& playerName : theatrePlayers.second) {
                cout << theatrePlayers.first << " : ";
                cout << playerName << std::endl;
            }
        }
        // Checks the validity of the given play
        if (!playFound) {
            cout << PLAY_NOT_FOUND << endl;
        }
     }
}

// Main function
int main()
{
    // Reads the input file's name
    string inputFile_name = "";
    cout << "Input file: ";
    getline(cin, inputFile_name);
    ifstream inputFile(inputFile_name);
    // Checks if the input file can be opened in a readable mode
    if (not inputFile) {
        cout << FILE_ERROR;
        return EXIT_FAILURE;
    }

    // Defines map to store play information.
    map<string, map<string, map<string, vector<pair<string, string>>>>> theatreData;
    // Checks if the input file met the requirement of the definition
    string line;
    int line_number = 0;

    while (getline(inputFile, line)) {
        line_number++;
        // Splits the line into fields
        vector<string> fields = split(line, ';');
        // Checks if there is missing field in the line
        if (fields.size() < NUMBER_OF_FIELDS) {
            cout << EMPTY_FIELD << line_number << endl;
            return EXIT_FAILURE;
        }
        // Defines the fields from the lines
        string town = fields.at(0);
        string theatre = fields.at(1);
        string play = fields.at(2);
        string player = fields.at(3);
        string numberSeats = fields.at(4);
        // Stores the input file into the map
        theatreData[town][theatre][play].push_back({player, numberSeats});
    }
    inputFile.close();

    while(true) {
        string command;
        cout << PROMPT;
        getline(cin, command);

        if (command == "quit") {
            return EXIT_SUCCESS;
        } else if (command.find("theatres") == 0 && command.find("theatres_") != 0)
        {            
            if (command.length() >  "theatres"s.length()) {
                cout << WRONG_PARAMETERS << endl; // User enters uneccesary parameters
            } else {
                theatres(theatreData);
            }

        } else if (command.find("plays") == 0 && command.find("plays_") != 0) {
            if (command.length() > "plays"s.length()) {
                cout << WRONG_PARAMETERS << endl; // User enters uneccesary parameters
            } else {
                plays(theatreData);
            }

        } else if (command.find("theatres_of_play") == 0) {
            // Gets the given play input in the same line with command
            string given_play = command.substr(17); // 17: the length of the command counted the last space
            // Remove the double quotes given in the given play so that it canbe
            // compared with plays in the function
            given_play.erase(std::remove_if(given_play.begin(), given_play.end(),
                             [](char x) { return x == '"'; }), given_play.end());

            theatres_of_play(theatreData, given_play);

        } else if (command.find("plays_in_theatre") == 0) {
            // Gets the given play input in the same line with command
            string given_theatre = command.substr(17); // 17: the length of the command counted the last space
            // Remove the double quotes given in the given play so that it canbe
            // compared with plays in the function
            given_theatre.erase(std::remove_if(given_theatre.begin(), given_theatre.end(),
                             [](char x) { return x == '"'; }), given_theatre.end());

            plays_in_theatre(theatreData, given_theatre);

        } else if (command.find("plays_in_town") == 0) {
            // Gets the given play input in the same line with command
            string given_town = command.substr(14); // 15: the length of the command counted the last space
            plays_in_town(theatreData, given_town);

        } else if (command.find("players_in_play") == 0) {
                  string given_input = command.substr(16);
                  string play;
                  optional<string> theatre;

                  // Finds the given theatre parameter enclosed in the double quotes " "
                  size_t pos = given_input.find('\"');
                  if (pos != string::npos) {
                      if (pos > 0) {
                          // Play name is identified before the first "
                          play = given_input.substr(0, pos - 1);
                      }
                      // Theatre name is identified before the closing "
                      size_t end_quote_pos = given_input.find('\"', pos + 1);
                      if (end_quote_pos != string::npos) {
                          theatre = given_input.substr(pos + 1, end_quote_pos - pos - 1);
                      } else {
                          theatre = given_input.substr(pos + 1);
                      }
                  } else {
                      play = given_input;
                  }

                  // Calls the function based on the provided input
                  if (!theatre) {
                             players_in_play(theatreData, play);  // Calls the function with only the play name
                  } else {
                             players_in_play(theatreData, play, theatre);  // Calls the function with both play and theater names
                    }
              } else {
                    cout << COMMAND_NOT_FOUND << endl; // User enters unidentified command
              }

        }

}


