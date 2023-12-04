#include "gameboard.hh"
#include <iostream>
#include <string>


GameBoard::GameBoard(char character):
    character_(character)
{
    board = std::vector < std::vector < char >> (SIZE, std::vector < char > (SIZE, ' '));
}

void GameBoard::initBoard()
{
    //Mark the character on board at described locations for the initial board
    for (unsigned int i : {0, 1, 6, 7})
    {
        for (unsigned int j = 0; j < SIZE; j++)
        {
             board.at(i).at(j) = character_;
        }
    }
    for (unsigned int i = 0; i < SIZE; i++)
    {
        for (unsigned int j : {0, 1, 6, 7})
        {
            board.at(i).at(j) = character_;
        }
    }
}

void GameBoard::print() const
{
    // Tulostetaan yläreuna
    // Printing upper border
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '=');

    // Tulostetaan otsikkorivi
    // Printing title row
    std::cout << "|   | ";
    for(unsigned int i = 0; i < SIZE; ++i)
    {
        std::cout << i + 1 << " ";
    }
    std::cout << "|" << std::endl;

    // Tulostetaan viiva otsikkorivin alle
    // Printing line after the title row
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '-');

    // Tulostetaan pelilaudan varsinainen sisältö
    // Printing the actual content of the gameboard
    for(unsigned int i = 0; i < SIZE; ++i)
    {
        std::cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < SIZE; ++j)
        {
            // TODO:
            // Tulosta tässä tyhjä tai pelilaudan alkio (i, j)
            // Print here empty or the element (i, j) in the gameboard
            std::cout << board.at(i).at(j) << " ";
        }
        std::cout << "|" << std::endl;
    }

    // Tulostetaan alareuna
    // Printing lower border
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '=');
}

void GameBoard::print_line(unsigned int length, char fill_character) const
{
    for(unsigned int i = 0; i < length; ++i)
    {
        std::cout << fill_character;
    }
    std::cout << std::endl;
}

bool GameBoard::move_piece(int x1, int y1, int x2, int y2)
{
    // Check if the source (x1, y1) has a piece and the destination (x2, y2) is empty
    if (board.at(y1 - 1).at(x1 - 1) == character_ && board.at(y2 - 1).at(x2 - 1) == ' ')
    {
        // Check if the points are on the same diagonal such that there is only one point
         // in the middle of them
        if (abs(x1 - x2) == abs(y1 - y2) && abs(x1 - x2) == 2)
        {
          int middle_x = (x1 + x2)/2;
          int middle_y = (y1 + y2)/2;
          // Check if the middle point has a piece
              if (board.at(middle_x - 1).at(middle_y - 1) == character_)
              {
                // Perform the move: set the destination to the character,
                 // clear the source and the middle point
                  // Update the total moves and the pieces left
                board.at(y2 - 1).at(x2 - 1) = character_;
                board.at(y1 - 1).at(x1 - 1) = ' ';
                board.at(middle_y - 1).at(middle_x - 1) = ' ';
                total_pieces_ -= 1;
                total_moves_ += 1;
                return true;
              } else {
                  return false;
              }
        } else
            {
                return false;
            }
    } else
        {
        return false;
        }
    return 0;
}

void GameBoard::print_summary()
{
    std::cout << total_moves_ << " move(s) made." << std::endl;
    std::cout << total_pieces_ << " piece(s) left." << std::endl;
}
