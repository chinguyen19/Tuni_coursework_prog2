#include "book.hh"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

Book::Book(string const& author, string const& name):
    author_(author), name_(name), loaned_(false) {}

void Book::loan(const Date& date) {
    if (loaned_) {
        std::cout << "Already loaned: cannot be loaned" << std::endl;
    } else {
        loaned_ = true;
        loan_date_ = date;
        due_date_ = loan_date_;
        due_date_.advance(28);
    }
}

void Book::print (){
    cout << author_ << " : " << name_ << endl;
    if (loaned_) {
        cout << "- loaned: ";
        Date loanDate = loan_date_;
        loanDate.print();
        cout << "- to be returned: ";
        Date returnDate = due_date_;
        returnDate.print();
        //cout << endl;
    } else {
        cout << "- available" << endl;
    }
}

void Book::renew() {
    if (loaned_) {
        due_date_.advance(28);
    } else {
        cout << "Not loaned: cannot be renewed" << endl;
    }
}

void Book::give_back() {
    loaned_ = false;
}
