//	Andrew Backes
//	6/11/2012
//	HW8b - complex numbers

#include <iostream>
#include <string>

using namespace std;

class complex_int {
public:
	complex_int();
	complex_int(int real_value, int imaginary_value);
	int real_part;
	int imaginary_part;
};

complex_int operator+(const complex_int& left, const complex_int& right) {
	complex_int result(left.real_part + right.real_part, left.imaginary_part + right.imaginary_part);
	return result;
}
complex_int operator-(const complex_int& left, const complex_int& right) {
	complex_int result(left.real_part - right.real_part, left.imaginary_part - right.imaginary_part);
	return result;
}
complex_int operator*(const complex_int& left, const complex_int& right) {
	int re = (left.real_part * right.real_part) - (left.imaginary_part * right.imaginary_part);
	int im = (left.real_part * right.imaginary_part) + (right.real_part * left.imaginary_part);
	complex_int result(re, im);
	return result;
}

complex_int::complex_int() {

}

complex_int::complex_int(int real_value, int imaginary_value) {
	real_part = real_value;
	imaginary_part = imaginary_value;
}

ostream& operator<<(ostream& out, complex_int& value) {
	out << value.real_part << ((value.imaginary_part >= 0) ? '+' : '-') << abs(value.imaginary_part) << 'i';
	return out;
}

istream& operator>>(istream& in, complex_int& num) {
	
	in >> num.real_part;
	in >> num.imaginary_part;
	return in;
}

 int main() {
	//This program demonstrate the complex number class
	complex_int number1;
	complex_int number2;

	cout << "This program demonstrates the implementation of the complex numbers class." << endl;
	cout << "Note: input must be of the format a+bi where a and b are integers." << endl << endl;
	cout << "Examples: 2+4i, 0+3i, 9+0i" << endl << endl;
	
	cout << "Please enter a complex number: ";
	cin >> number1;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	cout << "You entered: " << number1 << endl << endl;

	cout << "Please enter another complex number: ";
	cin >> number2;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	cout << "You entered: " << number2 << endl << endl;

	cout << number1 << " + " << number2 << " = " << number1 + number2 << endl;
	cout << number1 << " - " << number2 << " = " << number1 - number2 << endl;
	cout << number1 << " * " << number2 << " = " << number1 * number2 << endl;

	system("PAUSE");
	return 0;
 }