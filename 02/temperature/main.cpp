#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a temperature: ";

    // Write your code here
    float temp1, temp2, temp3;
    cin >> temp1;
    temp2 = (temp1 * 1.8) + 32;
    temp3 = (temp1 -32) / 1.8;
    cout << temp1 << " degrees Celsius is " << temp2 << " degrees Fahrenheit" << endl;
    cout << temp1 << " degrees Fahrenheit is " << temp3 << " degrees Celsius" << endl;
    return 0;
}
