/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/
#include <iostream>
#include <vector>
#include <utility>
#include <list>

using namespace std;

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
		// Constructors and Destructor

		BPlusTree() {
			root_node = NULL;
			init_size = 0;
		} 

		BPlusTree(int initial_size) {
			root_node = NULL;
			init_size = initial_size;
		} 

		~BPlusTree() {
			wipe_out_everything();
		}

		BPlusTree(BPlusTree<T>& bpt) {
			root_node = this->recursive_copy(bpt.root_node, NULL);
			init_size = bpt.init_size;
		}


		
		// Operator(s) TODO: operator=
		BPlusTree<T>& operator=(BPlusTree<T>& bpt);

		
		// Find
		BPlusTreeNode<T>* find(T key_value);

		// Insert
		void insert(T key_value);


		// Printing
		void print_sideways(ostream& out);
		void print_BFS(ostream& out);
		void print_BFS_pretty(ostream& out);

			// Print helpers
			void print_as_sideways_tree(ostream& out, BPlusTreeNode<T>*& node, int depth);
			

	private:

		// Member Variables
		BPlusTreeNode<T>* root_node;
		unsigned int init_size;
		const bool a_leaf = true;

		// General helper functions
		void copy(BPlusTreeNode<T>* node, BPlusTreeNode<T>* p);
		BPlusTreeNode<T>* recursive_copy(BPlusTreeNode<T>* node, BPlusTreeNode<T>* p);
		void set_tree(BPlusTree<T>& bpt);
		void recursive_destroy(BPlusTreeNode<T>* node);
		void wipe_out_everything();
		bool empty_tree_check();
		bool empty_tree_check(BPlusTreeNode<T>*& node);
		BPlusTreeNode<T>* new_node();
		BPlusTreeNode<T>* new_node_copy(BPlusTreeNode<T>*& node);
		BPlusTreeNode<T>* new_node_value(T& key_value);
		void add_key_value(T& key_value, BPlusTreeNode<T>*& node);
		bool leaf_check(BPlusTreeNode<T>*& node) {
			bool check = false;
			if (node->is_leaf()) {
				check = true;
			}
			
			return check;
		}

		// Find helper functions
		BPlusTreeNode<T>* find_helper(T& key_value, BPlusTreeNode<T>*& node);


		// Insert helper functions
		void insert_into_empty_tree(T& key_value);
		void not_empty_insert_helper(T& key_value, BPlusTreeNode<T>*& node);
		void with_parent_insert_helper(T& key_value, BPlusTreeNode<T>*& node, BPlusTreeNode<T>*& p);
		void insert_parent(T& key_value, BPlusTreeNode<T>*& node, BPlusTreeNode<T>*& p, int current_key);
		void insert_leaf(T& key_value, BPlusTreeNode<T>*& node, BPlusTreeNode<T>*& p, int current_key);
		void set_parent_and_children(BPlusTreeNode<T>*& node);
		pair<int, int> find_split(BPlusTreeNode<T>*& node);
		pair<int, int> find_child_split(BPlusTreeNode<T>*& node, int current_key);
		void split_and_fix_root(pair<int, int>& splits, BPlusTreeNode<T>*& node);
		void split_and_fix_children(pair<int, int>& splits, BPlusTreeNode<T>*& node, BPlusTreeNode<T>*& p, int current_key);

};

/*
		Stuff for functions:

		BPlusTree<T>::

		template <class T>

		BPlusTreeNode<T>*
*/


template <class T> void BPlusTree<T>::insert(T key_value) {
	bool insert_done = false;
	
	bool EmptyCheck = empty_tree_check();

	if (EmptyCheck) {
		insert_into_empty_tree(key_value);
		insert_done = true;
	}

	if (insert_done) {
		return;
	}
	BPlusTreeNode<T>* parent = NULL;
	with_parent_insert_helper(key_value, root_node, parent);
}

template <class T> bool BPlusTree<T>::empty_tree_check() {
	bool check = false;
	if (root_node == NULL) {
		check = true;
	}
	return check;
}

template <class T> void BPlusTree<T>::insert_into_empty_tree(T& key_value) {
	root_node = new_node_value(key_value);
}

template <class T> BPlusTreeNode<T>* BPlusTree<T>::new_node() {
	BPlusTreeNode<T>* temp = new BPlusTreeNode<T>();
	return temp;
}

template <class T> BPlusTreeNode<T>* BPlusTree<T>::new_node_value(T& key_value) {
	BPlusTreeNode<T>* temp = new_node();
	temp->keys.push_back(key_value);

	return temp;
}

template <class T> BPlusTreeNode<T>* BPlusTree<T>::find(T key_value) {
	BPlusTreeNode<T>* node = find_helper(key_value, root_node);
	return node;
}

