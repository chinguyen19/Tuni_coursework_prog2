#include <iostream>
#include <cmath>
using namespace std;

unsigned long int factorial(unsigned int n) {
    unsigned long long result = 1;

    for (unsigned int i = 1; i <= n; ++i) {
        result *= i;
    }

    return result;
}

int main() {
    unsigned long int result;

    cout << "Enter the total number of lottery balls: ";
    int num;
    cin >> num;
    cout << "Enter the number of drawn balls: ";
    int drawn;
    cin >> drawn;
    if ((num < 0) or (drawn < 0)) {
        cout << "The number of balls must be a positive number." << endl;
    } else if (drawn > num) {
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
    } else {
        result = factorial(num)/(factorial(num-drawn)*factorial(drawn));
        cout << "The probability of guessing all " << drawn << " balls correctly is 1/" << result << endl;
    }
}
