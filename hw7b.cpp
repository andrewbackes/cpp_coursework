// Andrew Backes SID: 403-925-529
// May 29, 2012
// HW7B - P13.4 - Word counter for a file using multiset

#include <iostream>
#include <set>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {
	
	//File name to open:
	string file_name = "hw7b.cpp";
	multiset<string> words;
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

	while( !file_stream.eof() ){
		string word_input;
		file_stream >> word_input;
		words.insert(word_input);
	}
	
	multiset<string>::iterator pos;
	set<string> shown_words;
	for (pos = words.begin(); pos != words.end(); pos++) {
		int word_count = 0;
		if(shown_words.count(*pos) == 0) //This is so that we won't show duplicates.
		{
			word_count = words.count(*pos);
			cout << " " << setw(40) << left << *pos << word_count << " times" << endl;
			shown_words.insert(*pos);
		}
	}

	system("PAUSE");
	return 0;
}