template <class T> BPlusTreeNode<T>* BPlusTree<T>::find_helper(T& key_value, BPlusTreeNode<T>*& node) {
	bool EmptyCheck = empty_tree_check(); 
	if (EmptyCheck) {
		return NULL;  // prevents returning a child [-1]
	}

	for (unsigned int key_val = 0; key_val < node->keys.size(); key_val++) {
		if (key_value < node->keys[key_val]) {
			if (node->is_leaf() == a_leaf) { // Exit case: key left
				return node;
			}
			else { // Have not found end so keep searching by child
				return find_helper(key_value, node->children[key_val]);
			}
		}
	}
	if (node->is_leaf() != a_leaf) { // find key right
		return find_helper(key_value, node->children[node->children.size() - 1]);
	} 
	else { // Exit case: key does not exist after
		  // not finding anything left and right
		return node;
	}
}


// CHECK 1: INSERT INTO EMPTY TREE AND FIND WORKS :) - TODO work find with a set larger than size 1

// inserting into an non-empty set
template <class T> void BPlusTree<T>::not_empty_insert_helper(T& key_value, BPlusTreeNode<T>*& node) {
	bool leave_check = false;
	BPlusTreeNode<T>* parent = NULL;
	int current_key = 0;
	for (; current_key < node->keys.size(); ++current_key) {
		if (key_value < node->keys[current_key]) {

			if (node->is_leaf() != a_leaf) {
				insert_parent(key_value, node, parent, current_key);
			}
			else {
				insert_leaf(key_value, node, parent, current_key);

				leave_check = true;
				break;
			}
		}
	}
	if (leave_check) {
		return;
	}

	
	if (node->is_leaf() != a_leaf) {
		insert_parent(key_value, node, parent, current_key);
	}
	else {
		insert_leaf(key_value, node, parent, current_key);
	}

	

}

template <class T> void BPlusTree<T>::with_parent_insert_helper(T& key_value, BPlusTreeNode<T>*& node, BPlusTreeNode<T>*& p) {
	bool leave_check = false;
	int current_key = 0;
	for ( ; current_key < node->keys.size(); ++current_key) {
		if (key_value < node->keys[current_key]) {

			if (node->is_leaf() != a_leaf) {
				insert_parent(key_value, node, p, current_key);
			}
			else {
				insert_leaf(key_value, node, p, current_key);

				leave_check = true;
				break;
			}
		}
	}
	if (leave_check) {
		return;
	}

	
	if (node->is_leaf() != a_leaf) {
		insert_parent(key_value, node, p, current_key);
	}
	else {
		insert_leaf(key_value, node, p, current_key);
	}

	
}

template <class T> void BPlusTree<T>::insert_parent(T& key_value, BPlusTreeNode<T>*& node, BPlusTreeNode<T>*& p, int current_key) {
	// TODO check if going through to deeper level by repitition
	with_parent_insert_helper(key_value, node->children[current_key], node);				// INFINITE RECURSION ISSUE
	// want to get here! 
	if (node->children[current_key]->keys.size() >= init_size) {
		pair<int, int> split_ = find_child_split(node, current_key);
		split_and_fix_children(split_, node, p, current_key);
	}
		
	if (!p) {
		if (node->keys.size() >= init_size) {
			set_parent_and_children(node);
		}
	}
}

template <class T> void BPlusTree<T>::insert_leaf(T& key_value, BPlusTreeNode<T>*& node, BPlusTreeNode<T>*& p, int current_key) {
	typename vector<T>::iterator locate_insert_location = node->keys.begin();
	node->keys.insert(locate_insert_location + current_key, key_value);

	if (!p) {
		if (node->keys.size() >= init_size) {
			set_parent_and_children(node);
		}
	}
}

template <class T> pair<int, int> BPlusTree<T>::find_split(BPlusTreeNode<T>*& node) {
	pair<int, int> returned;
	int split1, split2, denominator, sizes;
	denominator = 2;
	sizes = node->keys.size();
	split1 = sizes / denominator;

	if (node->is_leaf() == a_leaf) {
		split2 = sizes - split1;
	}
	else {
		int buffer = 1;
		split2 = sizes - split1 - buffer;
	}

	returned = make_pair(split1, split2);

	return returned;
}

