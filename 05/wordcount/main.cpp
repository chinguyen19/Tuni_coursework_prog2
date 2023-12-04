#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

int main()
{
    string input_filename = "";
    cout << "Input file: ";
    getline(cin, input_filename);
    ifstream file_object(input_filename);
    if (not file_object) {
        cout << "Error! The file " << input_filename << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    map<string, set<int>> wordOccurrences;
        string line;
        int lineNumber = 1;

        while (getline(file_object, line)) {
            istringstream iss(line);
            string word;

            while (iss >> word) {

                wordOccurrences[word].insert(lineNumber);
            }

            lineNumber++;
        }

        file_object.close();

        // Print the word occurrences
        for (const auto& pair : wordOccurrences) {
            cout << pair.first << " " << pair.second.size() << ": ";
            bool first = true;
            for (int line : pair.second) {
                if (!first) {
                    cout << ", ";
                }
                cout << line;
                first = false;
            }
            cout << endl;
        }

        return EXIT_SUCCESS;
 }
