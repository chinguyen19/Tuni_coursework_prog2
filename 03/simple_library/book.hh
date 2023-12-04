#ifndef BOOK_HH
#define BOOK_HH
#include <string>
using namespace std;
#include "date.hh"

class Book
{
public:
    Book(string const& author, string const& name);
    void loan(const Date& date);
    void renew();
    void give_back();
    void print();

private:

    string author_;
    string name_;
    int loan_period_;
    bool loaned_;
    Date due_date_;
    Date loan_date_;


};

#endif // BOOK_HH
