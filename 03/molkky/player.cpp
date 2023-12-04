#include "player.hh"
#include <iostream>
#include <string>

using namespace std;

Player::Player(string const& name):
    name_(name), points_(0), has_won_(false){}

string Player::get_name() {
    return name_;
}

int Player::get_points(){
    return points_;
}

void Player::add_points(int pts) {
    if (points_+pts == 50) {
        points_ += pts;
        has_won_ = true;
    } else if (points_ + pts < 50) {
        points_+= pts;
        has_won_ = false;
    } else {
        points_ = 25;
        cout << name_ << " gets penalty points!" << endl;
        has_won_ = false;
    }
}

bool Player::has_won() {
    if (has_won_) {
        return true;
 }  else {
            return false;
        }
}

