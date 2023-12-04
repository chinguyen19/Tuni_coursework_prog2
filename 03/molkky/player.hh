#ifndef PLAYER_HH
#define PLAYER_HH
#include <string>

using namespace std;

class Player
{
public:
    Player(string const& name);
    string get_name();
    int get_points();
    bool has_won();
    void add_points(int pts);

private:
   string name_;
   int points_;
   bool has_won_;

};

#endif // PLAYER_HH
