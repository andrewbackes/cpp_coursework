#include <iostream>
#include <string>

using namespace std;

class Vehicle {
public:
	double price;
	int year;
	int numberOfDoors;
	double mpg;
	string color;

	Vehicle(); 
	virtual void printFeatures();
	void prompt_for_basic_vehicle_info();
};

class SportsCar : public Vehicle {
public:
	SportsCar();
};

class Sedan : public Vehicle {
public:
	Sedan();
	bool isHybrid;
	void printFeatures();
	void prompt_for_hybrid_info();
};

class SUV : public Vehicle{
public:
	SUV();
	bool isHybrid;
	void printFeatures();
	void prompt_for_hybrid_info();
};