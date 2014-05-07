// Andrew Backes, SID: 403 925 529
// May 6, 2012
// HW4 - Modified Art Inventory I/O
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

const int NEWLINE_LENGTH = 2;

const int NAME_SIZE = 30;	//Plus comma
const int ARTIST_SIZE = 20;	//Plus comma
const int YEAR_SIZE = 5;	//Plus comma
const int PRICE_SIZE = 15;	//Plus new line

const int RECORD_SIZE = NAME_SIZE + 1 + ARTIST_SIZE + 1 + YEAR_SIZE + 1 + PRICE_SIZE + NEWLINE_LENGTH;

class Artwork
{
public:
	string artist;
	string title;
	int year;
	double price; 
	
	void print(ostream &output_stream) const {
		output_stream << setw(NAME_SIZE) << title << "," << setw(ARTIST_SIZE) << artist << "," << 
			setw(YEAR_SIZE) << year << "," << setw(PRICE_SIZE) << setprecision(15) << price << endl; }
};

double string_to_double(string s)
{
	istringstream instr(s);
	double x;
	instr >> x;
	return x;
}
int string_to_int(string s)
{
	istringstream instr(s);
	int x;
	instr >> x;
	return x;
}

bool compare_date(Artwork artItem1, Artwork artItem2) {
	//This is the compare function for the sort algorithm
	//Output: true if the first item comes before the second item.
	if(artItem1.year < artItem2.year)
		return true;
	else
		return false;
}

bool random_access_read(string input_file_name, vector<Artwork> * artInventory ) {
	//Output: "false" for failure, "true" for success.
	
	ifstream input_file_stream;

	input_file_stream.open(input_file_name.c_str());
	if (input_file_stream.fail() == true) 
	{
		cout << "Error reading " << input_file_name << endl;
		return false;
	}
	cout << "Input file data: " << endl;
	
	input_file_stream.seekg(0,ios::end); // Go to the end of the file.
	int num_of_records = input_file_stream.tellg() / RECORD_SIZE;

	for(int i = 0; i < num_of_records; i++) {
		input_file_stream.seekg(i*RECORD_SIZE, ios::beg);
		string line_data;
		getline(input_file_stream,line_data);
		Artwork new_inventory_entry;
		new_inventory_entry.title = line_data.substr(0,NAME_SIZE);
		new_inventory_entry.artist = line_data.substr(NAME_SIZE + 1,ARTIST_SIZE);
		new_inventory_entry.year = string_to_int(line_data.substr(NAME_SIZE + ARTIST_SIZE + 2, YEAR_SIZE));
		new_inventory_entry.price = string_to_double(line_data.substr(NAME_SIZE + ARTIST_SIZE + YEAR_SIZE + 3, PRICE_SIZE));
		(*artInventory).push_back(new_inventory_entry);
		new_inventory_entry.print(cout);
	}
	input_file_stream.close();
	return true;
}

bool random_access_save(string output_file_name, vector<Artwork> * artInventory) {
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

void change_vanGogh_to_priceless(string * file_name) {
	string priceless = "      priceless";
	
	fstream file_stream;
	file_stream.open((*file_name).c_str());
	file_stream.seekg(0, ios::end); // Go to the end of file.
	int num_of_records = file_stream.tellg() / RECORD_SIZE;
	
	for(int i = 0; i < num_of_records; i++) {
		file_stream.seekg(i*RECORD_SIZE, ios::beg);
		string line_data;
		getline(file_stream,line_data);
		if(line_data.substr(NAME_SIZE + 1, ARTIST_SIZE) == "    Vincent van Gogh")
		{
			cout << "Record " << i+1 << " is Vincent van Gogh. Changed price to \"priceless\"" << endl;
			file_stream.seekp((i*RECORD_SIZE) + NAME_SIZE + 1 + ARTIST_SIZE + 1 + YEAR_SIZE + 1, ios::beg);
			file_stream << priceless;
		}
	} 

	file_stream.close();
}

int main(int argv, char* argc[]) {
	vector<Artwork> artInventory;
	
	string input_file_name = "Inventory_formatted.txt.";
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
	if(random_access_read(input_file_name, &artInventory) == false) //"false" means that there was an error reading the file.
		return 1;

	//Prompt to add more art:
	cout << endl;
	prompt_to_add_art(&artInventory);
	
	//Sort the vector by date:
	sort( artInventory.begin(), artInventory.end(), compare_date);

	//Save the file:
	cout << endl;
	if(random_access_save(output_file_name, &artInventory) == false) //"false" means that there was an error saving the file.
		return 1;

	//Use random access to change the price of van Gogh paintings to 'priceless'
	change_vanGogh_to_priceless(&output_file_name);
	
	system("PAUSE");
	return 0;
}