#include "account.hh"
#include <iostream>
#include <string>

Account::Account(const std::string& owner, bool has_credit):

    owner_(owner), has_credit_(has_credit){generate_iban();}


// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

void Account::set_credit_limit(double limit)
{
    if (has_credit_) {
        credit_limit_ = limit;
        //std::cout << "Credit limit set to: " << credit_limit_ << std::endl;
    }
    else
    {
        std::cout << "Cannot set credit limit: the account has no credit card" << std::endl;
    }
}
void Account::take_money(double amount)
{
    if (balance_ >= amount && has_credit_ == false)
        {
            balance_ -= amount;
            std::cout << amount << " euros taken: new balance of " << iban_ << " is " << balance_ << " euros " <<   std::endl;
        }
    else if (balance_ < amount && has_credit_)
    {
       if ((balance_ - amount) < -credit_limit_) {

        std::cout << "Cannot take money: credit limit overflow" << std::endl;}
       else {
        balance_ -= amount;
        std::cout << amount << " euros taken: new balance of " << iban_ << " is " << balance_ << " euros " <<   std::endl;}
    }
    else
        {
            std::cout << "Cannot take money: balance underflow" << std::endl;
        }
}

void Account::save_money(double amount)
{
    balance_ += amount;
        //std::cout << amount << " saved to the account." << std::endl;
}

void Account::transfer_to(Account& destination, double amount)
{
    if (balance_ >= amount && has_credit_ == false)
       {
           balance_ -= amount;
           destination.balance_ += amount;
           std::cout << amount << " euros taken: new balance of " << iban_ << " is " << balance_ << " euros " << std::endl;
    }
    else if (balance_ < amount && has_credit_)
    {
       if ((balance_ - amount) < -credit_limit_) {

        std::cout << "Cannot take money: credit limit overflow" << std::endl;
        std::cout << "Transfer from " <<  iban_ << " failed" << std::endl;}
       else {
        balance_ -= amount;
        destination.balance_ += amount;
        std::cout << amount << " euros taken: new balance of " << iban_ << " is " << balance_ << " euros " <<   std::endl;}
    }
    else
       {
           std::cout << "Cannot take money: balance underflow" << std::endl;
           std::cout << "Transfer from " <<  iban_ << " failed" << std::endl;
       }

}

void Account::print() const
{
    std::cout << owner_ << " : " << iban_ << " : " << balance_ << " euros\n" << std::endl;

//    if (has_credit_)
//    {
//        std::cout << "Credit limit: " << credit_limit_ << std::endl;
//    }
//    std::cout << std::endl;
}
