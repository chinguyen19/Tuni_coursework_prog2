#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

void printSubnetwork(const std::string& id, const std::map<std::string, std::vector<std::string>>& relationships, int indent = 0) {
    if (relationships.find(id) != relationships.end()) {
        for (int i = 0; i < indent; i++) {
            std::cout << ".";
        }
        std::cout << id << std::endl;
        for (const std::string& recruitId : relationships.at(id)) {
            printSubnetwork(recruitId, relationships, indent + 2);
        }
    } else {
        // If the person has no recruits or is not enlisted, just print their ID
        for (int i = 0; i < indent; i++) {
            std::cout << ".";
        }
        std::cout << id << std::endl;
    }
}

// Recursive function to calculate subnetwork size
int countSubnetworkSize(const std::string& id, const std::map<std::string, std::vector<std::string>>& relationships) {
    if (relationships.find(id) == relationships.end()) {
        return 0; // This person has no recruits; the size is 0 (no one else in the subnetwork).
    }

    int size = 0; // Start with no recruits (excluding the current person).
    for (const std::string& recruitId : relationships.at(id)) {
        size +=1;
        size += countSubnetworkSize(recruitId, relationships);
    }

    return size;
}
// Recursive function to calculate the depth of the subnetwork
int calculateDepth(const std::string& id, const std::map<std::string, std::vector<std::string>>& relationships) {
    if (relationships.find(id) == relationships.end()) {
        return 1; // This person has no recruits; the depth is 1 (only the person itself).
    }

    int maxDepth = 0;
    for (const std::string& recruitId : relationships.at(id)) {
        int recruitDepth = calculateDepth(recruitId, relationships);
        if (recruitDepth > maxDepth) {
            maxDepth = recruitDepth;
        }
    }

    return maxDepth + 1; // ADD 1 for the current person
}



int main()
{
    // TODO: Implement the datastructure here
    std::map<std::string, std::vector<std::string>> relationships;

    while(true)
    {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        std::string command = parts.at(0);

        if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // TODO: Implement the command here!
            // Checks if the recruiter id1 exsits in the relationships dict
            if (relationships.find(id1) == relationships.end()) {
                        // If id1 does not exist, store the relationship
                        relationships[id1] = std::vector<std::string>{id2};

                        } else {
                        relationships[id1].push_back(id2);
                        }

        }
        else if(command == "P" or command == "p")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            printSubnetwork(id, relationships);
        }
        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            int size = countSubnetworkSize(id, relationships);
                        std::cout << size << std::endl;

        }
        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            int depth = calculateDepth(id, relationships);
                       std::cout << depth << std::endl;

        }
        else if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
