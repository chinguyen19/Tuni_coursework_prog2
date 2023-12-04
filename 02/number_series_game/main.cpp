#include <iostream>


int main()
{
    std::cout << "How many numbers would you like to have? ";

    // Write your code here
    int number;
    int i = 0;
    std::cin >> number;
    while (i < number) {
        i++;
        if ((i % 3 == 0) && (i % 7 == 0)) {
            std::cout << "zip boing" << std::endl;
        } else if (i % 7 == 0) {
            std::cout << "boing" << std::endl;
        } else if (i % 3 == 0) {
            std::cout << "zip" << std::endl;
        } else {
            std::cout << i << std::endl;
        }
    }
    return 0;
}