template <class T> void BPlusTree<T>::split_and_fix_children(pair<int, int>& splits, BPlusTreeNode<T>*& node, BPlusTreeNode<T>*& p, int current_key) {
	BPlusTreeNode<T>* child = new_node();
	child->parent = node;
	while (child->keys.size() != splits.second) {
		child->keys.insert(child->keys.begin(), node->keys[node->keys.size() - 1]);
		node->children[current_key]->keys.pop_back();
	}

	if (node->children[current_key]->is_leaf() != a_leaf) {
		int buffer = 1;
		while (child->children.size() != child->keys.size() + buffer) {
			child->children.insert(child->children.begin(), node->children[current_key]->children[node->children[current_key]->children.size() - 1]);
			child->children.front()->parent = child; 											// PROBLEM
			node->children[current_key]->children.pop_back();
		}
	}
	// setting up parent value
	T _key_ = node->children[current_key]->keys[node->children[current_key]->keys.size() - 1];
	if (node->children[current_key]->is_leaf() == a_leaf) {
		_key_ = child->keys[0];
	}
	else {
		node->children[current_key]->keys.pop_back();
	}

	typename vector<T>::iterator locate_keys = node->keys.begin();
	typename vector<BPlusTreeNode<T>*>::iterator locate_child = node->children.begin();

	node->keys.insert(locate_keys + current_key, _key_); // PROBLEM
	
	int buffer = 1;
	node->children.insert(locate_child + buffer + current_key, child);

	
}

template <class T> void BPlusTree<T>::split_and_fix_root(pair<int, int>& splits, BPlusTreeNode<T>*& node) {

	// size dif:
	// [node->keys.size() - 1]
	// .back()
	
	BPlusTreeNode<T>* child = new_node();
	while (child->keys.size() != splits.second) {
		child->keys.insert(child->keys.begin(), node->keys.back());
		node->keys.pop_back();
	}

	if (node->is_leaf() != a_leaf) {
		int buffer = 1;
		while (child->children.size() != child->keys.size() + buffer) {
			child->children.insert(child->children.begin(), node->children[node->children.size() - 1]);
			child->children.front()->parent = child; 											// PROBLEM
			node->children.pop_back();
		}
	}

	BPlusTreeNode<T>* fixed_root_parent = new_node();
	node->parent = fixed_root_parent;
	child->parent = fixed_root_parent;

	if (node->is_leaf() != a_leaf) {
		fixed_root_parent->keys.push_back(node->keys[node->keys.size() - 1]);
		node->keys.pop_back();
	}
	else {
		fixed_root_parent->keys.push_back(child->keys[0]);
	}

	fixed_root_parent->children.push_back(node);
	fixed_root_parent->children.push_back(child);
	this->root_node = fixed_root_parent;

}

template <class T> void BPlusTree<T>::set_parent_and_children(BPlusTreeNode<T>*& node) {
	pair<int, int> splits_ = find_split(node);
	split_and_fix_root(splits_, node);
}

template <class T> pair<int, int> BPlusTree<T>::find_child_split(BPlusTreeNode<T>*& node, int current_key) {
	pair<int, int> returned;
	int split1, split2, denominator, sizes;
	denominator = 2;
	sizes = node->children[current_key]->keys.size(); // PROBLEM ; FIX : GET KEYS SIZE NOT NODE SIZE
	split1 = sizes / denominator;

	if (node->is_leaf() == a_leaf) {
		split2 = sizes - split1;
	}
	else {
		int buffer = 1;
		split2 = sizes - split1 - buffer;
	}

	returned = make_pair(split1, split2);

	return returned;
}
// CHECK 1.5: Got another insert to work, literally almost there with another insert
// CHECK 2: I think I got it to insert more than one after the initial insert

template <class T> void BPlusTree<T>::recursive_destroy(BPlusTreeNode<T>* node) {
	if (!node) { // exit case
		return;
	}

	for (int n = 0; n < node->children.size(); n++) {
		recursive_destroy(node->children[n]);
	}

	delete node;
}

template <class T> void BPlusTree<T>::copy(BPlusTreeNode<T>* node, BPlusTreeNode<T>* p) {
	recursive_copy(node, p);
}

template <class T> BPlusTreeNode<T>* BPlusTree<T>::recursive_copy(BPlusTreeNode<T>* node, BPlusTreeNode<T>* p) {
	
	if (!node) {
		return NULL;
	}
	BPlusTreeNode<T>* new_ = new_node();

	for (int n = 0; n < node->children.size(); n++) {
		new_->children.push_back(recursive_copy(node->children[n], new_));
	}

	new_->parent = p;
	new_->keys = node->keys; 

	return new_;
	
}

template <class T> void BPlusTree<T>::set_tree(BPlusTree<T>& bpt) {
	root_node = recursive_copy(bpt.root_node, NULL);
	init_size = bpt.init_size;
}

template <class T> BPlusTree<T>& BPlusTree<T>::operator=(BPlusTree<T>& bpt) { // CHECKHERE
	if (&bpt != this) {
		this->recursive_destroy(root_node);
		root_node = recursive_copy(bpt.root_node, NULL);
		init_size = bpt.init_size;
	}
	return *this;
}

