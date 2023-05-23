/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/

#include <vector>
#include <iostream>
#include <fstream>
#include <utility>
#include <algorithm>
#ifndef DS_BPLUSTREE
#define DS_BPLUSTREE

///////////////////////////////////////////////////////////////////////////////
//DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////

//Do not implement the class here, this is a forward declaration. Implement at
//the bottom of the .h file
template <class T> class BPlusTree; 

template <class T>
class BPlusTreeNode{
public:
	BPlusTreeNode() : parent(NULL) {};
	bool is_leaf();
	bool contains(const T& key);

	//For grading only. This is bad practice to have, because
	//it exposes a private member variable.
	BPlusTreeNode* get_parent() { return parent; } 

	//We need this to let BPlusTree access private members
	friend class BPlusTree<T>; 
private:
	bool contains(const T& key,std::size_t low,std::size_t high);
	std::vector<T> keys;
	std::vector<BPlusTreeNode*> children;
	BPlusTreeNode* parent;
};

template <class T>
bool BPlusTreeNode<T>::is_leaf(){
	for(unsigned int i=0; i<children.size(); i++){
		if(children[i]){
			return false;
		}
	}
	return true;
}

template <class T>
bool BPlusTreeNode<T>::contains(const T& key){
	return contains(key,0,keys.size()-1);
}

