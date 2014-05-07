// Andrew Backes
// 6/11/2012
// HW8a - modified heap class.


#include <iostream>
#include <vector>

using namespace std;

class Heap
{
public:
	Heap();
	void push(int new_element);
	int top() const;
	void pop();
	int size() const;
private:
	void fix_heap();
	int get_left_child(int index);
	int get_right_child(int index);
	int get_parent(int index);
	vector<int> elements;
};

Heap::Heap()
{
   elements.push_back(0); 
}

void Heap::push(int new_element)
{
   // Add a new leaf
   elements.push_back(0);
   int index = elements.size() - 1;
      
   // Demote parents that are smaller than the new element
   while (index > 1 && get_parent(index) < new_element) 
   {
      elements[index] =  get_parent(index);
      index = (index/2);
   }

   // Store the new element into the vacant slot
   elements[index] = new_element;
}

int Heap::top() const
{
   return elements[1];
}

void Heap::pop()
{
   // Remove last element
   int last_index = elements.size() - 1;
   int last = elements[last_index];
   elements.pop_back();
   
   if (last_index > 1) {
      elements[1] = last;
      fix_heap();     
   }   
}

int Heap::size() const
{
   return elements.size() - 1;
}

void Heap::fix_heap()
{
   int root = elements[1];
   
   int last_index = elements.size() - 1;
   // Promote children of removed root while they are larger than last      
   
   int index = 1;
   bool more = true;
   while (more) {
      int child_index = (2 * index);
      if (child_index <= last_index) {
         // Get larger child 
         
         // Get left child first
         int child = get_left_child(index);
         
         // Use right child instead if it is larger
         if ((2* index + 1) <= last_index && get_right_child(index) > child) {
            child_index = (2 * index + 1);
            child = get_right_child(index);
         }
         
         // Check if smaller child is larger than root
         if (child > root) {
            // Promote child
            elements[index] = child;
            index = child_index;
         }
         else
         {
            // Root is larger than both children
            more = false;
         }
      }
      else 
      {
         // No children
         more = false; 
      }
   }
   
   // Store root element in vacant slot
   elements[index] = root;
}

int Heap::get_left_child(int index)
{
   return elements[2 * index];
}

int Heap::get_right_child(int index)
{
   return elements[2 * index + 1];
}

int Heap::get_parent(int index)
{
   return elements[index / 2];
}

int main()
{
   Heap tasks;
   tasks.push(2);
   tasks.push(3);
   tasks.push(2);
   tasks.push(1);
   tasks.push(4);
   tasks.push(9);
   tasks.push(1);
   tasks.push(5);

   while (tasks.size() > 0)
   {
      int task = tasks.top();
      tasks.pop();
      cout << task << "\n";
   }
   system("PAUSE");
   return 0;
}
