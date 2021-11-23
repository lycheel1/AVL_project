/*****************************************
 * UW User ID:  q282liu
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By  submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef RPOVDGBQN9TIEO3P
#define RPOVDGBQN9TIEO3P

#include "Exception.h"
#include "ece250.h"
#include <cassert>
#include <cmath>

template <typename Type>
class Search_tree {
	public:
		class Iterator;

	private:
		class Node {
			public:
				Type node_value;
				int tree_height;

				// The left and right sub-trees
				Node *left_tree;
				Node *right_tree;
				Node *parent_node;

				// Hint as to how you can create your iterator
				// Point to the previous and next nodes in linear order
				Node *previous_node;
				Node *next_node;

				// Member functions
				Node( Type const & = Type() );

				void update_height();
				
				int height() const;
				bool is_leaf() const;
				Node *front();
				Node *back();
				Node *find( Type const &obj );

				void clear();
				bool insert( Type const &obj, Node *&to_this );
				bool erase( Type const &obj, Node *&to_this );
				bool recursive_balance();
				bool recursive_update_height();		
				};

		Node *root_node;
		Node *mut_node;
		Node *mut_node_parent;  

		int tree_size;

		// Hint as to how to start your linked list of the nodes in order 
		Node *front_sentinel;
		Node *back_sentinel;

	public:
		class Iterator {
			private:
				Search_tree *containing_tree;
				Node *current_node;
				bool is_end;

				// The constructor is private so that only the search tree can create an iterator
				Iterator( Search_tree *tree, Node *starting_node );

			public:
				// DO NOT CHANGE THE SIGNATURES FOR ANY OF THESE
				Type operator*() const;
				Iterator &operator++();
				Iterator &operator--();
				bool operator==( Iterator const &rhs ) const;
				bool operator!=( Iterator const &rhs ) const;
				

			// Make the search tree a friend so that it can call the constructor
			friend class Search_tree;
		};

		// DO NOT CHANGE THE SIGNATURES FOR ANY OF THESE
		Search_tree();
		~Search_tree();

		bool empty() const;
		int size() const;
		int height() const;

		Type front() const;
		Type back() const;

		Iterator begin();
		Iterator end();
		Iterator rbegin();
		Iterator rend();
		Iterator find( Type const & );

		void clear();
		bool insert( Type const & );
		bool erase( Type const & );
		bool check_balance();
		void mutating_node();
		void mutate_tree();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Search_tree<T> const & );
};

//////////////////////////////////////////////////////////////////////
//                Search Tree Public Member Functions               //
//////////////////////////////////////////////////////////////////////

// The initialization of the front and back sentinels is a hint
template <typename Type>
Search_tree<Type>::Search_tree():
root_node( nullptr ),
tree_size( 0 ),
front_sentinel( new Search_tree::Node( Type() ) ),
back_sentinel( new Search_tree::Node( Type() ) ) {
	front_sentinel->next_node = back_sentinel;
	back_sentinel->previous_node = front_sentinel;
}

template <typename Type>
Search_tree<Type>::~Search_tree() {
	clear();  // might as well use it...
	delete front_sentinel;
	delete back_sentinel;
	//delete mut_node;
}

template <typename Type>
bool Search_tree<Type>::empty() const {
	return ( root_node == nullptr );
}

template <typename Type>
int Search_tree<Type>::size() const {
	return tree_size;
}

template <typename Type>
int Search_tree<Type>::height() const {
	return root_node->height();
}

template <typename Type>
Type Search_tree<Type>::front() const {
	if ( empty() ) {
		throw underflow();
	}

	return root_node->front()->node_value;
}

template <typename Type>
Type Search_tree<Type>::back() const {
	if ( empty() ) {
		throw underflow();
	}

	return root_node->back()->node_value;
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::begin() {
	return empty() ? Iterator( this, back_sentinel ) : Iterator( this, root_node->front() );
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::end() {
	return Iterator( this, back_sentinel );
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::rbegin() {
	return empty() ? Iterator( this, front_sentinel ) : Iterator( this, root_node->back() );
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::rend() {
	return Iterator( this, front_sentinel );
}

template <typename Type>
typename Search_tree<Type>::Iterator Search_tree<Type>::find( Type const &obj ) {
	if ( empty() ) {
		return Iterator( this, back_sentinel );
	}

	typename Search_tree<Type>::Node *search_result = root_node->find( obj );

	if ( search_result == nullptr ) {
		return Iterator( this, back_sentinel );
	} else {
		return Iterator( this, search_result );
	}
}

template <typename Type>
void Search_tree<Type>::clear() {
	if ( !empty() ) {
		root_node->clear();
		root_node = nullptr;
		tree_size = 0;
	}

	// Reinitialize the sentinels
	front_sentinel->next_node = back_sentinel;
	back_sentinel->previous_node = front_sentinel;
}

// This is the function for checking whether the entire tree is balanced
// Basically do the same as recursive_balance() except for checking the root_node edge case
template <typename Type>
bool Search_tree<Type>::check_balance(){

	if(empty()){
		return true;
	}
	else if(std::abs((root_node->left_tree->height())-(root_node->right_tree->height())) > 1){
		return false;
	}else{
		bool x = true;
		Node *itr = root_node;
		return root_node->recursive_balance();
	}
}

// This function is for finding the lowest unbalanced node
template <typename Type>
void Search_tree<Type>::mutating_node(){
	if(!check_balance()){
		Node *tree_tracker = root_node;
		Node *tracker_holder = root_node;
		//Check nullptr case
		if(tree_tracker->left_tree == nullptr && !(tree_tracker->recursive_balance())){
			mut_node = root_node;
		}else if(tree_tracker->right_tree == nullptr && !(tree_tracker->recursive_balance())){
			mut_node = root_node;
		}
		//Check for general case:
		// if left tree unbalanced, go to left, and vice versa
		// break when the lower trees are no longer unbalanced
		else{
			while(tree_tracker != nullptr){
				if((tree_tracker->left_tree != nullptr) && (!(tree_tracker->left_tree->recursive_balance()))){
					tree_tracker = tree_tracker->left_tree;
				}else if((tree_tracker->right_tree != nullptr) && (!(tree_tracker->right_tree->recursive_balance()))){
					tree_tracker = tree_tracker->right_tree;
				}else{
					break;
				}
			}
			mut_node = tree_tracker;
			if(mut_node->parent_node != nullptr){
				mut_node_parent = mut_node->parent_node;
			}
		}
	}
}

// This function rotates the tree
// four cases for unbalanced_node != root_node, and four for when they are equal
// the erase cases is when after erase, the next node height may be equaled.
template <typename Type>
void Search_tree<Type>::mutate_tree(){
	if (mut_node != root_node)
	{
		//case 1 (left-left)
		if ((mut_node->left_tree->height() > mut_node->right_tree->height()) && ((mut_node->left_tree->left_tree->height()) > (mut_node->left_tree->right_tree->height())))
		{
			//tree structure
			Node *b = mut_node->left_tree;
			Node *BR = b->right_tree;
			b->right_tree = mut_node;
			if (mut_node_parent->left_tree == mut_node)
			{
				mut_node_parent->left_tree = b;
			}
			else if (mut_node_parent->right_tree == mut_node)
			{
				mut_node_parent->right_tree = b;
			}

			mut_node->left_tree = BR;

			if(BR!=nullptr){
				BR->parent_node = mut_node;
			}
			mut_node->parent_node = b;
			b->parent_node = mut_node_parent;
		}
		//case 2 (left-right)
		else if (((mut_node->left_tree->height()) > (mut_node->right_tree->height())) && (mut_node->left_tree->left_tree->height() < mut_node->left_tree->right_tree->height()))
		{
			Node *b = mut_node->left_tree;
			Node *d = b->right_tree;
			Node *DL = d->left_tree;
			Node *DR = d->right_tree;
			d->left_tree = b;
			d->right_tree = mut_node;
			if (mut_node_parent->left_tree == mut_node)
			{
				mut_node_parent->left_tree = d;
			}
			else if (mut_node_parent->right_tree == mut_node)
			{
				mut_node_parent->right_tree = d;
			}
			b->right_tree = DL;
			mut_node->left_tree = DR;

			if(DL!=nullptr){
				DL->parent_node = b;
			}
			if(DR!=nullptr){
				DR->parent_node = mut_node;
			}
			b->parent_node = d;
			mut_node->parent_node = d;
			d->parent_node = mut_node_parent;
		}
		//case 3 (right-right)
		else if (((mut_node->left_tree->height()) < (mut_node->right_tree->height())) && ((mut_node->right_tree->left_tree->height()) < (mut_node->right_tree->right_tree->height())))
		{
			Node *b = mut_node->right_tree;
			Node *BR = b->left_tree;
			b->left_tree = mut_node;
			if (mut_node_parent->left_tree == mut_node)
			{
				mut_node_parent->left_tree = b;
			}
			else if (mut_node_parent->right_tree == mut_node)
			{
				mut_node_parent->right_tree = b;
			}

			mut_node->right_tree = BR;
			mut_node->tree_height -=2;
			if(BR!=nullptr){
				BR->parent_node = mut_node;
			}

			mut_node->parent_node = b;
			b->parent_node = mut_node_parent;
		}
		//case 4 (right-left)
		else if ((mut_node->left_tree->height() < mut_node->right_tree->height()) && (mut_node->right_tree->left_tree->height() > mut_node->right_tree->right_tree->height()))
		{
			Node *b = mut_node->right_tree;
			Node *d = b->left_tree;
			Node *DL = d->right_tree;
			Node *DR = d->left_tree;
			d->right_tree = b;
			d->left_tree = mut_node;
			if (mut_node_parent->left_tree == mut_node)
			{
				mut_node_parent->left_tree = d;
			}
			else if (mut_node_parent->right_tree == mut_node)
			{
				mut_node_parent->right_tree = d;
			}
			b->left_tree = DL;
			mut_node->right_tree = DR;
			if(DL!=nullptr){
				DL->parent_node = b;
			}
			if(DR!=nullptr){
				DR->parent_node = mut_node;
			}
			
			b->parent_node = d;
			mut_node->parent_node = d;
			d->parent_node = mut_node_parent;
		}
		//erase case 1
		else if(((mut_node->left_tree->height()) > (mut_node->right_tree->height())) && (mut_node->left_tree->left_tree->height() == mut_node->left_tree->right_tree->height())){
			//tree structure
			Node *b = mut_node->left_tree;
			Node *BR = b->right_tree;
			b->right_tree = mut_node;
			if (mut_node_parent->left_tree == mut_node)
			{
				mut_node_parent->left_tree = b;
			}
			else if (mut_node_parent->right_tree == mut_node)
			{
				mut_node_parent->right_tree = b;
			}

			mut_node->left_tree = BR;

			if(BR!=nullptr){
				BR->parent_node = mut_node;
			}
			mut_node->parent_node = b;
			b->parent_node = mut_node_parent;
		}
		//erase case 3
		else if((mut_node->left_tree->height() < mut_node->right_tree->height()) && (mut_node->right_tree->left_tree->height() == mut_node->right_tree->right_tree->height())){
			Node *b = mut_node->right_tree;
			Node *BR = b->left_tree;
			b->left_tree = mut_node;
			if (mut_node_parent->left_tree == mut_node)
			{
				mut_node_parent->left_tree = b;
			}
			else if (mut_node_parent->right_tree == mut_node)
			{
				mut_node_parent->right_tree = b;
			}

			mut_node->right_tree = BR;
			mut_node->tree_height -=2;
			if(BR!=nullptr){
				BR->parent_node = mut_node;
			}

			mut_node->parent_node = b;
			b->parent_node = mut_node_parent;		
		}
	}
	else if(mut_node == root_node)
	{
		//case 1 (left-left)
		if ((mut_node->left_tree->height() > mut_node->right_tree->height()) && (mut_node->left_tree->left_tree->height() > mut_node->left_tree->right_tree->height()))
		{
			//tree structure
			Node *b = mut_node->left_tree;
			Node *BR = b->right_tree;
			b->right_tree = mut_node;
			root_node = b;

			mut_node->left_tree = BR;
			if(BR!=nullptr){
				BR->parent_node = mut_node;
			}
			
			mut_node->parent_node = b;
		}
		//case 2 (left-right)
		else if (((mut_node->left_tree->height()) > (mut_node->right_tree->height())) && (mut_node->left_tree->left_tree->height() < mut_node->left_tree->right_tree->height()))
		{
			Node *b = mut_node->left_tree;
			Node *d = b->right_tree;
			Node *DL = d->left_tree;
			Node *DR = d->right_tree;
			d->left_tree = b;
			d->right_tree = mut_node;
			root_node = d;
			b->right_tree = DL;
			mut_node->left_tree = DR;
			if(DL!=nullptr){
				DL->parent_node = b;
			}
			if(DR!=nullptr){
				DR->parent_node = mut_node;
			}
			
			b->parent_node = d;
			mut_node->parent_node = d;
		}
		//case 3 (right-right)
		else if (((mut_node->left_tree->height()) < (mut_node->right_tree->height())) && (mut_node->right_tree->left_tree->height() < mut_node->right_tree->right_tree->height()))
		{
			Node *b = mut_node->right_tree;
			Node *BR = b->left_tree;
			b->left_tree = mut_node;
			root_node = b;

			mut_node->right_tree = BR;
			if(BR != nullptr){
				BR->parent_node = mut_node;
			}
			mut_node->parent_node = b;
		}
		//case 4 (right-left)
		else if ((mut_node->left_tree->height() < mut_node->right_tree->height()) && (mut_node->right_tree->left_tree->height() > mut_node->right_tree->right_tree->height()))
		{
			Node *b = mut_node->right_tree;
			Node *d = b->left_tree;
			Node *DL = d->right_tree;
			Node *DR = d->left_tree;
			d->right_tree = b;
			d->left_tree = mut_node;
			root_node = d;
			b->left_tree = DL;
			mut_node->right_tree = DR;
			if(DL!=nullptr){
				DL->parent_node = b;
			}
			if(DR!=nullptr){
				DR->parent_node = mut_node;
			}
			
			b->parent_node = d;
			mut_node->parent_node = d;
		}
		// erase case 1
		else if(((mut_node->left_tree->height()) > (mut_node->right_tree->height())) && (mut_node->left_tree->left_tree->height() == mut_node->left_tree->right_tree->height())){
			Node *b = mut_node->left_tree;
			Node *BR = b->right_tree;
			b->right_tree = mut_node;
			root_node = b;

			mut_node->left_tree = BR;
			if(BR!=nullptr){
				BR->parent_node = mut_node;
			}
			
			mut_node->parent_node = b;
		}
		//erase case 3
		else if((mut_node->left_tree->height() < mut_node->right_tree->height()) && (mut_node->right_tree->left_tree->height() == mut_node->right_tree->right_tree->height())){
			Node *b = mut_node->right_tree;
			Node *BR = b->left_tree;
			b->left_tree = mut_node;
			root_node = b;

			mut_node->right_tree = BR;
			if(BR != nullptr){
				BR->parent_node = mut_node;
			}
			mut_node->parent_node = b;			
		}	
	}
}

template <typename Type>
bool Search_tree<Type>::insert( Type const &obj ) {
	if ( empty() ) {
		root_node = new Search_tree::Node( obj );
		tree_size = 1;
		// Connect root and front/back together
		front_sentinel->next_node = root_node;
		back_sentinel->previous_node = root_node;
		root_node->next_node = back_sentinel;
		root_node->previous_node = front_sentinel;

		return true;
	} else if ( root_node->insert( obj, root_node ) ) {
		++tree_size;
		// Simply calling the finding the lowest unbalanced node -> rotate -> update height rotation
		if(!check_balance()){
			mutating_node();
			mutate_tree();
			root_node->recursive_update_height();
		}
		return true;
	} else {
		return false;
	}
}

template <typename Type>
bool Search_tree<Type>::erase( Type const &obj ) {
	if ( !empty() && root_node->erase( obj, root_node ) ) {
		--tree_size;
		//simply calling the three functions: finding lowest unbalanced node->rotate->update_height after a node is erased
		while(!check_balance()){
			if(!empty()){
				mutating_node();
				mutate_tree();
				root_node->recursive_update_height();

			}
		}
		return true;
	} else if(empty()){
		// if empty, front and back should be connect back together
		front_sentinel->next_node = back_sentinel;
		back_sentinel->previous_node = front_sentinel;
		return false;
	}else{
		return false;
	}
}

//////////////////////////////////////////////////////////////////////
//                   Node Public Member Functions                   //
//////////////////////////////////////////////////////////////////////

template <typename Type>
Search_tree<Type>::Node::Node( Type const &obj ):
node_value( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
parent_node(nullptr),
next_node( nullptr ),
previous_node( nullptr ),
tree_height( 0 ) {
	// does nothing
}

template <typename Type>
void Search_tree<Type>::Node::update_height() {
	tree_height = std::max( left_tree->height(), right_tree->height() ) + 1;
}

template <typename Type>
int Search_tree<Type>::Node::height() const {
	return ( this == nullptr ) ? -1 : tree_height;
}

// Return true if the current node is a leaf node, false otherwise
template <typename Type>
bool Search_tree<Type>::Node::is_leaf() const {
	return ( (left_tree == nullptr) && (right_tree == nullptr) );
}

// Return a pointer to the front node
template <typename Type>
typename Search_tree<Type>::Node *Search_tree<Type>::Node::front() {
	return ( left_tree == nullptr ) ? this : left_tree->front();
}

// Return a pointer to the back node
template <typename Type>
typename Search_tree<Type>::Node *Search_tree<Type>::Node::back() {
	return ( right_tree == nullptr ) ? this : right_tree->back();
}

template <typename Type>
typename Search_tree<Type>::Node *Search_tree<Type>::Node::find( Type const &obj ) {
	if ( obj == node_value ) {
		return this;
	} else if ( obj < node_value ) {
		return (left_tree == nullptr) ? nullptr : left_tree->find( obj );
	} else {
		return ( right_tree == nullptr ) ? nullptr : right_tree->find( obj );
	}
}

// Recursively clear the tree
template <typename Type>
void Search_tree<Type>::Node::clear() {
	if ( left_tree != nullptr ) {
		left_tree->clear();
	}

	if ( right_tree != nullptr ) {
		right_tree->clear();
	}

	delete this;
}

template <typename Type>
bool Search_tree<Type>::Node::insert( Type const &obj, Search_tree<Type>::Node *&to_this ) {
	if ( obj < node_value ) {
		if ( left_tree == nullptr ) {
			left_tree = new Search_tree<Type>::Node( obj );
			update_height();
			//connecting the nodes for iterator
			left_tree->next_node = to_this;
			left_tree->previous_node = to_this->previous_node;
			to_this->previous_node->next_node = left_tree;
			to_this->previous_node = left_tree;
			left_tree->parent_node = to_this;

			return true;
		} else {
			if ( left_tree->insert( obj, left_tree ) ) {
				update_height();
				return true;
			} else {
				return false;
			}
		}
	} else if ( obj > node_value ) {
		if ( right_tree == nullptr ) {
			right_tree = new Search_tree<Type>::Node( obj );
			update_height();
			right_tree->next_node = to_this->next_node;
			right_tree->previous_node = to_this;
			to_this->next_node->previous_node = right_tree;
			to_this->next_node = right_tree;
			right_tree->parent_node = to_this;

			return true;
		} else {
			if ( right_tree->insert( obj, right_tree ) ) {
				update_height();
				return true;
			} else {
				return false;
			}
		}
	} else {
		return false;
	}
}

template <typename Type>
bool Search_tree<Type>::Node::erase( Type const &obj, Search_tree<Type>::Node *&to_this ) {
	if ( obj < node_value ) {
		if ( left_tree == nullptr ) {
			return false;
		} else {
			if ( left_tree->erase( obj, left_tree ) ) {
				update_height();

				return true;
			}

			return false;
		}
	} else if ( obj > node_value ) {
		if ( right_tree == nullptr ) {
			return false;
		} else {
			if ( right_tree->erase( obj, right_tree ) ) {
				update_height();

				return true;
			}

			return false;
		}
	} else {
		assert( obj == node_value );

		if ( is_leaf() ) {
			to_this->previous_node->next_node = to_this->next_node;
			to_this->next_node->previous_node = to_this->previous_node;
			to_this = nullptr;
			delete this;
		} else if ( left_tree == nullptr ) {
			to_this->previous_node->next_node=right_tree;
			right_tree->previous_node = to_this->previous_node;
			if(right_tree!=nullptr){
				right_tree->parent_node = to_this->parent_node;
			}
			
			to_this = right_tree;
			delete this;
		} else if ( right_tree == nullptr ) {
			to_this->next_node->previous_node = left_tree;
			left_tree->next_node = to_this->next_node;
			if(left_tree!=nullptr){
				left_tree->parent_node = to_this->parent_node;
			}
			
			to_this = left_tree;
			delete this;
		} else {
			node_value = right_tree->front()->node_value;
			right_tree->erase( node_value, right_tree );
			update_height();
		}

		return true;
	}
}

template<typename Type>
bool Search_tree<Type>::Node::recursive_balance(){
	// This function checks recursively whether the tree is AVL or not
	// This block checks whether a node is balanced or not
  if(is_leaf()){
    return true;
  }
  else if(left_tree == nullptr){
    if(!(right_tree->is_leaf())){
      return false;
    }else{
      return true;
    }
  }else if(right_tree == nullptr){
    if(!(left_tree->is_leaf())){
      return false;
    }else{
      return true;
    }
  }
  else if(std::abs(left_tree->height() - right_tree->height()) > 1){
	  return false;
  }
  // This is the block for recursion: if this node is balanced -> go down a level
  else if(left_tree->recursive_balance() && (right_tree->recursive_balance())){
    return true;
  }else{
    return false;
  }
}

template<typename Type>
bool Search_tree<Type>::Node::recursive_update_height(){
	// This is a recursive function to update the height of the tree after rotation
	//This is block checks when this node is close to the bottom of the tree
  if(this->is_leaf()){
    tree_height = 0;
    return true;
  }else if(left_tree==nullptr){
	 tree_height = 1;
	 right_tree->update_height();
	  return true;
  }else if(right_tree==nullptr){
	  tree_height = 1;
	  left_tree->update_height();
	  return true;
  }
  //This is the block that keep recursively passing down until this node is close to the bottom
  else if(left_tree->recursive_update_height() && (right_tree->recursive_update_height())){
    update_height();
    return true;
  }
}
//////////////////////////////////////////////////////////////////////
//                   Iterator Private Constructor                   //
//////////////////////////////////////////////////////////////////////

template <typename Type>
Search_tree<Type>::Iterator::Iterator( Search_tree<Type> *tree, typename Search_tree<Type>::Node *starting_node ):
containing_tree( tree ),
current_node( starting_node ) {
	// This is done for you...
	// Does nothing...
}

//////////////////////////////////////////////////////////////////////
//                 Iterator Public Member Functions                 //
//////////////////////////////////////////////////////////////////////

template <typename Type>
Type Search_tree<Type>::Iterator::operator*() const {
	// This is done for you...
	return current_node->node_value;
}

template <typename Type>
typename Search_tree<Type>::Iterator &Search_tree<Type>::Iterator::operator++() {
	// Update the current node to the node containing the next higher value
	// If we are already at end do nothing

	// Your implementation here, do not change the return value
	if(current_node != containing_tree->back_sentinel){
		current_node = current_node->next_node;
	}else{
		return *this;
	}

	return *this;
}

template <typename Type>
typename Search_tree<Type>::Iterator &Search_tree<Type>::Iterator::operator--() {
	// Update the current node to the node containing the next smaller value
	// If we are already at either rend, do nothing

	// Your implementation here, do not change the return value
	if(current_node != containing_tree->front_sentinel){
		current_node = current_node->previous_node;
	}else{
		return *this;
	}
	return *this;
}

template <typename Type>
bool Search_tree<Type>::Iterator::operator==( typename Search_tree<Type>::Iterator const &rhs ) const {
	// This is done for you...
	return ( current_node == rhs.current_node );
}

template <typename Type>
bool Search_tree<Type>::Iterator::operator!=( typename Search_tree<Type>::Iterator const &rhs ) const {
	// This is done for you...
	return ( current_node != rhs.current_node );
}

//////////////////////////////////////////////////////////////////////
//                            Friends                               //
//////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Search_tree<T> const &list ) {
	out << "not yet implemented";

	return out;
}

#endif
