
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
 * Calender Term of Submission:  Fall 2017
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

#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

#include <algorithm>
// You may use std::swap and std::min

#ifndef nullptr
#define nullptr 0
#endif

template <typename Type>
class Leftist_node {
	private:
		Type element;
		Leftist_node *left_tree;
		Leftist_node *right_tree;
		int heap_null_path_length;

	public:
		Leftist_node( Type const & );

		Type retrieve() const;
		bool empty() const;
		Leftist_node *left() const;
		Leftist_node *right() const;
		int count( Type const & ) const;
		int null_path_length() const;

		void push( Leftist_node *, Leftist_node *& );
		void clear();
};

template <typename Type>
Leftist_node<Type>::Leftist_node( Type const &obj ):
element( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
heap_null_path_length( 0 ) {
	// does nothing
}

// You may need this

template <typename Type>
bool Leftist_node<Type>::empty() const {
	return ( this == nullptr );
}

// You must implement everything

// Accessors

// Returns element stored at the specific node. (O(1))
template <typename Type>
Type Leftist_node<Type>::retrieve() const {
    return element;
}

// Return left subtree of the specific node. (O(1))
template <typename Type>
Leftist_node<Type>* Leftist_node<Type>::left() const {
    return left_tree;
}

// Returns right subtree of the specific node. (O(1))
template <typename Type>
Leftist_node<Type>* Leftist_node<Type>::right() const {
    return right_tree;
}

// Returns -1 if heap is empty, else returns the null path length of the heap.(O(1))
template <typename Type>
int Leftist_node<Type>::null_path_length() const {
    if (this == nullptr)
       return -1;
       
    return heap_null_path_length;
}

// Returns 0 if heap is empty. Recursively calls count of left and right subtree
// and everytime an instance of the object is encountered, the partial sum is
// incremented until the entire tree is traversed. (O(n))
template <typename Type>
int Leftist_node<Type>::count(const Type &obj) const {
    
    if(this == nullptr)
        return 0;
    
    if (element == obj)
       return 1 + left_tree -> count(obj) + right_tree -> count(obj);
    
    return left_tree -> count(obj) + right_tree -> count(obj);
}

// Mutators

//Pushes new heap onto current heap while maintaining leftist heap properties. (O(ln(n)))
template <typename Type>
void Leftist_node<Type>::push(Leftist_node *new_heap, Leftist_node *&ptr_to_this) {
    // If heap to be inserted is empty, return out of the function
	if(new_heap == nullptr)
        return;
    
	// If this heap is empty, make the new heap this heap.
    if(ptr_to_this == nullptr){
        ptr_to_this = new_heap;
        return;
    }
    
	// When root node of this heap is less than or equal to root node of heap to be inserted.
    if(ptr_to_this -> element <= new_heap -> element){
         
        // Recursively call push with the new heap and the right subtree of this heap.           
        push(new_heap, ptr_to_this -> right_tree);
        
        // Updating heap_null_path_length process
		
		// Assuming left tree is null as default
        int left_null_path_length = -1 ;
        
		// If left tree is not a null tree, update left_null_path_length with
		// the actual null path_length of the left subtree
		if(ptr_to_this -> left_tree != nullptr)
		    left_null_path_length = ptr_to_this -> left_tree -> heap_null_path_length;
		
		// If left subtree is not empty, find heap_null_path_length by adding 1 for the current node
		// and the minimum of the null_path_length for the left subtree and the right subtree
        if (left_null_path_length > -1)
			ptr_to_this -> heap_null_path_length = 1 + std::min(left_null_path_length, ptr_to_this -> right_tree -> heap_null_path_length);
		    
        // Need to swap right subtree with left subtree to ensure it's a leftist heap
        if(left_null_path_length < ptr_to_this -> right_tree -> heap_null_path_length)
            std::swap(ptr_to_this -> left_tree, ptr_to_this -> right_tree);
    
        return;
    }
    
	// Case 3 - when the first two cases are not applicable
	// Sets the pointer to this heap as the pointer to the new heap and pushes this node
	// into the new heap using the original pointer to this heap.
    else{
        Leftist_node *temp = ptr_to_this;
        ptr_to_this = new_heap;
        push(temp, ptr_to_this);     
		return;
    }
    
    return;
    
}

// Calls clear recursively on the left and right subtree of the specific node.
// If the node is a nullptr, then stop recursive calls from that node onwards.
// Delete this specific node. (O(n))
template <typename Type>
void Leftist_node<Type>::clear(){
     if (this == nullptr)
        return;
     
     left_tree -> clear();
     right_tree -> clear();
          
     delete this;
     
     return;
}

#endif
