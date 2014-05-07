// Andrew Backes SID: 403-925-529
// May-29-2012
// HW7A - Sieve of Eratosthenes

#include <iostream>
#include <set>
#include <math.h>

using namespace std;

int main() {
	set<int> numbers;

	double user_input = 0;

	cout << "Please enter a valid number: ";
	cin >> user_input;

	//Fill the set with all the of the numbers up to the one inputed:
	for ( int i = 1; i <= user_input ; i++ ) {
		numbers.insert(i);
	}

	//Begin removing elements:
	double root_max = sqrt(user_input);
	for (double root = 2; root <= root_max ;  root++ ){
		for( int j = 1; j <= user_input; j++) {
			numbers.erase( (int)j*root );
		}
	}

	//Print out the results:
	cout << "The prime numbers less than your input are: ";
	set<int>::iterator pos;
	for (pos = numbers.begin(); pos != numbers.end(); pos++) {
		cout << *pos << " ";
	}
	cout << endl;
	system("PAUSE");
	return 0;
}