#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    cout << "Enter a number: ";
    int num;
    int result;
    cin >> num;
    result = static_cast<int32_t>(num) * num * num;
    if (cbrt(result) != num) {
        cout << "Error! The cube of " << num << " is not " << result << "." << endl;
    } else if (result < 0) {
        cout << "Error! The cube of " << num << " is not " << result << "." << endl;
    } else {
        cout << "The cube of " << num << " is " << result << "." << endl;
    }
}
