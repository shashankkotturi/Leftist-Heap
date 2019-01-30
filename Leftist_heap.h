
/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  vskottur @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Rall 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -s72rahma
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -s72rahma - debugging, testing
 *****************************************/

#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Leftist_node.h"

template <typename Type>
class Leftist_heap {
	private:
		Leftist_node<Type> *root_node;
		int heap_size;

	public:
		Leftist_heap();
		~Leftist_heap();

		void swap( Leftist_heap &heap );
		

		bool empty() const;
		int size() const;
		int null_path_length() const;
		Type top() const;
		int count( Type const & ) const;

		void push( Type const & );
		Type pop();
		void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Leftist_heap<T> const & );
};

// Sample functions given

template <typename Type>
Leftist_heap<Type>::Leftist_heap():
root_node( nullptr ),
heap_size( 0 ) {
	// does nothing
}


// Destructor
template <typename Type>
Leftist_heap<Type>::~Leftist_heap() {
	clear();  // might as well use it...
}

// Example of swap function
template <typename Type>
void Leftist_heap<Type>::swap( Leftist_heap<Type> &heap ) {
	std::swap( root_node, heap.root_node );
	std::swap( heap_size, heap.heap_size );
}


// Your implementation here
// STRONG HINT:  Write a default definition of each function, even if
// it only returns the default value (false, 0, or Type()).
//
// Once you have done this, you can proceed and implement the member functions
// one at a time.  If you do not, and just start implementing the member
// functions so that you can't compile and test your function, good luck. :-)


// Accessors

// Returns true if heap is empty, else false. (O(1))
template <typename Type>
bool Leftist_heap<Type>::empty() const {
	return (root_node == nullptr);
}

// Returns size of the heap
template <typename Type>
int Leftist_heap<Type>::size() const {
    return heap_size;
}

// Returns -1 if root_node is a nullptr
// Else, returns null_path_length of root_node
// Null path length is defined as the shortest path to a node that
// has an empty sub-tree. (O(1))
template <typename Type>
int Leftist_heap<Type>::null_path_length() const {
	if (root_node == nullptr) {
		return -1;
	}
    return root_node -> null_path_length();
}

// Returns number of instances of the argument in the heap. (O(n))
template <typename Type>
int Leftist_heap<Type>::count( const Type &obj ) const {
    if(root_node == nullptr)
		return 0;
    return root_node -> count(obj);
}

// Returns element at the top of the heap. If tree is empty, function
// throws an underflow exception. (O(1))
template <typename Type>
Type Leftist_heap<Type>::top() const {
    if (root_node == nullptr){
       throw underflow();
    }
    
    return root_node -> retrieve();
}

// Mutators

// Inserts new element into heap by creating a Leftist_node and calling
// push on the root node using root node as a second argument. After the
// object is pushed, heap size is incremented. (O(ln(n)))
template <typename Type>
void Leftist_heap<Type>::push( const Type &obj ){
     
	 // Create new node to insert element into heap
     Leftist_node<Type> *newNode = new Leftist_node<Type> (obj);
	 
	 // Checking if heap is empty. If empty, make new node the heap.
     if(root_node == nullptr)
         root_node = newNode;
	 // If not empty, push new node on root node using root node as 2nd argument.
     else
         root_node -> push(newNode, root_node);
     
	 // Increment heap size once push is completed.
     heap_size++;
	 
	 newNode = nullptr;
	 
     return;
}

// Pop's the least element in the heap and delete's its node. Throws 
// underflow exception if tree is empty. If not empty, left subtree of
// root_node is made the root and the right sub-tree is of the original
// root_node is pushed into the new root node. (O(ln(n)))
template <typename Type>
Type Leftist_heap<Type>::pop(){
     
	 // Throw underflow exception when heap is empty.
     if(root_node == nullptr)
         throw underflow();
	 
	 // Store original root node to delete later for deallocating memory.
	 Leftist_node<Type> * originalRoot = root_node;
	 
     // Store element that needs to be popped.
     Type poppedElement = root_node -> retrieve();    
     // Store right subtree of original root node.
	 Leftist_node<Type> *oldRootNodeRightChild = root_node -> right();
	 // Assign left subtree of original root node as the new root node.
     root_node = root_node -> left();
	 // Push right subtree of original root node to the new root node.
     root_node -> push(oldRootNodeRightChild, root_node);
     
     // Decrement heap size after popping element off the heap.
     heap_size--;
	 
	 oldRootNodeRightChild = nullptr;
	 
	 // Deleting popped element to deallocate memory.
	 delete originalRoot;
     // Return the popped element.
     return poppedElement;
     
}


// Calls clear on the root node and resets the root node and heap size. (O(n))
template <typename Type>
void Leftist_heap<Type>::clear(){
     root_node -> clear();
     root_node = nullptr;
     heap_size = 0;
}

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Leftist_heap<T> const &heap ) {
	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
