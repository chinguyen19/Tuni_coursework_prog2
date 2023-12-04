#include "gameboard.hh"
#include <iostream>
#include <limits>
#include <string>
#include <vector>


bool isValid(unsigned int x, unsigned int y)
{
    return x >= 1 && x <= SIZE && y >= 1 && y <= SIZE;
}

int main()
{
    char character;
        std::cout << "Enter piece character: ";
        std::cin >> character;

        GameBoard board(character);
        board.initBoard();
        board.print();


    while (true)
    {
        std::cout << "Enter start point (x, y) and destination point (x, y), "
                     "or q to quit: ";

        int x1, y1, x2, y2;
        char ch;

        // Stop the program if 'q' is entered
        if (!(std::cin >> ch) || ch == 'q')
        {
            board.print_summary();
            break; // Exit the loop
        }
        // Put back the character 'ch' to the input stream
        std::cin.unget();

        // Checks if the provided inputs are number
        if (not(std::cin >> x1 >> y1 >> x2 >> y2))
        {
             std::cin.clear();
             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
             std::cout << "Invalid start/destination point." << std::endl;
             continue; // Skip the rest of the loop iteration
        }

        // Checks if the provided inputs are in the board
        if (!isValid(x1, y1) || !isValid(x2, y2))
        {
            std::cout << "Invalid start/destination point." << std::endl;
            continue; // Skip the rest of the loop iteration
        }

        // Checks if the start point and the destination point are the same
        if (x1 == x2 && y1 == y2)
        {
            std::cout << "Invalid start/destination point." << std::endl;
            continue; // Skip the rest of the loop iteration
        }

        // Move the pieces according to the rule of the game
        if(board.move_piece(x1, y1, x2, y2))
        {
            board.print();
            continue;
        } else
        {
            std::cout << "Cannot move from start point to destination point." << std::endl;
            continue;
        }
    }

    return 0;
}
