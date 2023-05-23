HOMEWORK 8: B+ TREES


NAME:  Jimmy Chen


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Ethan Garcia, GeeksforGeeks.org, cplusplus.org, stackoverflow.com, youtube.com

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  35


TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your implementation?

I used Dr. Memory and valgrind to debug my code. As I went on, I created functions to made the readability 
of the code better and it also helped me with tackling which functions caused assertion faults and
where my code would cause a fail in the test cases. 

I also used GDB to step through each function and watch the data and track the order of the nodes
through insert. 



MISC. COMMENTS TO GRADER:  
I didn't get to implement the rest of the code due to time contraints and other classes.

i created copy constructors as well as a destructor but they cause me to lose submitty points due to memory errors.
i didnt have time to fix these errors so i just the code is below for you to see. Im sorry if i wasn't supposed to have it in the readme.
/*
		// BPlusTree(BPlusTree<T>& other){
		// 	copy(this->root_node, other.root_node, NULL);
		// }
		

		// BPlusTree<T> operator= (BPlusTree<T>& other){
		// 	copy(this->root_node, other.root_node, NULL);
		// 	return *this;
		// }

		// BPlusTreeNode<T>* copy(BPlusTreeNode<T>* &old, BPlusTreeNode<T>* &new_tree, BPlusTreeNode<T>* parent) {
		// 	if (old == NULL) {
		// 		return NULL;
		// 	}
		// 	// Create a new tree, set the keys from the old and the parents as well.
		// 	new_tree = new BPlusTreeNode<T>();
		// 	new_tree->keys = old->keys;
		// 	new_tree->parent = parent;
		// 	// Loop through all the children to set them as well
		// 	for (unsigned int i = 0; i < new_tree->children.size(); i++) {
		// 		copy(old->children[i], new_tree->children[i], parent);
		// 	}
		// 	return NULL;
		// }

		// // DESTRUCTORS

		// ~BPlusTree() {
		// 	delete_subtree(root_node);
		// }
		
		// void delete_subtree(BPlusTreeNode<T>* node) {
		// 	if (!node) {
		// 		return;
		// 	} else {
		// 		for (unsigned int i = 0; i < node->children.size(); i++) {
		// 			delete_subtree(node->parent);
		// 			delete node;
		// 		}
		// 	}
		// 	return;
		// }
*/