template <class T> void BPlusTree<T>::wipe_out_everything() {
	recursive_destroy(root_node);
	root_node = NULL;
}


// CHECK 3: Copy and Destroy

template <class T> void BPlusTree<T>::print_as_sideways_tree(ostream& out, BPlusTreeNode<T>*& node, int depth) {
	bool EmptyCheck = empty_tree_check();
	int increment = 1;

	if (EmptyCheck) {
		out << "Tree is empty." << endl;
		return;
	}
	int size_check = node->children.size();
	int split1, split2;
	split1 = size_check / 2;
	split2 = size_check - split1;

	for (int i = 0; i < split1; i++) {                  // TODO
		print_as_sideways_tree(out, node->children[i], depth + increment);
	}

	for (int iteration = 0; iteration < depth; iteration++) {
		out << "\t";
	}
	out << node->keys[0]; // start
	for (int next = 0; next < node->keys.size(); next++) {
		out << ',' << node->keys[next];
	}
	out << endl;

	for (int split_point = split1; split_point < split1 + split2; split_point++) {
		print_as_sideways_tree(out, node->children[split_point], depth + increment);
	}
}

template <class T> void BPlusTree<T>::print_sideways(ostream& out) {
	print_as_sideways_tree(out, root_node, 0);
}

template <class T> void BPlusTree<T>::print_BFS(ostream& out) {
	bool EmptyCheck = empty_tree_check();
	

	if (EmptyCheck) {
		out << "Tree is empty." << endl;
		return;
	}
	string tab = "        ";
	vector<int> depths;
	depths.push_back(0);
	vector<BPlusTreeNode<T>*> bfs;     // TODO function this
	bfs.push_back(root_node);

	int limit = 0;
	int increment = 0;
	int next_ = 1;
	while (bfs.size() != 0) {
		BPlusTreeNode<T>* c = bfs[0]; // start iteration
		bfs.erase(bfs.begin()); // TODO function this
		int depth = depths[0];
		depths.erase(depths.begin());

		if (depth == limit) {
			if (depth > increment) {
				out << tab;
			}
		}
		else {
			out << endl;
		}

		out << c->keys[0];
		for (int next = 1; next < c->keys.size(); next++) {
			out << ',' << c->keys[next];
		}

		for (int add = 0; add < c->children.size(); add++) {
			bfs.push_back(c->children[add]);
			depths.push_back(depth + next_);
		}

		limit = depth;
	}
	out << endl;
}

template <class T> void BPlusTree<T>::print_BFS_pretty(ostream& out) {
	bool EmptyCheck = empty_tree_check();

	if (EmptyCheck) {
		out << "Tree is empty." << endl;
		return;
	}
	string tab = "        ";
	 // Find levels
    int depth = 0;
    BPlusTreeNode<T>* node = root_node;
    while (node->children.size() != 0) {
        node = node->children[0];
        depth += 1;
    }
    
    
    list<BPlusTreeNode<T>*> print_queue;
    print_queue.push_back(root_node);
    list<int> depths;
    depths.push_back(0);
 	list<BPlusTreeNode<T>*> parents;
    parents.push_back(NULL);
    
    int limit = -1;
    BPlusTreeNode<T>* end_node = NULL;
    while (print_queue.size() != 0) {
        // get and remove the first element from queue
        BPlusTreeNode<T>* current(print_queue.front());
        print_queue.pop_front();
        int depth_ = depths.front();
        depths.pop_front();
        BPlusTreeNode<T>* parent = parents.front();
        parents.pop_front();
        
        // spacing
        if (depth_ != limit) {
            if (depth_ > 0) out << endl;
            for (int i = 0; i < depth - depth_; ++i) out << tab;
        } else {
            out << tab;
            if (parent != end_node && depth_ == depth) {
				out << tab;
			}
            else if (parent != end_node) {
                for (int i = 0; i <= depth - depth_; ++i) out << tab;
                for (int i = 0; i <= init_size; ++i) out << tab;
            } else for (int i = 0; i < depth - depth_; ++i) {
				out << tab;
			}
        }
        
        // print key vector
        out << current->keys[0];
        for (unsigned int i = 1; i < current->keys.size(); ++i)
            out << ',' << current->keys[i];
        
        // append current node's children to queue
        for (unsigned int i = 0; i < current->children.size(); ++i) {
            print_queue.push_back(current->children[i]);
            depths.push_back(depth_ + 1);
            parents.push_back(current->children[i]->parent);
        }
        
        limit = depth_;
        end_node = current->parent;
    }
    out << endl;
}



// Check 4: Printing Done and DONE!

#endif