#include <iostream>
#include <string>
#include <vector>


// TODO: Implement split function here
std::vector<std::string> split(const std::string& string, char separator, bool ignore_empty = false) {
    std::vector<std::string> parts;
    std::string part;
    bool consecutive_separator = false;

    for (char c:string) {
        if (c == separator) {
            if (!ignore_empty || !part.empty()) {
                parts.push_back(part);
            }
            part.clear();
            consecutive_separator = true;
        }
        else {
            part += c;
            consecutive_separator = false;
        }
    }

    if (!ignore_empty || !part.empty() || consecutive_separator) {
        parts.push_back(part);
    }
    return parts;
}
// Do not change main function


int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