//Private method takes advantage of the fact keys are sorted
template <class T>
bool BPlusTreeNode<T>::contains(const T& key,std::size_t low,std::size_t high){
	if(low>high){
		return false;
	}
	if(low==high){
		return key == keys[low];
	}
	std::size_t mid = (low+high)/2;
	if(key<=keys[mid]){
		return contains(key,0,mid);
	}
	else{
		return contains(key,mid+1,high);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//Your BPlusTree implementation goes below this point.
///////////////////////////////////////////////////////////////////////////////////////

template <class T> class BPlusTree {
	public:
		// CONSTRUCTORS
		BPlusTree() {
			start_size = 0;
			root_node = NULL;
		}
		BPlusTree(unsigned int size) {
			start_size = size;
			root_node = NULL;
		}
		~BPlusTree();
		// A function to insert a key into the tree
		void insert(const T& key);
		// A function to find a node that contains a key
		BPlusTreeNode<T>* find(const T& key);
		void print_BFS(std::ofstream &outfile) {
			outfile << "Tree is empty." << std::endl;
		}
		void print_sideways(std::ofstream &outfile) {
			outfile << "Tree is empty." << std::endl;
		}


	private: // REPRESENTATION
		unsigned int start_size;
		BPlusTreeNode<T>* root_node;
		
		BPlusTreeNode<T>* find_leaf(const T& key);
		void insert_key(BPlusTreeNode<T>* node, const T& key);
		bool is_overflow(BPlusTreeNode<T>* node);
		void split_and_insert(BPlusTreeNode<T>* node);
		BPlusTreeNode<T>* split(BPlusTreeNode<T>* node);
		T get_middle_key(BPlusTreeNode<T>* node);
		void remove_middle_key(BPlusTreeNode<T>* node);
		BPlusTreeNode<T>* get_or_create_parent(BPlusTreeNode<T>* node);
		void insert_child(BPlusTreeNode<T>* node, BPlusTreeNode<T>* child);
		void update_parent(BPlusTreeNode<T>* node, BPlusTreeNode<T>* parent);
		void update_parents(std::vector<BPlusTreeNode<T>*> nodes, BPlusTreeNode<T>* parent);
		void remove_keys(BPlusTreeNode<T>* node, unsigned int start);
		void remove_children(BPlusTreeNode<T>* node, unsigned int start);

};

// A function that helps with inserting a key into the tree
template <class T>
void BPlusTree<T>::insert(const T& key) {
	// If the tree is empty, create a new root node with one key
	if (root_node == NULL) {
		root_node = new BPlusTreeNode<T>();
		root_node->keys.push_back(key);
		return;
	}
	// Find the leaf node where the key should be inserted
	BPlusTreeNode<T>* leaf = find_leaf(key);
	// Insert the key into the leaf node in increasing order
	insert_key(leaf, key);
	// Check if there is an overflow in the leaf node
	if (is_overflow(leaf)) {
		// Split the leaf node into two nodes and insert the middle key into the parent node
		split_and_insert(leaf);
	}
}


// A helper function to find the leaf node where the key should be inserted
template <class T>
BPlusTreeNode<T>* BPlusTree<T>::find_leaf(const T& key) {
	BPlusTreeNode<T>* current = root_node;
	while (!current->is_leaf()) {
		unsigned int i = 0;
		while (i < current->keys.size() && key > current->keys[i]) {
		i++;
		}
		current = current->children[i];
	} 
	return current;
}

// A helper function to insert a key into a node in increasing order
template <class T>
void BPlusTree<T>::insert_key(BPlusTreeNode<T>* node, const T& key) {
	unsigned int i = 0;
	while (i < node->keys.size() && key > node->keys[i]) {
		i++;
	}
	node->keys.insert(node->keys.begin() + i, key);
}

// A helper function to check if a node has an overflow
template <class T>
bool BPlusTree<T>::is_overflow(BPlusTreeNode<T>* node) {
  	return node->keys.size() > start_size;
}

// A helper function to split a node into two nodes and insert the middle key into the parent node
template <class T>
void BPlusTree<T>::split_and_insert(BPlusTreeNode<T>* node) {
	// Split the node into two nodes
	BPlusTreeNode<T>* right = split(node);
	// Insert the middle key into the parent node
	T middle_key = get_middle_key(node);
	remove_middle_key(node);
	BPlusTreeNode<T>* parent = get_or_create_parent(node);
	insert_key(parent, middle_key);
	insert_child(parent, right);
	update_parent(right, parent);
	// Check if there is an overflow in the parent node
	if (is_overflow(parent)) {
		// Split the parent node into two nodes and repeat this step until there is no overflow or a new root node is created
		split_and_insert(parent);
	}
}

// A helper function to split a non-leaf node into two nodes and return the right one
template <class T>
BPlusTreeNode<T>* BPlusTree<T>::split(BPlusTreeNode<T>* node) {
	BPlusTreeNode<T>* right = new BPlusTreeNode<T>();
	int mid = start_size / 2;
	right->keys.assign(node->keys.begin() + mid + 1, node->keys.end());
	
	if (!node->is_leaf()) {
		right->children.assign(node->children.begin() + mid + 1, node->children.end());
		update_parents(right->children, right);
		remove_children(node, mid + 1);
		
	}
	
	remove_keys(node, mid + 1);
	return right;
}

// A helper function to get the middle key of a node
template <class T>
T BPlusTree<T>::get_middle_key(BPlusTreeNode<T>* node) {
	int mid = start_size / 2;
	return node->keys[mid];
}

// A helper function to remove the middle key of a node
template <class T>
void BPlusTree<T>::remove_middle_key(BPlusTreeNode<T>* node) {
  	node->keys.pop_back();
}

// A helper function to get or create the parent node of a node
template <class T>
BPlusTreeNode<T>* BPlusTree<T>::get_or_create_parent(BPlusTreeNode<T>* node) {
	BPlusTreeNode<T>* parent = node->parent;
	// If there is no parent node, create a new root node
	if (parent == NULL) {
		parent = new BPlusTreeNode<T>();
		root_node = parent;
		update_parent(node, parent);
		insert_child(parent, node);
	}
	return parent;
}

// A helper function to insert a child pointer into a node
template <class T>
void BPlusTree<T>::insert_child(BPlusTreeNode<T>* node, BPlusTreeNode<T>* child) {
	unsigned int i = 0;
	while (i < node->keys.size() && child->keys[0] > node->keys[i]) {
		i++;
	}
	node->children.insert(node->children.begin() + i + 1, child);
}

// A helper function to update the parent pointer of a node
template <class T>
void BPlusTree<T>::update_parent(BPlusTreeNode<T>* node, BPlusTreeNode<T>* parent) {
  	node->parent = parent;
}

// A helper function to update the parent pointers of a vector of nodes
template <class T>
void BPlusTree<T>::update_parents(std::vector<BPlusTreeNode<T>*> nodes, BPlusTreeNode<T>* parent) {
	for (unsigned int i = 0; i < nodes.size(); i++) {
		nodes[i]->parent = parent;
	}
}

// A helper function to remove some keys from a node
template <class T>
void BPlusTree<T>::remove_keys(BPlusTreeNode<T>* node, unsigned int start) {
  	node->keys.erase(node->keys.begin() + start, node->keys.end());
}

// A helper function to remove some children from a node
template <class T>
void BPlusTree<T>::remove_children(BPlusTreeNode<T>* node, unsigned int start) {
  	node->children.erase(node->children.begin() + start, node->children.end());
}

// A function to find a node that contains a key
template <class T>
BPlusTreeNode<T>* BPlusTree<T>::find(const T& key) {
	// If the tree is empty, return NULL
	if (root_node == NULL) {
		return NULL;
	}
	// Start from the root node and compare the key with the keys in the node
	BPlusTreeNode<T>* current = root_node;
	while (!current->is_leaf()) {
		unsigned int i = 0;
		while (i < current->keys.size() && key > current->keys[i]) {
		i++;
		}
		current = current->children[i];
	}
	// Check if the key is found in the leaf node
	if (current->contains(key)) {
		return current;
	}
	else {
		return NULL;
	}
}

template <class T>
BPlusTree<T>::~BPlusTree() {
  delete root_node; // will recursively delete all nodes below it as well
}



#endif
