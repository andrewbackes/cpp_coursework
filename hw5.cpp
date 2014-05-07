// Andrew Backes SID: 403 925 529
// May 16, 2012
// Homework5 - Sorting Algorithms

// Sample Size: 100 random vectors of each size per algorithm.
//				Ran in Release Mode.
// Table: vector size / algorithm
// Data:  Benchmark in milliseconds
//
//		Selection	Bubble		Insertion	Merge	Quick
// 1K	0.9			0.6			0.1			0.9		0.2
// 5K	15.21		15			0.2			4		1
// 10K	60.6		59.9		0.3			14.3	2.3
// 20K	244.45		240.4		1.3			28.7	5.1
// 30K	553.82		540.64		2.8			34.01	8.6
// 40K	987.21		958.59		4.9			58.01	11.5
// 50K	1549.23		1497.46		7.6			63.81	14.8
// 60K	2238.14		2157.76		11.2		71.82	19.01

#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <sstream>

using namespace std;

//////////////////////////////////////////////////////////////////////////
// HELPER FUNCTIONS:
//////////////////////////////////////////////////////////////////////////
int random_num(int a, int b) {
	return (a + rand() % (b-a+1));
}
void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}
void print_vector(vector<int>& the_vector) {
	int vector_length = the_vector.size();
	for(int i =0; i < vector_length; i++) {
		cout << the_vector.at(i) << " ";
	}
}
int string_to_int(string s) {
	istringstream instr(s);
	int x;
	instr >> x;
	return x;
}
//////////////////////////////////////////////////////////////////////////
// SELECTION SORT:
//////////////////////////////////////////////////////////////////////////
int find_min(vector<int>& search_vector, int start_index, int end_index) {
	//returns the POSITION in the vector with the minimal value
	int min_position = start_index;
	for (int i = start_index+1; i <= end_index; i ++) {
		if( search_vector.at(i) < search_vector.at(min_position) )
			min_position = i;
	}
	return min_position;
}
void selection_sort(vector<int>& sort_vector) {
	int vector_length = sort_vector.size();
	for (int i = 0; i < vector_length - 1; i++) {
		int min_index = find_min(sort_vector, i, vector_length-1);
		if (min_index != i)
			swap(sort_vector.at(i), sort_vector.at(min_index));
	}
}
//////////////////////////////////////////////////////////////////////////
// BUBBLE SORT:
//////////////////////////////////////////////////////////////////////////
void bubble_sort(vector<int>& v) {
	int v_length = v.size();
	for (int i=1; i < v_length; i ++ ) {
		for( int j=0; j < v_length - i; j++) {
			if ( v[j] > v[j+1] )
				swap(v[j],v[j+1]);
		}
	}
}
//////////////////////////////////////////////////////////////////////////
// INSERTION SORT:
//////////////////////////////////////////////////////////////////////////
void insertion_sort(vector<int>& v) {
	int j = 0;
	int value = 0;
	int v_length = v.size();
	for (int i=1; i < v_length; i++ ) {
		value = v[i];
		j= i -1;
		while (j >=0 && v[j] > value) {
			v[j+1] = v[j];
			j=j-1;
		}
		v[j+1] = value;
	}
}
//////////////////////////////////////////////////////////////////////////
// MERGE SORT:
//////////////////////////////////////////////////////////////////////////
void merge(vector<int>& v, int start, int mid, int end) {
	int size = end - start + 1;
	vector<int> new_v(size);

	int counter1 = start;
	int counter2 = mid + 1;
	int pos = 0;

	while ( counter1 <= mid && counter2 <= end) {
		if (v[counter1] < v[counter2]) {
			new_v[pos] = v[counter1];
			counter1++; }
		else {
			new_v[pos] = v[counter2];
			counter2++; }
		pos++;
	}

	while ( counter1 <= mid) {
		new_v[pos] = v[counter1];
		counter1++;
		pos++; }
	while ( counter2 <= end) {
		new_v[pos] = v[counter2];
		counter2++;
		pos++; }

	for(int i=0; i < size; i++) 
		v[start+i] = new_v[i];
}
void merge_sort(vector<int>& sort_vector, int start, int end) {
	if(start == end)
		return;
	int mid = (end + start) / 2;

	merge_sort(sort_vector, start, mid);
	merge_sort(sort_vector, mid+1, end);

	merge(sort_vector, start, mid, end);
}
void merge_sort(vector<int>& sort_vector) {
	int end_index = sort_vector.size() - 1;
	merge_sort(sort_vector, 0, end_index);
}
//////////////////////////////////////////////////////////////////////////
// QUICK SORT:
//////////////////////////////////////////////////////////////////////////
int partition(vector<int>& v, int start, int end) {
	int pivot = v[start];
	int i = start -1;
	int j = end +1;
	while ( i < j ) {
		i++; while (v[i] < pivot) i++;
		j--; while (v[j] > pivot) j--;
		if ( i < j ) swap(v[i],v[j]);
	}
	return j;
}
void quick_sort(vector<int>& v, int start, int end) {
	if (start >= end)
		return;
	int par = partition(v,start,end);
	quick_sort(v, start, par);
	quick_sort(v, par + 1, end);
}
void quick_sort(vector<int>& v) {
	int end_index = v.size() - 1;
	quick_sort(v, 0, end_index);
}
//////////////////////////////////////////////////////////////////////////
// INTERFACE:
//////////////////////////////////////////////////////////////////////////
void menu_loop() {
	string user_input;
	while(true) {
		cout << "Which algorithm would you like to benchmark: " << endl;
		cout << "1. Selection Sort" << endl;
		cout << "2. Bubble Sort" << endl;
		cout << "3. Insertion Sort" << endl;
		cout << "4. Merge Sort" << endl;
		cout << "5. Quick Sort" << endl;
		cout << "0. Quit" << endl << endl;
		cout << "Please input 0-5: ";
		getline(cin, user_input);
		if(user_input == "0") 
			//User wishes to quit.
			break;
		else if (user_input == "1" || user_input == "2" || user_input == "3" || user_input == "4" || user_input == "5" ){
			//User wants to do some benchmarking.
			cout << endl << "How many times would you like to test each vector? ";
			string user_input2;
			getline(cin, user_input2);
			int max_iterations = string_to_int(user_input2);
			int iteration_count = 0;

			int v_sizes[] = {1000,5000,10000,20000,30000,40000,50000,60000};
			for (int j = 0; j < 8; j ++) { 
				vector<int> test_vector(v_sizes[j]);
				//Fill the vector:
				for (int i = 0; i < test_vector.size(); i++) {
					test_vector[i] = random_num(1,37000);	
				}
				//Now test the vector:
				time_t start_time = time(NULL);
				for (iteration_count = 1; iteration_count <= max_iterations; iteration_count++) {
					if( user_input == "1")
						selection_sort(test_vector);
					else if ( user_input == "2")
						bubble_sort(test_vector);
					else if ( user_input == "3")
						insertion_sort(test_vector);
					else if ( user_input == "4")
						merge_sort(test_vector);
					else if ( user_input == "5")
						quick_sort(test_vector);
					if( time(NULL) - start_time > 300 ) //Time-out at 5min.
						break;
				}
				time_t end_time = time(NULL);
				double total_time = (double) end_time - start_time;
				double average_time = (double) (total_time) / (iteration_count - 1);

				cout << v_sizes[j] << " element vector took " << average_time << " secs to sort. Averaged over " << iteration_count-1 << " iterations." << endl;
			}
		}
		cout << endl;
	} 
}
int main() {
	cout << "Sorting Algorithms" << endl << endl;
	srand ( time(NULL) );
	menu_loop();
	return 0;
}