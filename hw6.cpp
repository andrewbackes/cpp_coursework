// Andrew Backes SID: 403-925-529
// May 20, 2012
//		Homework 6 - Linked List Practice
//		Note: This code was taken from the book and modified accordingly.

#include <string>
#include <iostream>
#include <cassert>

using namespace std;

class List;
class Iterator;

class Node
{
public:
   Node(string s);
private:
   string data;
   Node* previous;
   Node* next;
friend class List;
friend class Iterator;
};
class List
{
public:
   List();
   void push_back(string data);
   void insert(Iterator iter, string s);
   void reverse(); // Reverses the nodes in a list.
   void swap(List& other); // Swaps the elements of this list and other.
   Iterator erase(Iterator iter);
   Iterator begin();
   Iterator end();
private:
   Node* first;
   Node* last;
friend class Iterator;
};
class Iterator
{
public:
   Iterator();
   string get() const;
   void next();
   void previous();
   bool equals(Iterator b) const;
private:
   Node* position;
   List* container;
friend class List;
};

Node::Node(string s)
{  
   data = s;
   previous = NULL;
   next = NULL;
}

List::List()
{  
   first = NULL;
   last = NULL;
}
void List::push_back(string data)
{  
   Node* new_node = new Node(data);
   if (last == NULL) // List is empty
   {  
      first = new_node;
      last = new_node;
   }
   else
   {  
      new_node->previous = last;
      last->next = new_node;
      last = new_node;
   }
}
void List::insert(Iterator iter, string s)
{  
   if (iter.position == NULL)
   {  
      push_back(s);
      return;
   }

   Node* after = iter.position;
   Node* before = after->previous;
   Node* new_node = new Node(s);
   new_node->previous = before;
   new_node->next = after;
   after->previous = new_node;
   if (before == NULL) // Insert at beginning
      first = new_node;
   else
      before->next = new_node;
}
void List::swap(List& other) {
	// Swaps the elements in this list with another. 
	// Note: We only need to exchange control information.
	Node* temp_first = this->first;
	Node* temp_last = this->last;
	this->first = other.first;
	this->last = other.last;
	other.first = temp_first;
	other.last = temp_last;
}
void List::reverse() {
	// Reverse the nodes in the current list.
	Iterator pos;
	
	// First reverse the top and bottom of the list.
	Node* temp_first = this->first;
	this->first = this->last;
	this->last = temp_first;

	// Next flip next and previous on each node.
	for ( pos = this->begin(); !pos.equals(this->end()) ; pos.next() ) {
		Node* old_previous = pos.position->previous;
		pos.position->previous = pos.position->next;
		pos.position->next =  old_previous;
	}
}

Iterator List::erase(Iterator iter)
{  
   assert(iter.position != NULL);
   Node* remove = iter.position;
   Node* before = remove->previous;
   Node* after = remove->next;
   if (remove == first)
      first = after;
   else
      before->next = after;
   if (remove == last)
      last = before;
   else
      after->previous = before;
   delete remove;
   Iterator r;
   r.position = after;
   r.container = this;
   return r;
}
Iterator List::begin()
{  
   Iterator iter;
   iter.position = first;
   iter.container = this;
   return iter;
}
Iterator List::end()
{  
   Iterator iter;
   iter.position = NULL;
   iter.container = this;
   return iter;
}
Iterator::Iterator()
{  
   position = NULL;
   container = NULL;
}

string Iterator::get() const
{  
   assert(position != NULL);
   return position->data;
}
void Iterator::next()
{  
   assert(position != NULL);
   position = position->next;
}
void Iterator::previous()
{  
   assert(position != container->first);
   if (position == NULL)
      position = container->last;
   else 
      position = position->previous;
}
bool Iterator::equals(Iterator b) const
{  
   return position == b.position;
}

int main()
{  
   List staff;
   List senior_staff;

   Iterator pos; 
   staff.push_back("Tom");
   staff.push_back("Dick");
   staff.push_back("Harry");
   staff.push_back("Juliet");
   staff.push_back("Romeo");
   senior_staff.push_back("Obama");
   senior_staff.push_back("Bush");
   senior_staff.push_back("Clinton");
   senior_staff.push_back("Reagan");   

   cout << "*** DEMONSTRATING LIST REVERSE ***" << endl;
   // Print all values before reverse.
   cout << "Staff List before reversing: " << endl;
   for (pos = staff.begin(); !pos.equals(staff.end()); pos.next())
      cout << " " << pos.get() << "\n";

   // Reverse the List:
   staff.reverse();

   // Print all values after reverse.
   cout << "Staff List after reversing: " << endl;
   for (pos = staff.begin(); !pos.equals(staff.end()); pos.next())
      cout << " " << pos.get() << "\n";
   cout << endl;
   system("PAUSE");
   cout << endl << "*** DEMONSTRATING LIST SWAP ***" << endl;
   // Print Senior_staff List before swap
   cout << "Senior Staff List before swap: " << endl;
   for (pos = senior_staff.begin(); !pos.equals(senior_staff.end()); pos.next())
      cout << " " << pos.get() << "\n";

   // Swap lists.
   staff.swap(senior_staff);

   //Print lists out after the swap:
   cout << "Staff List after swap: " << endl;
   for (pos = staff.begin(); !pos.equals(staff.end()); pos.next())
      cout << " " << pos.get() << "\n";
   cout << "Senior Staff List after swap: " << endl;
   for (pos = senior_staff.begin(); !pos.equals(senior_staff.end()); pos.next())
      cout << " " << pos.get() << "\n";

   system("PAUSE");
   return 0;
}
