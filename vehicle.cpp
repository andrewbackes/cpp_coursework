#include <iostream>
#include <string>
#include <iomanip>

#include "vehicle.h"

using namespace std;

// ---------------------------------------------
// Base Class: Vehicle member functions
// ---------------------------------------------

void Vehicle::printFeatures() {
	cout << "Price: " << setw(10) << left << price;
	cout << "Year: " << setw(8) << left << year;
	cout << "Color: " << setw(10) << left << color;
	cout << "MPG: " <<setw(6) << left << mpg;
	cout << "Doors: " << setw(3) << left << numberOfDoors;
}

Vehicle::Vehicle() {	
	price = 1000;
	year = 1986;
	numberOfDoors = 4;
	mpg = 20;
	color = "brown";
}

void Vehicle::prompt_for_basic_vehicle_info() {
	string input; 
	cout << "Please enter some information about this car." << endl;
	cout << "Price: ";
	cin >> price;
	cout << "Year: ";
	cin >> year;
	cout << "Color: ";
	cin >> color;
}

// ---------------------------------------------
// Derived Class: SportsCar member functions
// ---------------------------------------------

SportsCar::SportsCar() {
	numberOfDoors = 2;
	Vehicle::prompt_for_basic_vehicle_info();
}

// ---------------------------------------------
// Derived Class: Sedan member functions
// ---------------------------------------------

void Sedan::prompt_for_hybrid_info() {
	string input; 
	cout << "Hybrid (Y/N): ";
	cin >> input;
	if ( input[0] == 'y' || input[0] == 'Y')
	{
		isHybrid = true;
		cout << "MPG: ";
		cin >> mpg;
	}
}

Sedan::Sedan() {
	prompt_for_basic_vehicle_info();
	prompt_for_hybrid_info();
}

void Sedan::printFeatures() {
	Vehicle::printFeatures();
	if (isHybrid == 1) 
		cout << "Hybrid: " << setw(2) << left << "Y";
	else
		cout << "Hybrid: " << setw(2) << left << "N";
}

// ---------------------------------------------
// Derived Class: SUV Class functions
// ---------------------------------------------
// note: All of these functions are almost exactly the same as the Sedan class,
//       except for the constructor setting mpg=10.
//       If the assignment didn't specify this, I would have done it more effeciently. 

SUV::SUV() {
	mpg = 10;
	prompt_for_basic_vehicle_info();
	prompt_for_hybrid_info();
}

void SUV::printFeatures() {
	Vehicle::printFeatures();
	if (isHybrid == 1) 
		cout << "Hybrid: " << setw(2) << left << "Y";
	else
		cout << "Hybrid: " << setw(2) << left << "N";
}

void SUV::prompt_for_hybrid_info() {
	string input; 
	cout << "Hybrid (Y/N): ";
	cin >> input;
	if ( input[0] == 'y' || input[0] == 'Y')
	{
		isHybrid = true;
		cout << "MPG: ";
		cin >> mpg;
	}
}


