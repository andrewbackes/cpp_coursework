//
// Andrew Backes, SID: 403 925 529
// PIC 10B - Homework 2 - April 22, 2012
//

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

#include "vehicle.h" 

void printCarsOnLot(vector<SUV*> *SUVList, vector<Sedan*> *SedanList, vector<SportsCar*> *SportsCarList) {
	cout << endl << setfill('-') << setw(80) << "-";
	cout << "Sports Cars on the Lot" << endl;
	cout << setfill('-') << setw(80) << "-" << setfill(' ');
	for(int i= 0; i < (*SportsCarList).size(); i++) {
		(*SportsCarList).at(i)->printFeatures();
		delete (*SportsCarList).at(i); //clear the memory
		cout << endl; }
	
	cout << endl << setfill('-') << setw(80) << "-";
	cout << "Sedans on the Lot" << endl;
	cout << setfill('-') << setw(80) << "-" << setfill(' ');
	for(int i= 0; i < (*SedanList).size(); i++) {
		(*SedanList).at(i)->printFeatures();
		delete (*SedanList).at(i); //clear the memory
		cout << endl; }
	
	cout << endl << setfill('-') << setw(80) << "-";
	cout << "SUVs on the Lot" << endl;
	cout << setfill('-') << setw(80) << "-" << setfill(' ');
	for(int i= 0; i < (*SUVList).size(); i++) {
		(*SUVList).at(i)->printFeatures();
		delete (*SUVList).at(i); //clear the memory
		cout << endl; }
	
	cout << endl;
}

int main() {
	vector<SUV*> SUVsOnLot;
	vector<Sedan*> SedansOnLot;
	vector<SportsCar*> SportsCarsOnLot;
	string userInput = "Yes";	//Set to "Yes" to jumpstart the loop.

	while(userInput[0] != 'n' && userInput[0] != 'N') {
		cout << "Would you like to add a car to the lot? (Y/N): ";
		cin >> userInput;
		if(userInput[0] == 'y' || userInput[0] == 'Y'){
			cout << "1. Sports Car \n";
			cout << "2. Sedan \n";
			cout << "3. SUV \n";
			while(userInput != "1" && userInput != "2" && userInput != "3") {
				cout << "What type of car is this? (1,2, or 3): ";
				cin >> userInput;
				if(userInput == "1") {
					SportsCarsOnLot.push_back(new SportsCar); }
				else if (userInput == "2") {
					SedansOnLot.push_back(new Sedan); }
				else if (userInput == "3") {
					SUVsOnLot.push_back(new SUV); }
			}
		}
	}

	printCarsOnLot(&SUVsOnLot, &SedansOnLot, &SportsCarsOnLot);

	system("PAUSE");
	return 0;
}