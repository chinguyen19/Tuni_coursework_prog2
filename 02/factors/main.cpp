#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a positive number: ";

    // Write your code here
    int number;
    int factor1 = 0;
    int factor2 = 0;
    cin >> number;
    if (number <= 0) {
       cout <<  "Only positive numbers accepted" << endl;
    }  else {
        for (int i = 1; i * i <= number; i++) {
            if (number % i == 0) {
                factor1 = i;
                factor2 = number / i;
            }
        }
        cout << number << " = " << factor1 << " * " << factor2 << endl;
    }

    return 0;
}
