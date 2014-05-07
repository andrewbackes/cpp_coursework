// Andrew Backes, SID: 403 925 529
// April 29, 2012
// HW3 - Art Inventory I/O
//		Description: Takes in 2 filenames as command line arguements.
//		First sorts the artwork in one file by date, then saves it to the other file. 

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Artwork
{
public:
	string artist;
	string title;
	int year;
	double price; 
	
	void print(ostream &output_stream = cout) const {
		output_stream << title << ", " << artist << ", " << year << ", " << setprecision(13) << price << endl; }
};

bool compare_date(Artwork artItem1, Artwork artItem2) {
	//This is the compare function for the sort algorithm
	//Output: true if the first item comes before the second item.
	if(artItem1.year < artItem2.year)
		return true;
	else
		return false;
}

bool read_file_data(string input_file_name, vector<Artwork> * artInventory ) {
	//Output: "false" for failure, "true" for success.
	
	ifstream input_file_stream;
	string line_data;
	char comma;

	input_file_stream.open(input_file_name.c_str());
	if (input_file_stream.fail() == true) 
	{
		cout << "Error reading " << input_file_name << endl;
		return false;
	}
	cout << "Input file data: " << endl;
	while (getline(input_file_stream,line_data)) {
		istringstream line_stream(line_data);
		Artwork new_inventory_entry;
		getline(line_stream, new_inventory_entry.title, ',');
		getline(line_stream, new_inventory_entry.artist, ',');
		line_stream >> new_inventory_entry.year;
		line_stream >> comma;
		line_stream >> new_inventory_entry.price;
		(*artInventory).push_back(new_inventory_entry);
		new_inventory_entry.print(cout);
	}
	input_file_stream.close();
	return true;
}

bool save_file_data(string output_file_name, vector<Artwork> * artInventory) {
	//Output: "false" for failure, "true" for success.
	ofstream output_file_stream;
	output_file_stream.open(output_file_name);
	if (output_file_stream.fail() == true) {
		cout << "Error reading " << output_file_name << endl;
		system("PAUSE");
		return false;
	}
	cout << "Output file data: " << endl;
	for (int i=0; i < (*artInventory).size() ; i++ ) 
	{
		(*artInventory).at(i).print(output_file_stream); //Print to file.
		(*artInventory).at(i).print(cout); //Print to screen.
	}
	output_file_stream.close();
	return true;
}

void prompt_to_add_art(vector<Artwork> * artInventory) 
{
	string user_input;
	while(user_input != "n") {
		if(user_input == "y") {
			Artwork new_inventory_entry;
			cout << "Title: ";
			getline(cin, new_inventory_entry.title);
			cout << "Artist: ";
			getline(cin, new_inventory_entry.artist);
			cout << "Year: ";
			cin >> new_inventory_entry.year;
			cin.ignore();
			cout << "Price: ";
			cin >> new_inventory_entry.price;
			cin.ignore();
			(*artInventory).push_back(new_inventory_entry);
		}
		cout << "Would you like to add more artwork to the inventory? (y/n)";
		getline(cin, user_input);
	}
}

int main(int argv, char* argc[]) {
	vector<Artwork> artInventory;

	string input_file_name = "exampleInventory.txt.";
	string output_file_name = "output.txt";
	
	if(argv > 1 ) {
		//Check to make sure there are command line arguements
		input_file_name = string(argc[1]);
		output_file_name = string(argc[2]);	
	}
	
	cout << "Input file: " << input_file_name << endl;
	cout << "Output file: " << output_file_name << endl;
	
	//Read the file:
	cout << endl;
	if(read_file_data(input_file_name, &artInventory) == false) //"false" means that there was an error reading the file.
		return 1;

	//Prompt to add more art:
	cout << endl;
	prompt_to_add_art(&artInventory);
	
	//Sort the vector by date:
	sort( artInventory.begin(), artInventory.end(), compare_date);

	//Save the file:
	cout << endl;
	if(save_file_data(output_file_name, &artInventory) == false) //"false" means that there was an error saving the file.
		return 1;

	system("PAUSE");
	return 0;
}