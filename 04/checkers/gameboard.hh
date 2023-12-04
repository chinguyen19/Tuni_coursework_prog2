#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include <vector>

// Pelilaudan koko
// Size of the gameboard
const unsigned int SIZE = 8;

// Vasemmanpuoleisimman sarakkeen koko, tarvitaan pelilaudan tulostamisessa
// Width of the left-most column, needed in printing the gameboard
const unsigned int LEFT_COLUMN_WIDTH = 5;

// GameBoard-luokka
// GameBoard class
class GameBoard
{
public:
    // Rakentaja: tarvittaessa voit lisätä parametreja
    // Constructor: you can add parameters if needed
    GameBoard(char character);

    //Create an initial gameboard with given template
    void initBoard();

    // Tulostaa pelilaudan (kunhan olet viimeistellyt metodin).
    // Prints the gameboard (after you have finished the method).
    void print() const;


    // Move given piece to given destination
    bool move_piece(int x1, int y1, int x2, int y2);


    // Prints the total moves pieces left when 'q' is pressed
    void print_summary();

private:
    // Tulostaa annetun pituisen rivin annettua tulostumerkkiä.
    // Prints a line with the given length and fill character.
    void print_line(unsigned int length, char fill_character) const;


    //Attributes of the class
    std::vector < std::vector < char >> board;
    char character_;
    int total_pieces_ = 48;
    int total_moves_ = 0;

};

#endif // GAMEBOARD_HH
