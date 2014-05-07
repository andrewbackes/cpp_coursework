// Andrew Backes SID: 403-925-529
// May 29, 2012
// HW7c - P13.5 - Word counter for a file using map.

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {
	
	//File name to open:
	string file_name = "hw7c.cpp";
	map<string, int> words;
	ifstream file_stream;

	cout << "This program counts the words in a file and stores it to a multiset" << endl << endl;
	cout << setw(40) << left << "WORDS" << "COUNT" << endl;

	//Open the file:
	file_stream.open(file_name.c_str());
	//Check to make sure it opened:
	if (file_stream.fail()) {
		cout << "Error reading file." << endl;
		return 0;
	}

	//Start going through the file:
	
	while( !file_stream.eof() ){
		string word_input;
		file_stream >> word_input;
	
		//Start counting:
		map<string, int>::iterator pos = words.find(word_input);
		if( pos == words.end() ) //Then the word is not yet on the list
			words[word_input] = 1;
		else // Then the word is already on the list
			words[word_input]++;
	}
	
	//Print the results:
	map<string, int>::iterator pos;
	for (pos = words.begin(); pos != words.end(); pos++) {
		cout << " " << setw(40) << left << (*pos).first << (*pos).second << " times" << endl;
	}

	system("PAUSE");
	return 0;
}