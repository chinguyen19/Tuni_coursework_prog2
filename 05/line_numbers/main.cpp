#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    string input_filename = "";
    string output_filename = "";
    cout << "Input file: ";
    getline(cin, input_filename);
    cout << "Output file: ";
    getline(cin, output_filename);

    ifstream file_object(input_filename);
    if ( not file_object ) {
        cout << "Error! The file " << input_filename << " cannot be opened." << endl;
        return EXIT_FAILURE;
    } else {
    ofstream outputFile(output_filename);
    string line;
    int lineNumber = 1;
    while (getline(file_object, line)) {
            outputFile << lineNumber << " " << line << std::endl;
            lineNumber++;
        }
    outputFile.close();
    }
    file_object.close();

}
