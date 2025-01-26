#include <iostream>
#include <cmath>

using namespace std;

void absValue();
void squareRoot();
void cubeRoot();
void power();
void naturalLog();
void logTenValue();
void hypotenuse();
void multiplication();
void division();
void addition();
void subtraction();

int main() {
    int x;
    cout << "Enter a value 1 through 11:  \n"
         << " 1.) For absolute value. \n"
         << " 2.) For square root. \n"
         << " 3.) For cube root. \n"
         << " 4.) For power of. \n"
         << " 5.) For natural logarithms. \n"
         << " 6.) For base 10 logarithms. \n"
         << " 7.) For finding hypotenuse value. \n"
         << " 8.) For multiplication. \n"
         << " 9.) For division. \n"
         << " 10.) For addition. \n"
         << " 11.) For subtraction. \n";
    cin >> x;

    switch (x) {
        case 1: absValue(); break;
        case 2: squareRoot(); break;
        case 3: cubeRoot(); break;
        case 4: power(); break;
        case 5: naturalLog(); break;
        case 6: logTenValue(); break;
        case 7: hypotenuse(); break;
        case 8: multiplication(); break;
        case 9: division(); break;
        case 10: addition(); break;
        case 11: subtraction(); break;
        default: cout << "Invalid choice." << endl;
    }

    return 0;

}

void absValue() {
    int x;

    cout << "Enter a number to find its' absolute value:" << endl;
    cin >> x;
    cout << "The absolute value of " << x << " is: " << abs(x) << endl;
}

void squareRoot() {
    double x;

    cout << "Enter a number to find its' square root: " << endl;
    cin >> x;
    cout << "The square root of " << x << " is: " << sqrt(x) << endl;
}

void cubeRoot() {
    double x;

    cout << "Enter a number to find its' cube root: " << endl;
    cin >> x;
    cout << "The cube root of " << x << " is: " << cbrt(x) << endl;
}

void power() {
    double x, y;

    cout << "Enter a number to find the value after raised to a power: " << endl;
    cin >> x >> y;
    cout << "The value of " << x << " raised to the power of " << y << " is: " << pow(x, y) << endl;
}

void naturalLog() {
    double x;

    cout << "Enter a number to find its' natural logarithm: " << endl;
    cin >> x;
    cout << "The natural logarithm of " << x << " is: " << log(x) << endl;
}

void logTenValue() {
    double x;

    cout << "Enter a number to find its' base-10 logarithm: " << endl;
    cin >> x;
    cout << "The base-10 logarithm value of " << x << " is: " << log10(x) << endl;
}

void hypotenuse() {
    double x, y;

    cout << "Enter two sides of a triangle to find the hypotenuse: " << endl;
    cin >> x;
    cout << "The hypotenuse of a triangle with sides " << x << " and " << y << " is: " << hypot(x, y) << endl;
}

void multiplication() {
    double x, y;

    cout << "Enter two numbers to multiply them together: " << endl;
    cin >> x >> y;
    cout << x << " * " << y << " = " << x * y << endl;
}

void division() {
    double x, y;

    cout << "Enter two numbers to divide them: " << endl;
    cin >> x >> y;
    cout << x << " / " << y << " = " << x / y << endl;
}

void addition() {
    double x, y;

    cout << "Enter two numbers to add them together: " << endl;
    cin >> x >> y;
    cout << x << " + " << y << " = " << x + y << endl;
}

void subtraction() {
    double x, y;

    cout << "Enter two numbers to subtract them: " << endl;
    cin >> x >> y;
    cout << x << " - " << y << " = " << x - y << endl;
}