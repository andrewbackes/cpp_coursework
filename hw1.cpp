///////////////////////////////////////////////////
// Andrew Backes - SID: 403-925-529
// PIC 10B - Homework 1
///////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

class Person
{
	public:
		string name;
		int popularity; //keeps track of how many other people have this person as their best friend.
		Person * bestfriend;
		
		Person() {
			popularity = 0; }
		void set_best_friend(Person * setFriend) {
			//input:	pointer to the person's best friend
			//output:	void. sets the person's best friend and also increases the best friends popularity.
			bestfriend = setFriend;
			(*setFriend).increase_popularity(); }
		void increase_popularity() {
			popularity++; }
};

void printTable(vector<Person> *NameTable) {
	//input:	a reference to a vector of persons
	//output:	void. prints out the vector of Persons nicely on the screen.
	cout << endl;
	cout << setfill('-') << setw(80) << "-";
	cout << setfill(' ') << setw(15) << "Name" << setw(15) << "Best Friend" << setw(15) << "Popularity" << endl;
	cout << setfill('-') << setw(80) << "-" << setfill(' ');

	for(int i=0; i< NameTable->size(); i++) {
		cout << setw(15) << NameTable->at(i).name << setw(15) << NameTable->at(i).bestfriend->name << setw(15) << NameTable->at(i).popularity << endl;
	}
	cout << endl;
}

int main(){
	//This program asks the user for a list of people 
	//then asks for those people's best friends.
	
	string userInput;
	Person tempPerson;
	vector<Person> NameList; //stores the names the user userInputs
	bool foundBestFriendFlag; //used to make sure the user userInputs a valid name for the best friend.

	cout << "Please input a list of names. Input a blank entry when done.\n" << "Name: ";
	getline(cin, userInput);

	while(!userInput.empty()) {
		//Keep asking for names until there is a blank entry.
		tempPerson.name = userInput;
		NameList.push_back(tempPerson);
		cout << "Name: ";
		getline(cin, userInput); 
	} 

	for (int i=0; i< NameList.size(); i++) {
		//Now ask for each person's best friend.
		foundBestFriendFlag = false; 
		while(!foundBestFriendFlag) {
			//Loop until the user inputs a valid best friend. 
			cout << "Who is " << NameList.at(i).name << "'s best friend? ";
			getline(cin,userInput);
			for (int j=0; j < NameList.size(); j++) {
				//Locate the name in the vector which matches the best friend's name.			
				if(NameList.at(j).name == userInput) {
					NameList.at(i).set_best_friend(&NameList.at(j));
					foundBestFriendFlag = true;
				}
			}
			if(!foundBestFriendFlag) {
				cout << "Invalid best friend. Please input a name from your origional list.\n"; }
		}
	}
		
	printTable(&NameList);

	system("PAUSE");
	return 0;
}