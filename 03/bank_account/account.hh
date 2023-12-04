#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <string>

class Account
{
public:
    // Constructor
    Account(const std::string& owner, bool has_credit = false);

    // More methods

    void set_credit_limit(double limit);
    void take_money(double amount);
    void save_money(double amount);
    void transfer_to(Account& destination, double amount);
    void print() const;

private:
    // Generates IBAN (based on running_number_ below).
    // Allows no more than 99 accounts.
    void generate_iban();

    // Used for generating IBAN.
    // Static keyword means that the value of running_number_ is the same for
    // all Account objects.
    // In other words, running_number_ is a class-wide attribute, there is
    // no own copies of it for each object of the class.
    static int running_number_;

    // More attributes/methods
    std::string owner_;
    std::string iban_;
    double balance_;
    bool has_credit_;
    double credit_limit_;

};

#endif // ACCOUNT_HH
