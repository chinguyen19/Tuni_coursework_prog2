// Note that there is no need for "using namespace std",
// since no C++ standard libraries are used.

double addition(double left, double right) {
    return left + right;
}


double subtraction(double left, double right) {
    return left - right;
}


double multiplication(double left, double right) {
    return left * right;
}


double division(double left, double right) {
    return left / right;
}

double exponential(double left, double right) {
    int count = 0;
    double result = 1.0;
    while (count < right) {
        result *= left;
        count += 1;
    }
    return result;
}
